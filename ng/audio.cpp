
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

int ng_audio_init (ngAudio* a) {
	SDL_AudioDeviceID device_id = 0;
	SDL_AudioSpec desired;
	desired.freq = 44100;
	desired.format = AUDIO_U8;
	desired.samples = 4096;
	desired.channels = 1;
	desired.callback = NULL;
	SDL_AudioSpec obtained;
	device_id = SDL_OpenAudioDevice(NULL, 0, &desired, &obtained, 0);
	if (device_id == 0) {
		return NG_ERROR;
	}
	
	a->spec = obtained;
	a->device = device_id;
	a->data = static_cast<uint8_t*>(malloc(4096 * sizeof(uint8_t)));
	a->samples = 4096;
	a->playing = false;
	
	return NG_SUCCESS;
}

void ng_audio_quit (ngAudio* a) {
	// free queue and clear queued audio
	free(a->data);
	a->data = NULL;
	a->samples = 0;
	SDL_ClearQueuedAudio(a->device);
	
	// close audio device
	SDL_CloseAudioDevice(a->device);
	a->device = 0;
}

int ng_clip_init (ngAudio* a, ngClip* clip, const char* file) {
	// load audio file
	ngClip wav;
	if (SDL_LoadWAV(file, &(wav.spec), &(wav.data), &(wav.samples)) == NULL) {
		return NG_ERROR;
	}
	clip->spec = a->spec;
	clip->data = NULL;
	clip->samples = 0;
	
	// use audio stream to convert loaded audio to desired format
	SDL_AudioStream* stream = NULL;
	stream = SDL_NewAudioStream(
	wav.spec.format, wav.spec.channels, wav.spec.freq,
	clip->spec.format, clip->spec.channels, clip->spec.freq);
	if (stream == NULL) {
		return NG_ERROR;
	}
	
	// put audio into stream
	if (SDL_AudioStreamPut(stream, wav.data, wav.samples) != 0) {
		return NG_ERROR;
	}
	
	// convert audio
	SDL_AudioStreamFlush(stream);
	
	// get converted audio
	int buffer_max = ((int)clip->spec.freq * 3600) * (int)clip->spec.channels;
	uint8_t* buffer = static_cast<uint8_t*>(malloc(buffer_max * sizeof(uint8_t)));
	int buffer_length = SDL_AudioStreamGet(stream, buffer, buffer_max);
	if (buffer_length <= 0) {
		// technically an error is -1, but we can't malloc 0 so catch that too
		return NG_ERROR;
	}
	SDL_FreeAudioStream(stream);
	SDL_FreeWAV(wav.data);
	
	// copy converted audio to clip
	clip->data = static_cast<uint8_t*>(malloc(buffer_length * sizeof(uint8_t)));
	for (int i = 0; i < buffer_length; i++) {
		clip->data[i] = buffer[i];
	}
	clip->samples = buffer_length;
	free(buffer);
	
	return NG_SUCCESS;
}

void ng_clip_quit (ngClip* clip) {
	if (clip->data != NULL) {
		free(clip->data);
		clip->data = NULL;
		clip->samples = 0;
	}
}

void ng_channel_init (ngChannel* c) {
	c->data = NULL;
	c->sounds = 0;
}

void ng_channel_quit (ngChannel* c) {
	// free sounds
	if (c->sounds > 0) {
		free(c->data);
		c->data = NULL;
		c->sounds = 0;
	}
}

void ng_audio_play (ngAudio* a) { // unpause audio device
	SDL_PauseAudioDevice(a->device, 0);
	a->playing = true;
}

void ng_audio_pause (ngAudio* a) { // pause audio device
	SDL_PauseAudioDevice(a->device, 1);
	a->playing = false;
}

void ng_channel_start_sound (ngChannel* c, ngClip* clip, int mode) { // add sound
	ngSound sound;
	sound.clip = clip;
	sound.sample = 0;
	sound.mode = mode;
	c->data = static_cast<ngSound*>(realloc(c->data, (c->sounds+1) * sizeof(ngSound)));
	c->data[c->sounds] = sound;
	c->sounds++;
}

void ng_channel_stop_sound (ngChannel* c, int sound) { // remove sound
	if (c->sounds < 1) {
		// no sounds to remove
		return;
	} else if (c->sounds == 1) {
		// remove last sound
		free(c->data);
		c->data = NULL;
		c->sounds = 0;
		return;
	}
	// remove sound, shift remaining sounds to fill void, and realloc
	for (int i = sound; i < c->sounds-1; i++) {
		c->data[i] = c->data[i+1];
	}
	c->data = static_cast<ngSound*>(realloc(c->data, (c->sounds-1) * sizeof(ngSound)));
	c->sounds--;
}

void ng_channel_stop (ngChannel* c) { // remove all sounds
	if (c->sounds > 0) {
		free(c->data);
		c->data = NULL;
		c->sounds = 0;
	}
}

void ng_audio_stop (ngAudio* a) { // clear queued audio
	SDL_ClearQueuedAudio(a->device);
}

void ng_audio_clear (ngAudio* a) { // fill queue with silence
	if (a->playing && SDL_GetQueuedAudioSize(a->device) < (a->samples * 2)) {
		int silence = 0;
		for (int i = 0; i < static_cast<int>(a->samples); i++) {
			a->data[i] = silence;
		}
	}
}

int ng_audio_mix_sample (int a, int b) { // add decibels
	int sum;
	sum = (a+b)/2;
	return sum;
}

void ng_audio_mix_sound (ngAudio* a, ngChannel* c, int sound) { // add clip data to queue
	ngClip* clip = c->data[sound].clip;
	int s = c->data[sound].sample;
	switch (c->data[sound].mode) {
		case NG_PLAYONCE: {
			for (int i=0; i < static_cast<int>(a->samples); i++) {
				a->data[i] = ng_audio_mix_sample(a->data[i], clip->data[s]);
				s++;
				if (s >= static_cast<int>(clip->samples)) {
					c->data[sound].mode = NG_COMPLETE;
					break;
				}
			}
			break;
		} case NG_LOOP: {
			for (int i=0; i < static_cast<int>(a->samples); i++) {
				a->data[i] = ng_audio_mix_sample(a->data[i], clip->data[s]);
				s++;
				if (s >= static_cast<int>(clip->samples)) {
					s = 0;
				}
			}
			break;
		}
	}
	c->data[sound].sample = s;
}

void ng_audio_mix_channel (ngAudio* a, ngChannel* c) {
	if (a->playing && SDL_GetQueuedAudioSize(a->device) < (a->samples * 2)) {
		for (int i = 0; i < c->sounds;) {
			ng_audio_mix_sound(a, c, i);
			if (c->data[i].mode == NG_COMPLETE) {
				ng_channel_stop_sound(c, i);
			} else {
				i++;
			}
		}
	}
}

int ng_audio_queue (ngAudio* a) { // queue audio
	if (a->playing && SDL_GetQueuedAudioSize(a->device) < (a->samples * 2)) {
		if (SDL_QueueAudio(a->device, a->data, a->samples) != 0) {
			return NG_ERROR;
		}
	}
	return NG_SUCCESS;
}

