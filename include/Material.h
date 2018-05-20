// A material class
#pragma once
#include "Ray.h"
#include "Hitable.h"
#include "Random.h"

class Texture;

class Material
{
public:
	Material() {}
	virtual ~Material() {}

	virtual bool Scatter(const Ray& rin, const HitRecord& rec, float3& attenuation, Ray& scattered) const = 0;
	virtual float3 Emitted(float u, float v, const float3& p) const { return float3{ 0,0,0 }; }
};

class Lambertian : public Material
{
public:
	Lambertian(Texture* inTexture) : m_Texture(inTexture) {}
	~Lambertian();

	virtual bool Scatter(const Ray& rin, const HitRecord& rec, float3& attenuation, Ray& scattered) const override;


	Texture* m_Texture;
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


