#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
//class Vec3
//{
//public:
//	Vec3();
//
//	Vec3(float x, float y, float z) 
//	{ 
//		e[0] = x;
//		e[1] = y;
//		e[2] = z;
//	}
//
//	~Vec3();
//
//	inline float x() const { return e[0]; }
//	inline float y() const { return e[1]; }
//	inline float z() const { return e[2]; }
//
//	inline float r() const { return e[0]; }
//	inline float g() const { return e[1]; }
//	inline float b() const { return e[2]; }
//
//	inline const Vec3 operator+() const { return *this; }
//	inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
//
//	inline float operator[](int i) const { return e[i]; }
//	inline float& operator[](int i) { return e[i]; }
//
//	Vec3& operator+=(const Vec3& v2);
//	Vec3& operator-=(const Vec3& v2);
//	Vec3& operator*=(const Vec3& v2);
//	Vec3& operator/=(const Vec3& v2);
//	Vec3& operator*=(float t);
//	Vec3& operator/=(float t);
//
//	inline float Length() const
//	{
//		return float(sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]));
//	}
//	inline float LengthSquared() const
//	{
//		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
//	}
//
//	void MakeUnitVector();
//
//	float e[3];
//};

//inline std::istream& operator>>(std::istream &is, Vec3& t)
//{
//	is >> t.e[0] >> t.e[1] >> t.e[2];
//	return is;
//}
//inline std::ostream& operator<<(std::ostream& os, const Vec3& t)
//{
//	os << t.e[0] << t.e[1] << t.e[2];
//	return os;
//}
//inline Vec3 operator+(const Vec3& v1, const Vec3& v2)
//{
//	return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
//}
//inline Vec3 operator-(const Vec3& v1, const Vec3& v2)
//{
//	return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
//}
//
//inline Vec3 operator/(const Vec3& v1, const Vec3& v2)
//{
//	return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
//}
//
//inline Vec3 operator*(const Vec3& v1, const Vec3& v2)
//{
//	return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
//}
//
//inline Vec3 operator*(const Vec3& v1, float f)
//{
//	return  Vec3(v1.e[0] * f, v1.e[1] * f, v1.e[2] * f);
//}
//
//inline Vec3 operator*(float f,const Vec3& v1)
//{
//	return Vec3(v1.e[0] * f, v1.e[1] * f, v1.e[2] * f);
//}
//
//inline Vec3 operator/(const Vec3& v1, float f)
//{
//	return  Vec3(v1.e[0] / f, v1.e[1] / f, v1.e[2] / f);
//}
//
//inline Vec3 operator/(float f,const Vec3& v1)
//{
//	return  Vec3(v1.e[0] / f, v1.e[1] / f, v1.e[2] / f);
//}
//inline float dot(const Vec3& v1, const Vec3& v2)
//{
//	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
//}
//
//inline Vec3 cross(const Vec3& v1, const Vec3& v2)
//{
//	return Vec3(
//		v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1],
//		-( v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0] ),
//		v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0]
//	);
//}
//
//inline Vec3 UnitVector(const Vec3& v)
//{
//	return v / v.Length();
//}
