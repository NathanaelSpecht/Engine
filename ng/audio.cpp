
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

void ng::Clip::init (Audio* a, const char* file) {
	// load audio file
	Clip wav;
	if (SDL_LoadWAV(file, &(wav.spec), &(wav.data), &(wav.samples)) == NULL) {
		throw std::runtime_error(SDL_GetError());
	}
	this->spec = a->spec;
	this->data = NULL;
	this->samples = 0;
	
	// use audio stream to convert loaded audio to desired format
	SDL_AudioStream* stream = NULL;
	stream = SDL_NewAudioStream(
	wav.spec.format, wav.spec.channels, wav.spec.freq,
	this->spec.format, this->spec.channels, this->spec.freq);
	if (stream == NULL) {
		SDL_FreeWAV(wav.data);
		throw std::runtime_error("unsupported audio format");
	}
	
	// put audio into stream
	if (SDL_AudioStreamPut(stream, wav.data, wav.samples) != 0) {
		SDL_FreeAudioStream(stream);
		SDL_FreeWAV(wav.data);
		throw std::runtime_error("audio conversion failure");
	}
	
	// convert audio
	SDL_AudioStreamFlush(stream);
	
	// get converted audio
	int buffer_max = ((int)this->spec.freq * 3600) * (int)this->spec.channels;
	uint8_t* buffer = static_cast<uint8_t*>(std::malloc(buffer_max * sizeof(uint8_t)));
	int buffer_length = SDL_AudioStreamGet(stream, buffer, buffer_max);
	SDL_FreeAudioStream(stream);
	SDL_FreeWAV(wav.data);
	if (buffer_length <= 0) {
		// technically an error is -1, but we can't malloc 0 so catch that too
		throw std::runtime_error("audio conversion failure");
	}
	
	// copy converted audio to clip
	this->data = static_cast<uint8_t*>(std::malloc(buffer_length * sizeof(uint8_t)));
	for (int i = 0; i < buffer_length; i++) {
		this->data[i] = buffer[i];
	}
	this->samples = buffer_length;
	std::free(buffer);
}

void ng::Clip::quit () {
	if (this->data != NULL) {
		std::free(this->data);
		this->data = NULL;
		this->samples = 0;
	}
}

void ng::Sound::init (Clip* clip, int mode) {
	// start sound at the beginning of a clip
	this->clip = clip;
	this->sample = 0;
	this->mode = mode;
}

void ng::Channel::init () {
	this->data = NULL;
	this->sounds = 0;
}

void ng::Channel::quit () {
	// free sounds
	if (this->sounds > 0) {
		std::free(this->data);
		this->data = NULL;
		this->sounds = 0;
	}
}

void ng::Channel::start_sound (Clip* clip, int mode) { // add sound
	this->data = static_cast<Sound*>(std::realloc(this->data, (this->sounds+1) * sizeof(Sound)));
	this->data[this->sounds].init(clip, mode);
	this->sounds++;
}

void ng::Channel::stop_sound (int sound) { // remove sound
	if (this->sounds < 1) {
		// no sounds to remove
		return;
	} else if (this->sounds == 1) {
		// remove last sound
		std::free(this->data);
		this->data = NULL;
		this->sounds = 0;
		return;
	}
	// remove sound, shift remaining sounds to fill void, and realloc
	for (int i = sound; i < this->sounds-1; i++) {
		this->data[i] = this->data[i+1];
	}
	this->data = static_cast<Sound*>(std::realloc(this->data, (this->sounds-1) * sizeof(Sound)));
	this->sounds--;
}

void ng::Channel::stop () { // remove all sounds
	if (this->sounds > 0) {
		std::free(this->data);
		this->data = NULL;
		this->sounds = 0;
	}
}

void ng::Audio::init () {
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
		throw std::runtime_error(SDL_GetError());
	}
	
	this->spec = obtained;
	this->device = device_id;
	this->data = static_cast<uint8_t*>(std::malloc(4096 * sizeof(uint8_t)));
	this->samples = 4096;
	this->playing = false;
}

void ng::Audio::quit () {
	// free queue and clear queued audio
	std::free(this->data);
	this->data = NULL;
	this->samples = 0;
	SDL_ClearQueuedAudio(this->device);
	
	// close audio device
	SDL_CloseAudioDevice(this->device);
	this->device = 0;
}

void ng::Audio::play () { // unpause audio device
	SDL_PauseAudioDevice(this->device, 0);
	this->playing = true;
}

void ng::Audio::pause () { // pause audio device
	SDL_PauseAudioDevice(this->device, 1);
	this->playing = false;
}

void ng::Audio::stop () { // clear queued audio
	SDL_ClearQueuedAudio(this->device);
}

void ng::Audio::clear () { // fill queue with silence
	if (this->playing && SDL_GetQueuedAudioSize(this->device) < (this->samples * 2)) {
		int silence = 0;
		for (int i = 0; i < static_cast<int>(this->samples); i++) {
			this->data[i] = silence;
		}
	}
}

int ng::Audio::mix_sample (int a, int b) const { // add decibels
	int sum;
	sum = (a+b)/2;
	return sum;
}

void ng::Audio::mix_sound (Channel* c, int sound) { // add clip data to queue
	Clip* clip = c->data[sound].clip;
	int s = c->data[sound].sample;
	switch (c->data[sound].mode) {
		case ng::SoundPlayOnce: {
			for (int i=0; i < static_cast<int>(this->samples); i++) {
				this->data[i] = this->mix_sample(this->data[i], clip->data[s]);
				s++;
				if (s >= static_cast<int>(clip->samples)) {
					c->data[sound].mode = ng::SoundComplete;
					break;
				}
			}
			break;
		} case ng::SoundLoop: {
			for (int i=0; i < static_cast<int>(this->samples); i++) {
				this->data[i] = this->mix_sample(this->data[i], clip->data[s]);
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

void ng::Audio::mix_channel (Channel* c) {
	if (this->playing && SDL_GetQueuedAudioSize(this->device) < (this->samples * 2)) {
		for (int i = 0; i < c->sounds;) {
			this->mix_sound(c, i);
			if (c->data[i].mode == ng::SoundComplete) {
				c->stop_sound(i);
			} else {
				i++;
			}
		}
	}
}

void ng::Audio::queue () { // queue audio
	if (this->playing && SDL_GetQueuedAudioSize(this->device) < (this->samples * 2)) {
		if (SDL_QueueAudio(this->device, this->data, this->samples) != 0) {
			throw std::runtime_error(SDL_GetError());
		}
	}
}


