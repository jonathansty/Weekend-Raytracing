#include "stdafx.h"
#include "Noise.h"

using namespace Math;

float3* PerlinNoise::m_RanFloat = PerlinNoise::PerlinGenerate();
int * PerlinNoise::m_PermX = PerlinNoise::PerlinGeneratePerm();
int * PerlinNoise::m_PermY = PerlinNoise::PerlinGeneratePerm();
int * PerlinNoise::m_PermZ = PerlinNoise::PerlinGeneratePerm();



float Math::PerlinNoise::noise(const float3& p) const
{
	using namespace hlslpp;
	float u, v, w;
	u = p.x;
	v = p.y;
	w = p.z;

	int i = int(std::floor(u));
	int j = int(std::floor(v));
	int k = int(std::floor(w));

	u -= std::floor(u);
	v -= std::floor(v);
	w -= std::floor(w);


	float3 c[2][2][2]{};
	for (int di = 0; di < 2; ++di)
		for (int dj = 0; dj < 2; ++dj)
			for (int dk = 0; dk < 2; ++dk)
				c[di][dj][dk] = m_RanFloat[
					m_PermX[(i + di) & 255] ^
						m_PermY[(j + dj) & 255] ^
						m_PermZ[(k + dk) & 255]
				];

	return PerlinInterp(c, u, v, w);
}

float Math::PerlinInterp(float3 c[2][2][2], float u, float v, float w)
{
	float uu = u * u *(3 - 2 * u);
	float vv = u * u *(3 - 2 * v);
	float ww = w * w *(3 - 2 * w);

	float accum = 0;
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			for (int k = 0; k < 2; ++k)
			{
				float3 weight_v{ u - i, v - j, w - k };

				float3 cv = c[i][j][k];
				float dp = dot(c[i][j][k], weight_v);
				//accum += (i*uu + (1 - i)*(1 - uu))*
				//		 (j*vv + (1 - j)*(1 - vv))*
				//		 (k*ww + (1 - k)*(1 - ww))*
				//		 dp;

				accum += (i*uu + (1 - i)*(1 - uu))*
					(j*vv + (1 - j)*(1 - vv))*
					(k*ww + (1 - k)*(1 - ww))*dot(c[i][j][k], weight_v);
			}
	return accum;
}
