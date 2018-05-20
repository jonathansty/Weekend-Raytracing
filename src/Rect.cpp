#include "stdafx.h"
#include "Rect.h"
#include "aabb.h"

bool XYRect::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
	float t = (m_k - r.Origin().z) / r.Direction().z;
	if (t < t_min || t > t_max)
		return false;
	float x = r.Origin().x + t * r.Direction().x;
	float y = r.Origin().y + t * r.Direction().y;
	if (x < m_x0 || x > m_x1 || y < m_y0 || y > m_y1)
		return false;

	rec.uv.x = (x - m_x0) / (m_x1 - m_x0);
	rec.uv.y = (y - m_y0) / (m_y1 - m_y0);
	rec.t = t;
	rec.material = m_Material;
	rec.p = r.PointAtParameter(t);
	rec.normal = float3(0, 0, 1);
	return true;
}

bool XYRect::BoundingBox(float t0, float t1, Math::AABB& box) const
{
	box = Math::AABB({ m_x0,m_y0,m_k - 0.0001f }, { m_x1,m_y1,m_k + 0.0001f });
	return true;
}
