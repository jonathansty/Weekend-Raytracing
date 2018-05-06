#include "stdafx.h"
#include "Vec3.h"
#include "Ray.h"
#include "Hitable.h"
#include "HitableList.h"
#include "aabb.h"

bool HitableList::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
	HitRecord tmp{};
	bool bHitAnything = false;;
	float ClosestSoFar = t_max;

	for (uint32_t i = 0; i < m_ListSize; ++i)
	{
		if (m_List[i]->Hit(r, t_min, ClosestSoFar, tmp))
		{
			bHitAnything = true;
			ClosestSoFar = tmp.t;
			rec = tmp;
		}
	}

	return bHitAnything;
}

bool HitableList::BoundingBox(float t0, float t1, Math::AABB& box) const
{
	using namespace Math;

	if (m_ListSize < 1) return false;
	AABB tmp{};
	bool firstTrue = m_List[0]->BoundingBox(t0, t1, tmp);
	if (!firstTrue)
		return false;
	else
		box = tmp;

	for (int i = 1; i < m_ListSize; ++i)
	{
		if (m_List[i]->BoundingBox(t0, t1, tmp))
		{
			box = SurroundingBox(box, tmp);
		}
		else
			return false;
	}

	return true;
}
