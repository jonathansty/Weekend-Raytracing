#include "stdafx.h"
#include "Noise.h"

using namespace Math;

float3* PerlinNoise::m_RanFloat = PerlinNoise::PerlinGenerate();
std::array<int,256>  PerlinNoise::m_PermX = PerlinNoise::PerlinGeneratePerm();
std::array<int,256>  PerlinNoise::m_PermY = PerlinNoise::PerlinGeneratePerm();
std::array<int,256>  PerlinNoise::m_PermZ = PerlinNoise::PerlinGeneratePerm();



float Math::PerlinNoise::noise(const float3& p) const
{
	using namespace hlslpp;
	float u = p.x - std::floor(p.x);
	float v = p.y - std::floor(p.y);
	float w = p.z - std::floor(p.z);

	//u = u * u*(3 - 2 * u);
	//v = v * v*(3 - 2 * v);
	//w = w * w*(3 - 2 * w);

	int i = int(std::floor(p.x));
	int j = int(std::floor(p.y));
	int k = int(std::floor(p.z));

	float3 c[2][2][2];
	for (int di = 0; di < 2; ++di)
	{
		for (int dj = 0; dj < 2; ++dj)
		{
			for (int dk = 0; dk < 2; ++dk)
			{
				int x = ( i + di ) & 255;
				int y = ( j + dj ) & 255;
				int z = ( k + dk ) & 255;
				c[di][dj][dk] = m_RanFloat[
						m_PermX[x] ^
						m_PermY[y] ^
						m_PermZ[z]
				];
			}
		}
	}

	return TrilinearInterp(c, u, v, w);
}

float Math::PerlinNoise::turb(const float3& p, int depth /*= 7*/) const
{
	float accum = 0;
	float3 temp_p = p;
	float weight = 1.0;
	for (int i = 0; i < depth; i++) {
		accum += weight * noise(temp_p);
		weight *= 0.5;
		temp_p *= 2;
	}
	return fabs(accum);
}

float3* Math::PerlinNoise::PerlinGenerate()
{
	float3* p = new float3[256];
	for (int i = 0; i < 256; ++i)
	{
		float3 v = float3(Random::Range(-1.0f,1.0f), Random::Range(-1.0f,1.0f), Random::Range(-1.0f,1.0f));
		p[i] = v / hlslpp::length(v);
	}

	return p;
}

void Math::PerlinNoise::Permute(std::array<int,256> p, int n)
{
	for (int i = n - 1; i > 0; --i)
	{
		int target = int(Random::Value() * (i + 1));
		int tmp = p[i];
		p[i] = p[target];
		p[target] = tmp;
	}
}

std::array<int,256> Math::PerlinNoise::PerlinGeneratePerm()
{
	std::array<int, 256> arr;
	for (int i = 0; i < 256; ++i)
		arr[i] = i;

	Permute(arr, 256);
	return arr;
}

float Math::TrilinearInterp(float3 c[2][2][2], float u, float v, float w)
{
	float uu = u * u *(3 - 2 * u);
	float vv = v * v *(3 - 2 * v);
	float ww = w * w *(3 - 2 * w);

	float accum = 0;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				float3 weight_v{ u - i, v - j, w - k };
				float3 cv =c[i][j][k];

				float moveV = (i*uu + (1 - i)*(1 - uu))*
							  (j*vv + (1 - j)*(1 - vv))*
						 	  (k*ww + (1 - k)*(1 - ww));

				accum += moveV * dot(c[i][j][k], weight_v);
			}
		}
	}
	return fabs(accum);
}
