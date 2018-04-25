#pragma once

class Sphere : public IHitable
{
public:

	Sphere() {}
	Sphere(Vec3 Center, float radius)
	: m_Center(Center)
	, m_Radius(radius)
	{
	}

	Vec3 m_Center;
	float m_Radius;

	virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;

};
