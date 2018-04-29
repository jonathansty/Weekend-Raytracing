#pragma once
#include "Vec3.h"
class Ray
{
public:
	Ray();

	Ray(const float3& a, const float3& b)
		: m_A(a)
		, m_B(b)
	{

	}

	~Ray();


	const float3& Origin() const { return m_A; }
	const float3& Direction() const { return m_B; }
	float3 PointAtParameter(float t) const { return m_A + t * m_B; }


	float3 m_A;
	float3 m_B;
};

