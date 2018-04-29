// RayTracerInAWeekend.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <chrono>
#include "Config.h"
#include "Vec3.h"
#include "Ray.h"
#include "Hitable.h"
#include "HitableList.h"
#include "Sphere.h"
#include "Camera.h"

#include "Material.h"




using namespace Random;
using namespace hlslpp;

/* Samples a color from the scene */
float3 Color(const Ray& r, IHitable* world, int depth = 0)
{
	HitRecord rec;
	if (world->Hit(r, 0.001f, std::numeric_limits<float>::max(), rec))
	{
		Ray scattered;
		float3 attenuation;
		if (depth < 50 && rec.material->Scatter(r, rec, attenuation, scattered))
		{
			return attenuation * Color(scattered, world, depth + 1);
		}
		else {
			// Replace with IBL ?
			return float3(0, 0, 0);
		}
	}

	// Background
	float3 unitDir = hlslpp::normalize(r.Direction());
	float t = 0.5f*(unitDir.y + 1.0f);
	return (1.0f - t)*float3(1.0f, 1.0f, 1.0f) + t * float3(0.5f, 0.7f, 1.0f);
}


int main()
{
	std::cout << "Starting ray tracer Version " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;
	// Resolution 
	int nx = 200;
	int ny = 100;
	uint16_t ns = 100;
	uint8_t nThreads = 1;
	
#if !defined(_DEBUG)
	nThreads = 8;
	nx = 600;
	ny = 400;
	ns = 100;
#endif

	IHitable* list[5];
	list[0] = new Sphere({ 0,0,-1 }, 0.5f, new Lambertian({ 0.8f,0.3f,0.3f }));
	list[1] = new Sphere({ 0,-100.5,-1 }, 100.f, new Lambertian({ 0.9f,0.8f,0.0f }));
	list[2] = new Sphere({ 1,0,-1 }, 0.5f, new Metal({ 0.8f,0.6f,0.2f },0.2f));
	list[3] = new Sphere({ -1,0,-1 }, 0.5f, new Dielectric(1.5f));
	list[4] = new Sphere({ -1,0,-1 }, -0.45f, new Dielectric(1.5f));

	//float r = cos(M_PI / 4.0f);
	//list[0] = new Sphere({ -r,0,-1 }, r,new Lambertian({ 0,0,1 }));
	//list[1] = new Sphere({  r,0,-1 }, r, new Lambertian({1,0,0}));
	IHitable* world = new HitableList(list, 5);

	float3 eye{ 3,3,2 };
	float3 lookat{ 0,0,-1 };
	float aperture = 0.1f;
	float focusDist = hlslpp::length(eye - lookat);
	Camera cam(eye, lookat,float3(0,1,0),20.0f,float(nx) / ny, aperture,focusDist);

	auto d = std::uniform_real_distribution<float>();

	/* 8 bit per color channel */
	struct RGBColor 
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
	};

	RGBColor* all_data = new RGBColor[nx * ny];
	RGBColor* data = all_data;

	int nRows = ny / nThreads;
	std::vector<std::thread> threadCalc;
	for (int i = 0; i < nThreads; ++i)
	{
		threadCalc.push_back(std::thread(
		[&]() 
		{
			int start = ny - i * nRows;
			for (int j = ny - 1 - i*nRows; j >= 0 ; --j)
			{
				for (int i = 0; i < nx; ++i)
				{
					float3 col{ 0,0,0 };
					for (int s = 0; s < ns; ++s)
					{
						float u = float(i + d(g_mt)) / nx;
						float v = float(j + d(g_mt)) / ny;
						Ray r = cam.GetRay(u, v);
						col += Color(r, world);
					}
					col /= float(ns);
					// Gamma correction
					float gamma = 1 / 2.f;
					col = float3(pow(col._f32[0], gamma), pow(col._f32[1], gamma), pow(col._f32[2], gamma));

					// Convert the colors to file range
					uint8_t ir = uint8_t(255.99* col._f32[0]);
					uint8_t ig = uint8_t(255.99* col._f32[1]);
					uint8_t ib = uint8_t(255.99* col._f32[2]);

					data[i + (ny - 1 - j) * nx] = { ir,ig,ib };
				}
			}
		}));
	}

	for(std::thread& s : threadCalc)
	{
		s.join();
	}


	stbi_write_png("image.png", nx, ny, 3, all_data,nx*sizeof(RGBColor));

	delete[] all_data;
	delete world;

    return 0;
}

