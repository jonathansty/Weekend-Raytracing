#include "stdafx.h"
#include "Ray.h"
#include "aabb.h"
#include "Random.h"
using namespace Math;


bool AABB::Hit(const Ray& r, float tmin, float tmax) const
{
	// TODO: Use optimized code
	for (int i = 0; i < 3; ++i)
	{
		float t0 = Math::ffmin(
			(m_Min._f32[i] - r.Origin()._f32[i]) / r.Direction()._f32[i],
			(m_Max._f32[i] - r.Origin()._f32[i]) / r.Direction()._f32[i]);

		float t1 = Math::ffmax(
			(m_Min._f32[i] - r.Origin()._f32[i]) / r.Direction()._f32[i],
			(m_Max._f32[i] - r.Origin()._f32[i]) / r.Direction()._f32[i]);

		tmin = ffmax(t0, tmin);
		tmax = ffmax(t0, tmax);
		if (tmax <= tmin)
			return false;
	}
	return true;
}

AABB Math::SurroundingBox(const AABB& box0, const AABB& box1)
{
	float3 small{
		fmin(box0.Min().x, box1.Min().x),
		fmin(box0.Min().y, box1.Min().y),
		fmin(box0.Min().z, box1.Min().z)
	};

	float3 big{
		fmax(box0.Max().x, box1.Max().x),
		fmax(box0.Max().y, box1.Max().y),
		fmax(box0.Max().z, box1.Max().z)
	};

	return AABB(small, big);
}
int box_x_compare(const void* left, const void* right)
{
	IHitable* aleft = *(IHitable**)left;
	IHitable* aright = *(IHitable**)right;


	AABB boxLeft, boxRight;
	if (!aleft->BoundingBox(0, 0, boxLeft) || !aright->BoundingBox(0, 0, boxRight))
		std::cerr << "No Bounding box in box_x_compare\n";

	if (boxLeft.Min().x - boxRight.Min().x < 0.0)
		return -1;

	return 1;
}
int box_y_compare(const void* left, const void* right)
{
	IHitable* aleft = *(IHitable**)left;
	IHitable* aright = *(IHitable**)right;

	AABB boxLeft, boxRight;
	if (!aleft->BoundingBox(0, 0, boxLeft) || !aright->BoundingBox(0, 0, boxRight))
		std::cerr << "No Bounding box in box_x_compare\n";

	if (boxLeft.Min().y - boxRight.Min().y < 0.0)
		return -1;

	return 1;
}
int box_z_compare(const void* left, const void* right)
{
	IHitable* aleft = *(IHitable**)left;
	IHitable* aright = *(IHitable**)right;


	AABB boxLeft, boxRight;
	if (!aleft->BoundingBox(0, 0, boxLeft) || !aright->BoundingBox(0, 0, boxRight))
		std::cerr << "No Bounding box in box_x_compare\n";

	if (boxLeft.Min().z - boxRight.Min().z < 0.0)
		return -1;

	return 1;
}
// BVH NODE
BVHNode::BVHNode(std::vector<IHitable*> l, float t0, float t1)
{
	int axis = int(3 * Random::Value());
	if (axis == 0)
	{
		qsort(l.data(), l.size(),sizeof(IHitable*), box_x_compare);
	}
	else if (axis == 1)
	{
		qsort(l.data(), l.size(),sizeof(IHitable*), box_y_compare);
	}
	else
	{
		qsort(l.data(), l.size(),sizeof(IHitable*), box_z_compare);
	}

	if (l.size() == 1)
	{
		m_Left = m_Right = l[0];
	}
	else if (l.size() == 2)
	{
		m_Left = l[0];
		m_Right = l[1];
	}
	else 
	{
		std::vector<IHitable*> left{ l.begin(), l.begin() + l.size() / 2 };
		std::vector<IHitable*> right{ l.begin() + l.size() / 2, l.end() };
		m_Left = new BVHNode(left, t0, t1);
		m_Right = new BVHNode(right, t0, t1);
	}

	AABB boxLeft, boxRight;
	if ( !m_Left->BoundingBox(t0, t1, boxLeft) 
	  || !m_Right->BoundingBox(t0, t1, boxRight))
	{
		std::cerr << "No bounding box in BVHNode constructor \n";
	}

	m_Box = SurroundingBox(boxLeft, boxRight);
}

bool BVHNode::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
	if (m_Box.Hit(r, t_min, t_max)) 
	{
		HitRecord left, right;
		bool bLeft = m_Left->Hit(r, t_min, t_max, left);
		bool bRight = m_Right->Hit(r, t_min, t_max, right);
		if (bLeft && bRight)
		{
			if (left.t < right.t)
				rec = left;
			else
				rec = right;
			return true;
		}
		else if (bLeft)
		{
			rec = left;
			return true;
		}
		else if (bRight)
		{
			rec = right;
			return true;
		}
		else
			return false;
	}

	return false;
}

bool BVHNode::BoundingBox(float t0, float t1, Math::AABB& box) const
{
	box = m_Box;
	return true;
}

