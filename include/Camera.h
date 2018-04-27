#pragma once

#include "Ray.h"
#include "Material.h"

class Camera
{
public:
	Camera(Vec3 eye, Vec3 lookat, Vec3 vup, float vfov, float aspect, float aperture, float focus_dist)
	{
		float theta = float(vfov*M_PI / 180.0);
		float half_height = tan(theta / 2.0f);
		float half_width = aspect * half_height;

		m_LensRadius = aperture / 2;

		m_Origin = eye;
		m_W = UnitVector(eye - lookat);
		m_U = UnitVector(cross(vup, m_W));
		m_V = cross(m_W, m_U);

		//m_LowerLeftCorner = Vec3(-half_width, -half_height, -1.0);
		m_LowerLeftCorner = m_Origin - (half_width*focus_dist * m_U) - (half_height*focus_dist * m_V ) - m_W*focus_dist;
		m_Horizontal = 2*half_width*focus_dist*m_U;
		m_Vertical = 2*half_height*focus_dist*m_V;
	}

	Ray GetRay(float u, float v){ 
		Vec3 rd = m_LensRadius * Random::RandomUnitDisk();
		Vec3 offset = m_U * rd.x() + m_V * rd.y();
		return Ray(m_Origin + offset, m_LowerLeftCorner + u * m_Horizontal + v * m_Vertical - m_Origin - offset); 
	};

	float m_LensRadius;
	Vec3 m_U, m_V, m_W;
	Vec3 m_Origin;
	Vec3 m_LowerLeftCorner;
	Vec3 m_Horizontal;
	Vec3 m_Vertical;
};