// A material class
#pragma once
#include <chrono>
#include "Ray.h"
#include "Hitable.h"

class Material
{
public:
	virtual bool Scatter(const Ray& rin, const HitRecord& rec, float3& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material
{
public:
	Lambertian(const float3& a) : m_Albedo(a) {}

	virtual bool Scatter(const Ray& rin, const HitRecord& rec, float3& attenuation, Ray& scattered) const override;

	float3 m_Albedo;
};

class Metal : public Material
{
public:
	Metal(const float3& a,float f) : m_Alberto(a),m_Fuzz(f<1?f:1)
	{}

	virtual bool Scatter(const Ray& rin, const HitRecord& rec, float3& attenuation, Ray& scattered) const override;

	// Mijn naam is alberto!
	float3 m_Alberto;
	float m_Fuzz;


};

class Dielectric : public Material
{
public:
	Dielectric(float ri) : m_RefIdx(ri)
	{}

	virtual bool Scatter(const Ray& rin, const HitRecord& rec, float3& attenuation, Ray& scattered) const override;

	// Mijn naam is alberto!
	float m_RefIdx;


};

/* Generates a random point in the unit sphere using a mt and uniform real distribution */
namespace Random
{
	// I'm dumb when doing random generations. We need to always use the same one that got seeded else we'll get the same random during our generation.
	static std::mt19937_64 g_mt = std::mt19937_64(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	float3 RandomUnitSphere();
	float3 RandomUnitDisk();

	float Range(float a, float b);
}
