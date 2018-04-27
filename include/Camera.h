#pragma once

#include "Ray.h"
class Camera
{
public:
	Camera(Vec3 eye, Vec3 lookat, Vec3 vup, float vfov, float aspect)
	{
		Vec3 u, v, w;
		float theta = float(vfov*M_PI / 180.0);
		float half_height = tan(theta / 2.0f);
		float half_width = aspect * half_height;

		m_Origin = eye;
		w = UnitVector(eye - lookat);
		u = UnitVector(cross(vup, w));
		v = cross(w, u);

		//m_LowerLeftCorner = Vec3(-half_width, -half_height, -1.0);
		m_LowerLeftCorner = m_Origin - (half_width * u) - (half_height * v ) - w;
		m_Horizontal = 2*half_width*u;
		m_Vertical = 2*half_height*v;
	}

	Ray GetRay(float u, float v){ return Ray(m_Origin, m_LowerLeftCorner + u * m_Horizontal + v * m_Vertical - m_Origin); };

	Vec3 m_Origin;
	Vec3 m_LowerLeftCorner;
	Vec3 m_Horizontal;
	Vec3 m_Vertical;
};