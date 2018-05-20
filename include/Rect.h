#pragma once
#include "Hitable.h"
#include "Ray.h"

class Material;
class XYRect : public IHitable
{
public:
	XYRect() {}
	XYRect(float x0, float x1, float y0, float y1, float k, Material* mat)
		: m_x0(x0)
		, m_x1(x1)
		, m_y0(y0)
		, m_y1(y1)
		, m_k(k)
		, m_Material(mat)
	{

	}

	float m_x0, m_x1, m_y0, m_y1, m_k;
	Material* m_Material;


	virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;

	virtual bool BoundingBox(float t0, float t1, Math::AABB& box) const override;

};