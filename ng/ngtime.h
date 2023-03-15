
#ifndef NGTIME_H
#define NGTIME_H

#include "ngcore.h"

namespace ng {

	class Time {
	public:
		int64_t ticks; // Ticks since program start.
		int delta; // Duration of this tick, in ms. Starts at 10.
		int max; // Duration of longest tick since program start.
		int tps; // Average ticks per second. Starts at 100.
		
		// Internal timestamps, to calculate delta.
		uint32_t now;
		uint32_t last;
		
		// Internal counts, to calculate tps.
		int count;
		int ms;
		
		void init ();
		void tick ();
	};

}

#endif


