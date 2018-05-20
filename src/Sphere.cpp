#include "stdafx.h"
#include "Vec3.h"
#include "Ray.h"
#include "Hitable.h"
#include "Sphere.h"
#include "aabb.h"
#include "Material.h"

Sphere::~Sphere()
{
	delete m_Material;
	m_Material = nullptr;
}

bool Sphere::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
	float3 oc = r.Origin() - m_Center;
	float a = dot(r.Direction(), r.Direction());
	float b = dot(oc, r.Direction());
	float c = dot(oc, oc) - m_Radius * m_Radius;

	float discriminant = b * b - a*c;
	if (discriminant > 0)
	{
		float sqr = sqrt(discriminant);
		float X1 = (-b - sqr) / (a);
		if (X1 < t_max && X1 > t_min)
		{
			rec.t = X1;
			rec.p = r.PointAtParameter(X1);
			// Normalized normal
			rec.normal = (rec.p - m_Center) / m_Radius;
			rec.material = m_Material;
			return true;
		}

		X1 = (-b + sqr) / (a);
		if (X1 < t_max && X1 > t_min)
		{
			rec.t = X1;
			rec.p = r.PointAtParameter(X1);
			// Normalized normal
			rec.normal = (rec.p - m_Center) / m_Radius;
			rec.material = m_Material;
			return true;
		}
	}
	return false;
}

bool Sphere::BoundingBox(float t0, float t1, Math::AABB& box) const
{
	box = Math::AABB(
			m_Center - float3(m_Radius, m_Radius, m_Radius), 
			m_Center + float3(m_Radius, m_Radius, m_Radius)
		);
	return true;
}

bool MovingSphere::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
	float3 oc = r.Origin() - Center(r.Time());
	float a = dot(r.Direction(), r.Direction());
	float b = dot(oc, r.Direction());
	float c = dot(oc, oc) - m_Radius * m_Radius;

	float discriminant = b * b - a*c;
	if (discriminant > 0)
	{
		float sqr = sqrt(discriminant);
		float X1 = (-b - sqr) / (a);
		if (X1 < t_max && X1 > t_min)
		{
			rec.t = X1;
			rec.p = r.PointAtParameter(X1);
			// Normalized normal
			rec.normal = (rec.p - Center(r.Time())) / m_Radius;
			rec.material = m_Material;
			return true;
		}

		X1 = (-b + sqr) / (a);
		if (X1 < t_max && X1 > t_min)
		{
			rec.t = X1;
			rec.p = r.PointAtParameter(X1);
			// Normalized normal
			rec.normal = (rec.p - Center(r.Time())) / m_Radius;
			rec.material = m_Material;
			return true;
		}
	}
	return false;
}

bool MovingSphere::BoundingBox(float t0, float t1, Math::AABB& box) const
{
	box = SurroundingBox(
		Math::AABB(Center(t0) - float3(m_Radius, m_Radius, m_Radius),Center(t0) + float3(m_Radius, m_Radius, m_Radius)),
		Math::AABB(Center(t1) - float3(m_Radius, m_Radius, m_Radius), Center(t1) + float3(m_Radius, m_Radius, m_Radius)));
	return true;
}
