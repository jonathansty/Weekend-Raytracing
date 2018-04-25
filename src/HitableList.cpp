#include "stdafx.h"
#include "Vec3.h"
#include "Ray.h"
#include "Hitable.h"
#include "HitableList.h"

bool HitableList::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
	HitRecord tmp{};
	bool bHitAnything = false;;
	double ClosestSoFar = t_max;

	for (uint32_t i = 0; i < m_ListSize; ++i)
	{
		if (m_List[i]->Hit(r, t_min, ClosestSoFar, tmp))
		{
			bHitAnything = true;
			ClosestSoFar = rec.t;
			rec = tmp;
		}
	}

	return bHitAnything;
}
