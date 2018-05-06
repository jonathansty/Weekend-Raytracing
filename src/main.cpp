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
#include "texture.h"
#include "aabb.h"
#include "main.h"
using namespace Math;
using namespace Random;
using namespace hlslpp;

HitableList* RandomScene()
{
	int n = 5000;
	IHitable** list = new IHitable*[n + 1];
	list[0] = new Sphere(float3(0, -1000, 0), 1000, new Lambertian(
		new CheckerTexture(
			new ConstantTexture(float3(0.5f, 0.5f, 0.5f)),
			new ConstantTexture(float3(0.1f,0.1f,0.1f))
		)
	));

	int i = 1;
	for (int a = -10; a < 10; ++a)
	{
		for (int b = -10; b < 10; ++b)
		{
			float matRand = Random::Value();
			float3 center(a + 0.9f*Random::Value(), 0.2f, b + 0.9f*Random::Value());
			if (hlslpp::length(center - float3(4.f, 0.2f, 0.f)) > 0.9f)
			{
				// Pick diffuse
				if (matRand < 0.8)
				{
					list[i++] = new MovingSphere(0.f, 1.0f, center, center + float3(0.f, 0.5f*Random::Value(), 0.0f), 0.2f,
						new Lambertian(new ConstantTexture(float3(Random::Value()*Random::Value(), Random::Value() * Random::Value(), Random::Value() * Random::Value()))));
				}
				// Pick metal
				else if (matRand < 0.95)
				{
					list[i++] = new Sphere(center, 0.2f, new Metal(float3(0.5f*(1 + Random::Value()), 0.5f*(1 + Random::Value()), 0.5f*(1 + Random::Value())), 0.5f*Random::Value()));
				}
				// Pick glass
				else
				{
					list[i++] = new Sphere(center, 0.2f, new Dielectric(1.5f));
				}
			}
		}
	}
	list[i++] = new Sphere(float3(0, 1, 0), 1.0f, new Dielectric(1.5f));
	list[i++] = new Sphere(float3(-4, 1, 0), 1.0f, new Lambertian(new ConstantTexture(float3(0.4f, 0.2f, 0.1f))));
	list[i++] = new Sphere(float3(4, 1, 0), 1.0f, new Metal(float3(0.7f, 0.6f, 0.5f), 0.0f));

	return new HitableList(list, i);

}
/* Samples a color from the scene */
static const int g_Depth = 10;

float3 Color(const Ray& r, IHitable* world, int depth = 0)
{
	HitRecord rec;
	if (world->Hit(r, 0.001f, std::numeric_limits<float>::max(), rec))
	{
		Ray scattered;
		float3 attenuation;
		if (depth < g_Depth && rec.material->Scatter(r, rec, attenuation, scattered))
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
	std::chrono::high_resolution_clock timer{};
	auto tbegin = timer.now();
	// Resolution 
	int nx = 200;
	int ny = 100;
	uint16_t ns = 15;
	uint8_t nThreads = 6;
	
	unsigned int n = std::thread::hardware_concurrency();
#if !defined(_DEBUG)
	nThreads = n - 1;
	nx = 600;
	ny = 300;
	ns = 60;
#endif
	std::cout << nx << "x" << ny << "@" << ns << "ppp" << "\n";
	std::cout << "Running with " << std::to_string(nThreads) << " thread(s)." << "\n";

	//float r = cos(M_PI / 4.0f);
	//list[0] = new Sphere({ -r,0,-1 }, r,new Lambertian({ 0,0,1 }));
	//list[1] = new Sphere({  r,0,-1 }, r, new Lambertian({1,0,0}));
	HitableList* scene = RandomScene();
	IHitable* world = scene;
	//std::vector<IHitable*> list{ scene->m_List, scene->m_List + scene->m_ListSize};
	//IHitable* world = new BVHNode(list,0.0f,1.0f);

	float3 eye{ 13,2,3 };
	float3 lookat{ 0,0,0 };
	float aperture = 0.0f;
	//float focusDist = hlslpp::length(eye - lookat);
	float focusDist = 10.0;
	Camera cam(eye, lookat,float3(0,1,0),20.0f,float(nx) / ny, aperture,focusDist, 0.f, 1.f);

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

	std::atomic<int> counter = 0;
	std::atomic<bool> bRendering = true;

	int nRows = ny / nThreads;
	std::vector<std::thread> threadCalc;
	for (int i = 0; i < nThreads; ++i)
	{
		int start = ny - 1 - i * nRows;
		int target = std::max(start - nRows, 0);
		if (i == nThreads - 1)
			target = 0;

		std::cout << "Created thread for region " << start << " to " << target << "\n";
		threadCalc.push_back(std::thread(
		[&,start,target]() 
		{
			for (int j = start; j >= target; --j)
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
					++counter;
				}
			}
		}));
	}

	std::thread progressThread{ 
	[&]() 
	{
		float p = 0;
		std::chrono::milliseconds dur;
		while (bRendering)
		{
			p = 100.f * float(counter) / (nx * ny - 1);

			auto tEnd = timer.now();
			dur = std::chrono::duration_cast<std::chrono::milliseconds>(tEnd - tbegin);
			std::cout << "Progress: " << std::fixed << std::setprecision(4) << std::setw(4) << p  << "% (" << std::setw(4) << dur.count() / 1000.0f << "s) \n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		std::cout << "Finished rendering after " << dur.count() / 1000.0f << " seconds! \n";
	} 
	};

	for(std::thread& s : threadCalc)
	{
		s.join();
	}

	bRendering = false;
	auto tEnd = timer.now();
	auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(tEnd - tbegin);
	std::cout << "Finished in " << dur.count() / 1000.0f << "ms" << std::endl;
	progressThread.join();


	stbi_write_png("image.png", nx, ny, 3, all_data,nx*sizeof(RGBColor));

	delete[] all_data;
	
	std::cin.get();
    return 0;
}

