
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#ifndef NGAUDIO_H
#define NGAUDIO_H

#include "ngcore.h"

namespace ng {

	enum EnumSound {
		SoundPlayOnce = 1,
		SoundLoop = 2,
		SoundComplete = 3
	};
	
	class Clip {
	public:
		SDL_AudioSpec spec;
		float* buffer;
		int samples;
		
		// Load .wav file into buffer, with same spec as audio device.
		void init (Audio*, const char* file);
		
		// Free buffer.
		void quit ();
	};
	
	class Sound {
	public:
		Clip* clip;
		int sample;
		int mode;
		
		// Internal. Called by channel::add_sound.
		// Initialize a sound pointing to the start of clip, with EnumSound mode.
		void init (Clip*, int mode);
	};
	
	class Channel {
	public:
		Sound* queue;
		int sounds;
		float* buffer;
		int samples;
		float volume;
		
		// Initialize sound queue and sample buffer to 0.
		void init ();
		
		// Free queue and buffer.
		void quit ();
		
		// Queue a sound with EnumSound mode.
		void play_sound (Clip*, int mode);
		
		// Internal. Called by mix.
		// Remove queued sound.
		void remove_sound (int sound);
		
		// Remove all queued sounds.
		void stop ();
		
		// Internal. Called by audio::mix_channel.
		// Allocate samples for buffer and fill with silence.
		void clear (int samples);
		
		// Internal. Called by mix.
		// Mix samples from sound clip into channel buffer.
		int mix_sound (int sound);
		
		// Internal. Called by audio::mix_channel.
		// Mix sounds into channel buffer.
		void mix ();
	};
	
	class Audio {
	public:
		SDL_AudioDeviceID device;
		SDL_AudioSpec spec;
		float* buffer;
		int samples;
		float volume;
		bool playing;
		
		// Open audio device in a paused state and set playing to false.
		void init ();
		
		// Free buffer and close audio device.
		void quit ();
		
		// Allocate at least ms of samples for buffer and fill with silence.
		void clear (int ms);
		
		// Clear channel, mix sounds, and mix channel buffer.
		void mix_channel (Channel*);
		
		// Send buffer to audio device and set playing to true.
		void play ();
	};

}

#endif

