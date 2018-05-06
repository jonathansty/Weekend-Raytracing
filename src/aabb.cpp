#include "stdafx.h"
#include "Ray.h"
#include "aabb.h"

bool Math::AABB::Hit(const Ray& r, float tmin, float tmax) const
{
	// TODO: Use optimized code
	for (int i = 0; i < 3; ++i)
	{
		float t0 = Math::ffmin(
			(m_Min._f32[i] - r.Origin()._f32[i]) / r.Direction()._f32[i],
			(m_Max._f32[i] - r.Origin()._f32[i]) / r.Direction()._f32[i]);

		float t1 = Math::ffmax(
			(m_Min._f32[i] - r.Origin()._f32[i]) / r.Direction()._f32[i],
			(m_Max._f32[i] - r.Origin()._f32[i]) / r.Direction()._f32[i]);

		tmin = ffmax(t0, tmin);
		tmax = ffmax(t0, tmax);
		if (tmax <= tmin)
			return false;
	}
	return true;
}
