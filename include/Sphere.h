#pragma once

class Sphere : public IHitable
{
public:

	Sphere() {}
	Sphere(float3 Center, float radius, class Material* material)
	: m_Center(Center)
	, m_Radius(radius)
	, m_Material(material)
	{
	}

	float3 m_Center;
	float m_Radius;
	class Material* m_Material;

	virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;

};
