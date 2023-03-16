
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ngaudio.h"
#include "ngmath.h"

// Load .wav file into buffer, with same spec as audio device.
void ng::Clip::init (Audio* a, const char* file) {
	// load audio file
	SDL_AudioSpec spec;
	uint8_t* file_buffer;
	uint32_t file_bytes;
	if (SDL_LoadWAV(file, &spec, &file_buffer, &file_bytes) == NULL) {
		throw std::runtime_error(SDL_GetError());
	}
	
	// Use audio stream to convert loaded audio to desired format
	this->spec = a->spec;
	this->buffer = NULL;
	this->samples = 0;
	SDL_AudioStream* stream = NULL;
	stream = SDL_NewAudioStream(
	spec.format, spec.channels, spec.freq,
	this->spec.format, this->spec.channels, this->spec.freq);
	if (stream == NULL) {
		SDL_FreeWAV(file_buffer);
		throw std::runtime_error("unsupported audio format");
	}
	
	// Put audio into stream
	if (SDL_AudioStreamPut(stream, file_buffer, static_cast<int>(file_bytes)) != 0) {
		SDL_FreeAudioStream(stream);
		SDL_FreeWAV(file_buffer);
		throw std::runtime_error("audio conversion failure");
	}
	
	// Convert audio
	SDL_AudioStreamFlush(stream);
	
	// Get converted audio
	// Max 10 minutes (600 seconds) of stereo 44100Hz float32 audio = 212MB!
	int clip_max = static_cast<int>(this->spec.freq) * 600 *
		static_cast<int>(this->spec.channels) * sizeof(float);
	this->buffer = static_cast<float*>(std::malloc(clip_max));
	int clip_bytes = SDL_AudioStreamGet(stream, this->buffer, clip_max);
	SDL_FreeAudioStream(stream);
	SDL_FreeWAV(file_buffer);
	if (clip_bytes <= 0) {
		// Technically an error is -1, but we can't realloc 0 so catch that too
		throw std::runtime_error("audio conversion failure");
	}
	
	// Compute samples and resize buffer
	this->samples = clip_bytes / sizeof(float);
	this->buffer = static_cast<float*>(std::realloc(this->buffer, this->samples * sizeof(float)));
}

// Free buffer.
void ng::Clip::quit () {
	this->samples = 0;
	if (this->buffer != NULL) {
		std::free(this->buffer);
		this->buffer = NULL;
	}
}

void ng::Sound::init (Clip* clip, int mode) {
	this->clip = clip;
	this->sample = 0;
	this->mode = mode;
}

void ng::Channel::init () {
	this->queue = NULL;
	this->sounds = 0;
	this->buffer = NULL;
	this->samples = 0;
	this->volume = 1.0;
}

// Free queue and buffer.
void ng::Channel::quit () {
	this->sounds = 0;
	if (this->queue == NULL) {
		std::free(this->queue);
		this->queue = NULL;
	}
	this->samples = 0;
	if (this->buffer == NULL) {
		std::free(this->buffer);
		this->buffer = NULL;
	}
}

// Queue a sound with EnumSound mode.
void ng::Channel::play_sound (Clip* c, int mode) {
	this->queue = static_cast<Sound*>(std::realloc(this->queue,
		(this->sounds + 1) * sizeof(Sound)));
	this->queue[this->sounds].init(c, mode);
	this->sounds++;
}

// Remove queued sound.
void ng::Channel::remove_sound (int sound) {
	if (this->sounds == 0 || sound < 0 || sound >= this->sounds) {
		return;
	}
	
	if (this->sounds == 1) {
		// Remove last sound and free queue.
		std::free(this->queue);
		this->queue = NULL;
		this->sounds = 0;
	} else {
		// Shift remaining sounds to fill gap and reduce queue by 1.
		for (int i=sound; i < this->sounds - 1; i++) {
			this->queue[i] = this->queue[i + 1];
		}
		this->queue = static_cast<Sound*>(std::realloc(this->queue,
			(this->sounds - 1) * sizeof(Sound)));
		this->sounds--;
	}
}

// Remove all queued sounds.
void ng::Channel::stop () {
	if (this->queue != NULL) {
		std::free(this->queue);
		this->queue = NULL;
		this->sounds = 0;
	}
}

// Allocate samples for buffer and fill with silence.
void ng::Channel::clear (int samples) {
	this->buffer = static_cast<float*>(realloc(this->buffer, samples * sizeof(float)));
	this->samples = samples;
	for (int i=0; i < samples; i++) {
		this->buffer[i] = ng::dB_silence();
	}
}

// Mix samples from sound clip into channel buffer.
int ng::Channel::mix_sound (int sound) {
	Clip* clip = this->queue[sound].clip;
	int s = this->queue[sound].sample;
	
	switch (this->queue[sound].mode) {
		case ng::SoundPlayOnce: {
			for (int i=0; i < this->samples; i++) {
				this->buffer[i] = ng::mix_dB(this->buffer[i], clip->buffer[s]);
				s++;
				// Returns ng::SoundComplete if sound completes during the mix.
				if (s == clip->samples) {
					this->queue[sound].mode = ng::SoundComplete;
					this->queue[sound].sample = s;
					return ng::SoundComplete;
				}
			}
			break;
			
		} case ng::SoundLoop: {
			for (int i=0; i < this->samples; i++) {
				this->buffer[i] = ng::mix_dB(this->buffer[i], clip->buffer[s]);
				s++;
				if (s == clip->samples) {
					s = 0;
				}
			}
			break;
		}
	}
	
	this->queue[sound].sample = s;
	return ng::None;
}

// Mix sounds into channel buffer.
void ng::Channel::mix () {
	for (int i=0; i < this->sounds;) {
		if (this->mix_sound(i) == ng::SoundComplete) {
			this->remove_sound(i);
		} else {
			i++;
		}
	}
}

// Open audio device in a paused state and set playing to false.
void ng::Audio::init () {
	this->buffer = NULL;
	this->samples = 0;
	this->volume = 1.0;
	this->playing = false;
	
	SDL_AudioSpec desired, obtained;
	desired.freq = 44100;
	desired.format = AUDIO_F32SYS;
	desired.samples = 4096;
	desired.channels = 2;
	desired.callback = NULL;
	int allowed_changes =
		static_cast<int>(SDL_AUDIO_ALLOW_FREQUENCY_CHANGE) |
		static_cast<int>(SDL_AUDIO_ALLOW_CHANNELS_CHANGE) |
		static_cast<int>(SDL_AUDIO_ALLOW_SAMPLES_CHANGE);
	this->device = SDL_OpenAudioDevice(NULL, 0, &desired, &obtained, allowed_changes);
	if (this->device == 0) {
		throw std::runtime_error(SDL_GetError());
	}
	
	this->spec = obtained;
}

// Free buffer and close audio device.
void ng::Audio::quit () {
	this->playing = false;
	this->samples = 0;
	if (this->buffer!= NULL) {
		std::free(this->buffer);
		this->buffer = NULL;
	}
	SDL_ClearQueuedAudio(this->device);
	SDL_CloseAudioDevice(this->device);
	this->device = 0;
}

// Allocate at least ms of samples for buffer and fill with silence.
void ng::Audio::clear (int ms) {
	int queue_bytes, queue_samples;
	// If playing is false, then does not check audio device.
	if (this->playing) {
		queue_bytes = static_cast<int>(SDL_GetQueuedAudioSize(this->device));
		queue_samples = queue_bytes / sizeof(float);
	} else {
		queue_bytes = 0;
		queue_samples = 0;
	}
	
	int chunk_samples, samples_per_ms, samples;
	chunk_samples = this->spec.samples * this->spec.channels;
	samples_per_ms = this->spec.freq / 1000;
	// If ms == 0, allocates 1 chunk of (spec.samples * spec.channels) samples.
	if (ms > 0) {
		samples = ms * samples_per_ms;
	} else {
		samples = chunk_samples;
	}
	// If the audio device contains more samples than ms would create, then
	// sets samples = 0 and does nothing to buffer.
	if (queue_samples >= samples) {
		this->samples = 0;
		return;
	}
	
	// Samples is a multiple of (spec.samples * spec.channels) chunks, and
	// takes into account the number of samples already in audio device.
	samples -= queue_samples;
	int chunks = (samples / chunk_samples) + 1;
	samples = chunks * chunk_samples;
	
	this->buffer = static_cast<float*>(std::realloc(this->buffer, samples * sizeof(float)));
	this->samples = samples;
	for (int i=0; i < samples; i++) {
		this->buffer[i] = ng::dB_silence();
	}
}

// Clear channel, mix sounds, and mix channel buffer.
void ng::Audio::mix_channel (Channel* c) {
	// Does nothing if samples == 0.
	if (this->samples == 0) {
		return;
	}
	
	c->clear(this->samples); // Channel samples = samples.
	c->mix();
	
	float dv = ng::dB_volume(c->volume);
	for (int i=0; i < this->samples; i++) {
		c->buffer[i] *= dv;
		this->buffer[i] = ng::mix_dB(this->buffer[i], c->buffer[i] * dv);
	}
}

// Send buffer to audio device and set playing to true.
void ng::Audio::play () {
	// Does nothing if samples == 0.
	if (this->samples == 0) {
		return;
	}
	
	// Send buffer in chunks of spec.samples * spec.channels.
	int chunk_samples, chunks, chunk_bytes;
	chunk_samples = static_cast<int>(this->spec.samples) *
		static_cast<int>(this->spec.channels);
	chunks = this->samples / chunk_samples;
	chunk_bytes = chunk_samples * sizeof(float);
	
	float dv = ng::dB_volume(this->volume);
	float* chunk = static_cast<float*>(std::malloc(chunk_bytes));
	for (int i=0; i < chunks; i++) {
		for (int f=0; f < chunk_samples; f++) {
			chunk[f] = this->buffer[(i * chunk_samples) + f] * dv;
		}
		int result = SDL_QueueAudio(this->device, chunk, static_cast<uint32_t>(chunk_bytes));
		if (result != 0) {
			throw std::runtime_error(SDL_GetError());
		}
	}
	std::free(chunk);
	
	// The first call to play sets playing to true and unpauses audio device.
	if (!this->playing) {
		SDL_PauseAudioDevice(this->device, 0); // unpause audio device
		this->playing = true;
	}
}


