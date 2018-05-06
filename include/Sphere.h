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

	~Sphere();

	float3 m_Center;
	float m_Radius;
	class Material* m_Material;

	virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;
	virtual bool BoundingBox(float t0, float t1, Math::AABB& box) const override;

};

class MovingSphere : public Sphere
{
public:
	MovingSphere(float time0, float time1, float3 center0, float3 center1, float r, class Material* mat)
		: Sphere(float3(0,0,0), r,mat)
		, m_Center0(center0)
		, m_Center1(center1)
		, m_Time0(time0)
		, m_Time1(time1)
	{

	}
	~MovingSphere(){}

	float3 Center(float time) const { 
		float dt = (time - m_Time0) / (m_Time1 - m_Time0);
		return hlslpp::lerp(m_Center0, m_Center1, dt); 
	}

	virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rex) const override;

	virtual bool BoundingBox(float t0, float t1, Math::AABB& box) const override;
private:
	float3 m_Center0;
	float3 m_Center1;
	
	float m_Time0;
	float m_Time1;

};
