
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
		std::vector<float> buffer;
		
		Clip ();
		~Clip ();
		
		// Load .wav file into buffer, with same spec as audio device.
		void load (Audio*, const char* file);
	};
	
	class Sound {
	public:
		Clip* clip;
		size_t sample;
		int mode;
		
		Sound ();
		~Sound ();
		
		// Internal. Called by channel::add_sound.
		// Initialize a sound pointing to the start of clip, with EnumSound mode.
		void set (Clip*, int mode);
	};
	
	class Channel {
	public:
		std::vector<Sound> queue;
		//size_t sounds;
		std::vector<float> buffer;
		//size_t samples;
		float volume;
		
		Channel ();
		~Channel ();
		
		// Queue a sound with EnumSound mode.
		void play_sound (Clip*, int mode);
		
		// Internal. Called by mix.
		// Remove queued sound.
		void remove_sound (size_t sound);
		
		// Remove all queued sounds.
		void stop ();
		
		// Internal. Called by audio::mix_channel.
		// Allocate samples for buffer and fill with silence.
		void clear (size_t samples);
		
		// Internal. Called by mix.
		// Mix samples from sound clip into channel buffer.
		int mix_sound (size_t sound);
		
		// Internal. Called by audio::mix_channel.
		// Mix sounds into channel buffer.
		void mix ();
	};
	
	class Audio {
	public:
		SDL_AudioDeviceID device;
		SDL_AudioSpec spec;
		std::vector<float> buffer;
		//size_t samples;
		float volume;
		bool playing;
		
		Audio ();
		~Audio ();
		
		// Open audio device in a paused state.
		void open ();
		
		// Close audio device.
		void close ();
		
		// Allocate at least ms of samples for buffer and fill with silence.
		void clear (int ms);
		
		// Clear channel, mix sounds, and mix channel buffer.
		void mix_channel (Channel*);
		
		// Send buffer to audio device and set playing to true.
		void play ();
	};

}

#endif


