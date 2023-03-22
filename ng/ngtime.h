
#ifndef NGTIME_H
#define NGTIME_H

#include "ngcore.h"

namespace ng {
	
	// Pause for at least 1 millisecond (ms).
	// Returns ms since program start (might overflow).
	// 'last' is the value returned from previous call to tick(), or 0.
	uint32_t tick (uint32_t last);
	
	// Calculate ms time difference between 'now' and 'last', regardless of overflow.
	// Call tick() to get 'now' before calling delta().
	int delta (uint32_t now, uint32_t last);
	
	// Calculate ticks per second (tps), given:
	//  - accummulated ticks and ms this second.
	//  - delta ms this tick.
	// Designed to be called every tick.
	// acc_ticks and acc_ms reset to 0 when tps is re-calculated each second.
	int tps (int tps, int delta, int* acc_ticks, int* acc_ms);

	class Time {
	public:
		// Internal
		uint32_t now; // Time ms since program start.
		uint32_t last; // Previous value of 'now'.
		int acc_ticks; // Ticks since previous tps calculation.
		int acc_ms; // Time ms since previous tps calculation.
		
		// Public
		int64_t ticks; // Ticks since program start.
		int delta; // Duration of this tick, in ms. Starts at 10.
		int tps; // Average ticks per second. Starts at 100.
		int max; // Duration of longest tick since program start.
		
		void init ();
		void tick ();
	};

}

#endif


