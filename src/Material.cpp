#include "stdafx.h"
#include "Material.h"

bool Lambertian::Scatter(const Ray& rin, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const
{
	Vec3 target = rec.p + rec.normal + Random::RandomUnitSphere();
	scattered = Ray(rec.p, target - rec.p);
	attenuation = m_Albedo;
	return true;
}

Vec3 Random::RandomUnitSphere()
{
	auto d = std::uniform_real_distribution<float>(-1.0f, 1.0f);
	Vec3 p;
	do
	{
		p = Vec3(d(g_mt), d(g_mt), d(g_mt));
	} while (p.LengthSquared() >= 1.0);
	return p;
}

Vec3 Random::RandomUnitDisk()
{
	auto d = std::uniform_real_distribution<float>(-1.0f, 1.0f);
	Vec3 p;
	do
	{
		p = Vec3(d(g_mt), d(g_mt), 0.0f);
	} while (dot(p,p) >= 1.0);
	return p;
}

float Random::Range(float a, float b)
{
	auto d = std::uniform_real_distribution<float>(a, b);
	return d(g_mt);
}

Vec3 Reflect(const Vec3& v, const Vec3& n)
{
	// The reflection is the incoming v minus 2 times the length from the end point of V to the surface.
	return v - 2 * dot(v, n) * n;
}

// Refract according to snells law
bool Refract(const Vec3& v, const Vec3& n, float NiOverNt, Vec3& refracted)
{
	Vec3 uv = UnitVector(v);
	float dt = dot(uv, n);
	float d = 1.0f - NiOverNt * NiOverNt*(1 - dt*dt);
	if (d > 0)
	{
		refracted = NiOverNt * (uv - n * dt) - n * sqrt(d);
		return true;
	}
	else
		return false;
}

float Schlick(float cosine, float RefIdx)
{
	float r0 = (1 - RefIdx) / (1 + RefIdx);
	r0 = r0 * r0;
	return r0 + (1 - r0)*pow((1 - cosine), 5);
}

bool Metal::Scatter(const Ray& rin, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const
{
	Vec3 reflected = Reflect(UnitVector(rin.Direction()), rec.normal);
	scattered = Ray(rec.p, reflected + m_Fuzz * Random::RandomUnitSphere());
	attenuation = m_Alberto;
	// Just making sure we've got a proper ray
	return (dot(scattered.Direction(), rec.normal) > 0);
}

bool Dielectric::Scatter(const Ray& rin, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const
{
	Vec3 outwardNormal;
	Vec3 Reflected = Reflect(rin.Direction(), rec.normal);
	float NiOverNt;
	attenuation = Vec3(1.f,1.f,1.f);

	Vec3 Refracted;
	float ReflectProb;
	float Cosine;
	if (dot(rin.Direction(), rec.normal) > 0) 
	{
		outwardNormal = -rec.normal;
		NiOverNt = m_RefIdx;
		Cosine = m_RefIdx * dot(rin.Direction(), rec.normal) / rin.Direction().Length();
	}
	else
	{
		outwardNormal = rec.normal;
		NiOverNt = 1.0f / m_RefIdx;
		Cosine =  -dot(rin.Direction(), rec.normal) / rin.Direction().Length();
	}
	
	if (Refract(rin.Direction(), outwardNormal, NiOverNt, Refracted))
	{
		ReflectProb = Schlick(Cosine, m_RefIdx);
	}
	else
	{
		ReflectProb = 1.0f;
	}

	if (Random::Range(0.0f, 1.0f) < ReflectProb)
	{
		scattered = Ray(rec.p, Reflected);
	}
	else
	{
		scattered = Ray(rec.p, Refracted);
	}

	return true;

}
