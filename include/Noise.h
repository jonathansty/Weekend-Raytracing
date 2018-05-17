#pragma once

namespace Math
{
	float TrilinearInterp(float3 c[2][2][2], float u, float v, float w);

	class PerlinNoise
	{
	public:

		float noise(const float3& p) const;

		float turb(const float3& p, int depth = 7) const;
		static float3* m_RanFloat;

		static std::array<int,256> m_PermX;
		static std::array<int,256> m_PermY;
		static std::array<int,256> m_PermZ;

		static float3* PerlinGenerate();

		static void Permute(std::array<int,256> p, int n);

		static std::array<int,256> PerlinGeneratePerm();
	};


}
