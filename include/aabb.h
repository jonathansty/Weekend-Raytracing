#pragma once
#include "Hitable.h"

namespace Math
{


	inline float ffmin(float a, float b) { return (a > b) ? b : a; }
	inline float ffmax(float a, float b) { return (a > b) ? a : b; }

	class AABB
	{
	public:
		AABB() {}

		AABB(const float3& a, const float3& b)
			: m_Min(a)
			, m_Max(b)
		{
		}

		float3 Min() const { return m_Min; }
		float3 Max() const { return m_Max; }

		bool Hit(const Ray& r, float tmin, float tmax) const;

	private:
		float3 m_Min;
		float3 m_Max;
	};

	AABB SurroundingBox(const AABB& box0, const AABB& box1);

	class BVHNode : public IHitable
	{
	public:
		BVHNode() {}
		BVHNode(std::vector<IHitable*> l, float t0, float t1);

		IHitable* m_Left;
		IHitable* m_Right;
		AABB m_Box;

		virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;
		virtual bool BoundingBox(float t0, float t1, Math::AABB& box) const override;

	};

}
