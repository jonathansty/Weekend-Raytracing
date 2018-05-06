#include "stdafx.h"


float3 Random::RandomUnitSphere()
{
	auto d = std::uniform_real_distribution<float>(-1.0f, 1.0f);
	float3 p;
	do
	{
		p = float3(d(g_mt), d(g_mt), d(g_mt));
	} while (hlslpp::dot(p,p) >= 1.0f);
	return p;
}

float3 Random::RandomUnitDisk()
{
	auto d = std::uniform_real_distribution<float>(-1.0f, 1.0f);
	float3 p;
	do
	{
		p = float3(d(g_mt), d(g_mt), 0.0f);
	} while (hlslpp::dot(p,p) >= 1.0f);
	return p;
}

float Random::Range(float a, float b)
{
	auto d = std::uniform_real_distribution<float>(a, b);
	return d(g_mt);
}

float Random::Value()
{
	return Range(0.f, 1.f);
}


