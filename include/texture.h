#pragma once

class Texture
{
public:
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



