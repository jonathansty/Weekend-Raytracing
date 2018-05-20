#pragma once
#include "Ray.h"
namespace Math
{
	class AABB;
}

struct HitRecord 
{
	float t;
	hlslpp::float3 p;
	hlslpp::float3 normal;
	hlslpp::float2 uv;
	class Material* material;
};

class IHitable
{
public:
	virtual ~IHitable() {};
	virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
	virtual bool BoundingBox(float t0, float t1, Math::AABB& box) const = 0;

};
