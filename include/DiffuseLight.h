#pragma once
#include "Material.h"

class Texture;
class DiffuseLight : public Material 
{
public:
	DiffuseLight(Texture* texture) : m_Emit(texture) {}

	virtual float3 Emitted(float u, float v, const float3& p) const;

	virtual bool Scatter(const Ray& rin, const HitRecord& rec, float3& attenuation, Ray& scattered) const override;

private:
	Texture * m_Emit;
};
