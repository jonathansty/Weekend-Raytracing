cmake_minimum_required (VERSION 2.6)
project("Raytracing_In_A_Weekend")

# Setup config
set (Raytracing_In_A_Weekend_VERSION_MAJOR 1)
set (Raytracing_In_A_Weekend_VERSION_MINOR 1)
set (CMAKE_CXX_STANDARD 17)

include_directories(
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/lib/hlslpp/src"
)

configure_file(
	"${PROJECT_SOURCE_DIR}/Config.h.inl"
	"${PROJECT_BINARY_DIR}/Config.h"
)
if(!WIN32)
	set (GCC_COVERAGE_COMPILE_FLAGS "-m32 -msse4.1")
	set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
endif()



include_directories("$(PROJECT_BINARY_DIR)")
set ( SOURCES 
	"src/main.cpp"
	"include/main.h"

	# precompiled header ( normally )
	"src/stdafx.cpp"
	"include/stdafx.h"

	# Maths
	"src/Ray.cpp"
	"include/Ray.h"
	"src/Vec3.cpp"
	"include/Vec3.h"
	"src/aabb.cpp"
	"include/aabb.h"
	"src/Random.cpp"
	"include/Random.h"
	"src/Noise.cpp"
	"include/Noise.h"

	# hitables
	"src/Hitable.cpp"
	"include/Hitable.h"
	"src/HitableList.cpp"
	"include/HitableList.h"
	"src/Sphere.cpp"
	"include/Sphere.h"
	"src/Rect.cpp"
	"include/Rect.h"
	
	# camera
	"src/Camera.cpp"
	"include/Camera.h"

	# materials
	"src/Material.cpp"
	"include/Material.h"

	# textures
	"src/texture.cpp"
	"include/texture.h"

	# lights
	"src/DiffuseLight.cpp"
	"include/DiffuseLight.h"

)

add_executable(raytracer ${SOURCES})