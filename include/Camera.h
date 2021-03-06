#pragma once

#include "Ray.h"
#include "Material.h"

class Camera
{
public:
	Camera(float3 eye, float3 lookat, float3 vup, float vfov, float aspect, float aperture, float focus_dist, float time0, float time1)
		: m_Time0(time0)
		, m_Time1(time1)
	{
		float theta = float(vfov*M_PI / 180.0);
		float half_height = tan(theta / 2.0f);
		float half_width = aspect * half_height;

		m_LensRadius = aperture / 2;

		m_Origin = eye;
		m_W = hlslpp::normalize(eye - lookat);
		m_U = hlslpp::normalize(hlslpp::cross(vup, m_W));
		m_V = hlslpp::cross(m_W, m_U);

		//m_LowerLeftCorner = Vec3(-half_width, -half_height, -1.0);
		m_LowerLeftCorner = m_Origin - (half_width*focus_dist * m_U) - (half_height*focus_dist * m_V ) - m_W*focus_dist;
		m_Horizontal = 2*half_width*focus_dist*m_U;
		m_Vertical = 2*half_height*focus_dist*m_V;
	}

	Ray GetRay(float u, float v){ 
		float3 rd = m_LensRadius * Random::RandomUnitDisk();
		float3 offset = m_U * rd.x + m_V * rd.y;
		float time = m_Time0 + Random::Range(0.f, 1.f) * (m_Time1 - m_Time0);
		return Ray(m_Origin + offset, m_LowerLeftCorner + u * m_Horizontal + v * m_Vertical - m_Origin - offset, time); 
	};

	float m_LensRadius;
	float3 m_U, m_V, m_W;
	float3 m_Origin;
	float3 m_LowerLeftCorner;
	float3 m_Horizontal;
	float3 m_Vertical;
	
	float m_Time0;
	float m_Time1;
};
