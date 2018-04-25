#include "stdafx.h"
#include "Vec3.h"
#include "Ray.h"
#include "Hitable.h"
#include "Sphere.h"

bool Sphere::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
	Vec3 oc = r.Origin() - m_Center;
	float a = dot(r.Direction(), r.Direction());
	float b = 2.0f * dot(oc, r.Direction());
	float c = dot(oc, oc) - m_Radius * m_Radius;
	float discriminant = b * b - 4 * a*c;
	if (discriminant > 0)
	{
		float tempT = (-b - sqrt(discriminant)) / (2.0f*a);
		if (tempT < t_max && tempT > t_min)
		{
			rec.t = tempT;
			rec.p = r.PointAtParameter(tempT);
			// Normalized normal
			rec.normal = (rec.p - m_Center) / m_Radius;
			return true;
		}
		tempT = (-b + sqrt(discriminant)) / (2.0f*a);
		if (tempT < t_max && tempT > t_min)
		{
			rec.t = tempT;
			rec.p = r.PointAtParameter(tempT);
			// Normalized normal
			rec.normal = (rec.p - m_Center) / m_Radius;
			return true;
		}
	}
	return false;
}
