#include "stdafx.h"
#include "DiffuseLight.h"

#include "texture.h"

float3 DiffuseLight::Emitted(float u, float v, const float3& p) const
{
	return m_Emit->Value(hlslpp::float2{u, v}, p);
}

bool DiffuseLight::Scatter(const Ray& rin, const HitRecord& rec, float3& attenuation, Ray& scattered) const
{
	attenuation = { 0,0,0 };
	return false;
}
