// RayTracerInAWeekend.cpp : Defines the entry point for the console application.
//

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

/* Samples a color from the scene */
Vec3 Color(const Ray& r, IHitable* world, int depth = 0)
{
	HitRecord rec;
	if (world->Hit(r, 0.001f, std::numeric_limits<float>::max(), rec))
	{
		Ray scattered;
		Vec3 attenuation;
		if (depth < 50 && rec.material->Scatter(r, rec, attenuation, scattered))
		{
			return attenuation * Color(scattered, world, depth + 1);
		}
		else {
			// Replace with IBL ?
			return Vec3(0, 0, 0);
		}
	}

	// Background
	Vec3 unitDir = UnitVector(r.Direction());
	float t = 0.5f*(unitDir.y() + 1.0f);
	return (1.0f - t)*Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
}


int main()
{
	std::cout << "Starting raytracer Version " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;
	std::ofstream file("image.ppm");
	int nx = 200;
	int ny = 100;
	uint16_t ns = 100;
#if !defined(_DEBUG)
	ns = 500;
#endif

	file << "P3\n" << nx << " " << ny << "\n255\n";

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

	Camera cam(Vec3(-2,2,1), Vec3(0,0,-1),Vec3(0,1,0),50.0f,float(nx) / ny);

	auto d = std::uniform_real_distribution<float>();
	for (int j = ny - 1; j >= 0; --j)
	{
		for (int i = 0; i < nx; ++i)
		{
			Vec3 col{ 0,0,0 };
			for (int s = 0; s < ns; ++s)
			{
				float u = float(i + d(g_mt)) / nx;
				float v = float(j + d(g_mt)) / ny;
				Ray r = cam.GetRay(u, v);
				col += Color(r,world);
			}
			col /= float(ns);
			// Gamma correction
			float gamma = 1 / 2.f;
			col = Vec3(pow(col[0],gamma), pow(col[1],gamma), pow(col[2],gamma));

			// Convert the colors to file range
			int ir = int(255.99* col[0]);
			int ig = int(255.99* col[1]);
			int ib = int(255.99* col[2]);
			file << ir << " " << ig << " " << ib << "\n";
		}
		std::cout << "Row " << j << " finished." << std::endl;
	}
	std::cout << "Done" << std::endl;

	delete world;

    return 0;
}

