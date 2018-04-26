cmake_minimum_required (VERSION 2.6)
project("Raytracing_In_A_Weekend")

# Setup config
set (Raytracing_In_A_Weekend_VERSION_MAJOR 1)
set (Raytracing_In_A_Weekend_VERSION_MINOR 0)
set (CMAKE_CXX_STANDARD 17)

include_directories(
	"${PROJECT_SOURCE_DIR}/include"
)

configure_file(
	"${PROJECT_SOURCE_DIR}/Config.h.inl"
	"${PROJECT_BINARY_DIR}/Config.h"
)

include_directories("$(PROJECT_BINARY_DIR)")
set ( SOURCES 
	"src/main.cpp"
	"src/Ray.cpp"
	"src/Vec3.cpp"
	"src/stdafx.cpp"
	"src/Hitable.cpp"
	"src/Sphere.cpp"
	"src/HitableList.cpp"
	"src/Camera.cpp"
	"src/Material.cpp"
	
	"include/Material.h"
	"include/Ray.h"
	"include/Vec3.h"
	"include/stdafx.h"
	"include/Hitable.h"
	"include/Sphere.h"
	"include/HitableList.h"
	"include/Camera.h"

)

add_executable(raytracer ${SOURCES})