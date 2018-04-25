#pragma once

#include "Ray.h"
class Camera
{
public:
	Camera()
		// Z is in the screen
		: m_LowerLeftCorner(-2.0f, -1.0f, -1.0f)
		, m_Horizontal(4.f, 0.f, 0.f)
		, m_Vertical(0.f, 2.f, 0.f)
		, m_Origin(0.0, 0.0, 0.0)
	{
	}

	Ray GetRay(float u, float v){return Ray(m_Origin, m_LowerLeftCorner + u * m_Horizontal + v * m_Vertical);};

	Vec3 m_Origin;
	Vec3 m_LowerLeftCorner;
	Vec3 m_Horizontal;
	Vec3 m_Vertical;
};