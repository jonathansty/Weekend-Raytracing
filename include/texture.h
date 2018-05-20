#pragma once
#include "Noise.h"

class Texture
{
public:
	Texture() {}
	virtual ~Texture() {}
	virtual hlslpp::float3 Value(const hlslpp::float2& uv, const hlslpp::float3& p) const = 0;

};

class ConstantTexture : public Texture
{
public:
	ConstantTexture(const float3& albedo) 
		: m_Albedo(albedo)
	{

	}
	ConstantTexture() {}

	virtual hlslpp::float3 Value(const hlslpp::float2& uv, const hlslpp::float3& p) const override;

private:
	float3 m_Albedo;

};

class CheckerTexture : public Texture
{
public:
	CheckerTexture(Texture* even, Texture* odd) 
		: m_evenAlbedo(even)
		, m_oddAlbedo(odd)
	{

	}

	virtual hlslpp::float3 Value(const hlslpp::float2& uv, const hlslpp::float3& p) const override;

private:
	Texture* m_evenAlbedo;
	Texture* m_oddAlbedo;
};

class NoiseTexture : public Texture
{
public:
	NoiseTexture(const float3& scale) : m_Scale(scale) {};
	virtual hlslpp::float3 Value(const hlslpp::float2& uv, const hlslpp::float3& pos) const override;

private:
	float3 m_Scale;
	Math::PerlinNoise m_noise;
};


