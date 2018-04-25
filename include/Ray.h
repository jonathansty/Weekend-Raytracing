#pragma once
#include "Vec3.h"
class Ray
{
public:
	Ray();

	Ray(const Vec3& a, const Vec3& b)
		: m_A(a)
		, m_B(b)
	{

	}

	~Ray();


	const Vec3& Origin() const { return m_A; }
	const Vec3& Direction() const { return m_B; }
	Vec3 PointAtParameter(float t) const { return m_A + t * m_B; }


	Vec3 m_A;
	Vec3 m_B;
};

