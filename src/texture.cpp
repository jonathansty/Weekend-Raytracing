#include "stdafx.h"

#include "texture.h"



hlslpp::float3 ConstantTexture::Value(const hlslpp::float2& uv, const hlslpp::float3& p) const
{
	return m_Albedo;
}

hlslpp::float3 CheckerTexture::Value(const hlslpp::float2& uv, const hlslpp::float3& p) const
{
	float sines = sin(10 * p.x) * sin(10 * p.y) * sin(10 * p.z);
	if (sines < 0)
		return m_evenAlbedo->Value(uv, p);
	else
		return m_oddAlbedo->Value(uv, p);
}

float3 NoiseTexture::Value(const hlslpp::float2& uv, const float3& pos) const
{
	return float3(1, 1, 1)*m_noise.noise(pos*m_Scale);

}
