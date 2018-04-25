// RayTracerInAWeekend.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Config.h"
#include "Vec3.h"
#include "Ray.h"
#include "Hitable.h"
#include "HitableList.h"
#include "Sphere.h"
#include "Camera.h"

Vec3 Color(const Ray& r, IHitable* world)
{
	HitRecord rec;
	if (world->Hit(r, 0.0f, std::numeric_limits<float>::max(),rec))
		return 0.5f*(Vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1));

	// Background color
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
	file << "P3\n" << nx << " " << ny << "\n255\n";

	Vec3 LowerLeft(-2.0, -1.0, -1.0);
	Vec3 hor(4.0, 0.0, 0.0);
	Vec3 ver(0.0, 2.0, 0.0);
	Vec3 origin(0.0, 0.0, 0.0);

	IHitable* list[2];
	list[0] = new Sphere({ 0,0,-1 }, 0.5f);
	list[1] = new Sphere({ 0,-100.5,-1 }, 100);
	IHitable* world = new HitableList(list, 2);

	Camera cam;
	std::mt19937 ms_random;
	auto d = std::uniform_real_distribution<float>();
	for (int j = ny - 1; j >= 0; --j)
	{
		for (int i = 0; i < nx; ++i)
		{
			Vec3 col{ 0,0,0 };
			for (int s = 0; s < ns; ++s)
			{
				float u = float(i + d(ms_random)) / nx;
				float v = float(j + d(ms_random)) / ny;
				Ray r = cam.GetRay(u, v);
				Vec3 p = r.PointAtParameter(2.0f);
				col += Color(r,world);
			}
			col /= float(ns);

			// Convert the colors to file range
			int ir = int(255.99* col[0]);
			int ig = int(255.99* col[1]);
			int ib = int(255.99* col[2]);
			file << ir << " " << ig << " " << ib << "\n";
		}
	}
	std::cout << "Done" << std::endl;

	delete world;

    return 0;
}

