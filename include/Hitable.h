#pragma once

namespace Math
{
	class AABB;
}
class Material;
struct HitRecord 
{
	float t;
	float3 p;
	float3 normal;
	Material* material;
};

class IHitable
{
public:
	virtual ~IHitable() {};
	virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
	virtual bool BoundingBox(float t0, float t1, Math::AABB& box) const = 0;

};