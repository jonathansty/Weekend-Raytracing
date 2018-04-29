#include "stdafx.h"
#include "Vec3.h"
#include "Ray.h"
#include "Hitable.h"
#include "Sphere.h"

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
