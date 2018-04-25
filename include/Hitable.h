#pragma once

struct HitRecord 
{
	float t;
	Vec3 p;
	Vec3 normal;
};

class IHitable
{
public:
	virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;

};