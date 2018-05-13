#pragma once

namespace Math
{
	float PerlinInterp(float3 c[2][2][2], float u, float v, float w);
	class PerlinNoise
	{
	public:

		float noise(const float3& p) const;
		static float3* m_RanFloat;

		static int *m_PermX;
		static int *m_PermY;
		static int *m_PermZ;

		static float3* PerlinGenerate()
		{
			float3* p = new float3[256];
			for (int i = 0; i < 256; ++i)
			{
				float3 v = float3(-1 + 2 * Random::Value(), -1 + 2 * Random::Value(), -1 + 2 * Random::Value());
				p[i] = hlslpp::normalize(v);
			}
			return p;
		}
		static void Permute(int* p, int n)
		{
			for (int i = n - 1; i > 0; --i)
			{
				int target = int(Random::Value() * (i + 1));
				int tmp = p[i];
				p[i] = p[target];
				p[target] = tmp;
			}
		}
		static int* PerlinGeneratePerm() {
			int* p = new int[256];
			for (int i = 0; i < 256; ++i)
				p[i] = i;

			Permute(p, 256);
			return p;
		}
	};


}
