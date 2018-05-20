// RayTracerInAWeekend.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <chrono>
#include "Config.h"
#include "Vec3.h"
#include "Ray.h"
#include "Hitable.h"
#include "HitableList.h"
#include "Sphere.h"
#include "Rect.h"
#include "Camera.h"

#include "Material.h"
#include "DiffuseLight.h"
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
	for (int a = -25; a < 25; ++a)
	{
		for (int b = -25; b < 25; ++b)
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


HitableList* TheThreeBalls()
{

	IHitable** d = new IHitable*[5];
	d[0] = (new Sphere(float3(0, -1000, 0), 1000, new Lambertian(
		new CheckerTexture(
			new ConstantTexture(float3(0.5f, 0.5f, 0.5f)),
			new ConstantTexture(float3(0.1f, 0.1f, 0.1f))
		)
	)));

	d[1] = ( new Sphere(float3(0, 1, 0), 1.0f, new Dielectric(1.5f)));
	d[2] = ( new Sphere(float3(0, 1, 0), 0.8f, new Dielectric(1.5f)));
	d[3] = ( new Sphere(float3(-4, 1, 0), 1.0f, new Lambertian(new ConstantTexture(float3(0.4f, 0.2f, 0.1f)))));
	d[4] = ( new Sphere(float3(4, 1, 0), 1.0f, new Metal(float3(0.7f, 0.6f, 0.5f), 0.0f)));
	return new HitableList(d,5);
}
HitableList* TwoSpheres(Camera& cam, uint32_t nx, uint32_t ny)
{
	cam = Camera(
		float3(13, 2, 3), 
		float3(0, 0, 0), 
		float3(0, 1, 0), 
		20.f, // fov
		float(nx) / float(ny),
		0.f, 
		10.f, 
		0.0f,
		1.0f);

	Texture* checker = new CheckerTexture(new ConstantTexture(float3(1, 1, 1)), new ConstantTexture(float3(0, 0, 0)));
	int n = 2;
	IHitable **list = new IHitable *[n + 1];
	list[0] = new Sphere(float3(0, -10, 0), 10, new Lambertian(checker));
	list[1] = new Sphere(float3(0, 10, 0), 10, new Lambertian(checker));
	return new HitableList(list, 2);
}
HitableList* TwoNoiseSpheres(Camera& cam, uint32_t nx, uint32_t ny)
{
	cam = Camera(
		float3(13, 2, 3),
		float3(0, 0, 0),
		float3(0, 1, 0),
		20.f, // fov
		float(nx) / float(ny),
		0.f,
		10.f,
		0.0f,
		1.0f);

	Texture* checker = new NoiseTexture(4.0f);
	int n = 2;
	IHitable **list = new IHitable *[n + 1];
	list[0] = new Sphere(float3(0, -1000, 0), 1000, new Lambertian(checker));
	list[1] = new Sphere(float3(0, 2, 0), 2, new Lambertian(checker));
	return new HitableList(list, 2);
}
HitableList* SimpleLight(Camera& cam, uint32_t nx, uint32_t ny) {
	cam = Camera(
		float3(19, 7, 3),
		float3(0, 1, 0),
		float3(0, 1, 0),
		20.f, // fov
		float(nx) / float(ny),
		0.f,
		10.f,
		0.0f,
		1.0f);

	Texture* perTex = new NoiseTexture(4);
	IHitable** list = new IHitable*[4];
	list[0] = new Sphere(float3(0, -1000, 0), 1000, new Lambertian(new CheckerTexture(new ConstantTexture({ 1,1,1 }), new ConstantTexture({ 0.1f,0.1f,0.1f }))));
	list[1] = new Sphere(float3(0, 2, 0), 2, new Lambertian(new ConstantTexture({ 0.4f,1,0 })));
	list[2] = new Sphere(float3(0, 7, 0), 2, new DiffuseLight(new ConstantTexture({4,4,4})));
	list[3] = new XYRect(3, 5, 1, 3, -2, new DiffuseLight(new ConstantTexture({ 4,4,4 })));

	return new HitableList(list, 4);
}
/* Samples a color from the scene */
static const int g_Depth = 50;

float3 Color(const Ray& r, IHitable* world, int depth = 0)
{
	HitRecord rec;
	if (world->Hit(r, 0.001f, std::numeric_limits<float>::max(), rec))
	{
		Ray scattered;
		float3 attenuation;
		float3 emitted = rec.material->Emitted(rec.uv.x, rec.uv.y, rec.p);
		if (depth < g_Depth && rec.material->Scatter(r, rec, attenuation, scattered))
		{
			return emitted + attenuation * Color(scattered, world, depth + 1);
		}
		else {
			// Replace with IBL ?
			return emitted;
		}
	}

	// Background
	return float3(0, 0, 0);

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
	int nx = 400;
	int ny = 200;
	uint16_t ns = 10;
	
	unsigned int n = std::thread::hardware_concurrency();
	uint8_t nThreads = n - 2;
	nThreads = 1;
#if !defined(_DEBUG)
	nThreads = n - 1;
	//nThreads = 1;
	nx = 1280;
	ny = 720;
	ns = 250;
#endif
	std::cout << nx << "x" << ny << "@" << ns << "ppp" << "\n";
	std::cout << "Running with " << std::to_string(nThreads) << " thread(s)." << "\n";

	float3 eye{ 13,2,3 };
	float3 lookat{ 0,0,0 };
	float aperture = 0.0f;
	//float focusDist = hlslpp::length(eye - lookat);
	float focusDist = 10.0;
	Camera cam(eye, lookat,float3(0,1,0),20.0f,float(nx) / ny, aperture,focusDist, 0.f, 1.f);

	HitableList* scene = SimpleLight(cam,nx,ny);
	IHitable* world = scene;
	{
		auto t = ScopedTimer("Setting up BVH tree: ");
		std::vector<IHitable*> list{ scene->m_List, scene->m_List + scene->m_ListSize};
		world = new BVHNode(list,0.0f,1.0f);
	}


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

	int override_nx = 202;
	int override_ny = 108;

	int nRows = ny / nThreads;
	std::vector<std::thread> threadCalc;
	for (int i = 0; i < nThreads; ++i)
	{
		int start = ny - 1 - i * nRows;
		int target = std::max(start - nRows + 1, 0) ;
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
					//j = ny - override_ny;
					//i = override_nx;
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
					// Just casting brings problems when the value range is bigger than 1
					uint8_t ir = uint8_t(fmin(255.99f* col._f32[0],255));
					uint8_t ig = uint8_t(fmin(255.99f* col._f32[1],255));
					uint8_t ib = uint8_t(fmin(255.99f* col._f32[2],255));

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
			p = 100.f * float(counter) / (nx * ny);

			auto tEnd = timer.now();
			dur = std::chrono::duration_cast<std::chrono::milliseconds>(tEnd - tbegin);
			std::cout << "Progress: " << std::fixed << std::setprecision(4) << std::setw(4) << p  << "% (" << std::setw(4) << dur.count() / 1000.0f << "s) \n";
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
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

