#pragma once
#include <random>

namespace wrap
{
	inline void seedRandom(int seed) { srand(seed); }
	
	inline int random() { return rand(); }
	inline int random(int max) { return random() % max; }
	inline int random(int min, int max) { return min + random() % ((max - min) + 1); }

	inline float randomf() { return rand() / (float)RAND_MAX; }
	inline float randomf(float max) { return randomf() * max; }
	inline float randomf(int min, int max) { return min + randomf((float)max - (float)min); }

}