#pragma once

/* Generates a random point in the unit sphere using a mt and uniform real distribution */
namespace Random
{
	// I'm dumb when doing random generations. We need to always use the same one that got seeded else we'll get the same random during our generation.
	static std::mt19937_64 g_mt = std::mt19937_64(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	float3 RandomUnitSphere();
	float3 RandomUnitDisk();

	float Range(float a, float b);

	float Value();
}


