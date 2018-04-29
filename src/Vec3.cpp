#include "stdafx.h"
#include "Vec3.h"


//Vec3::Vec3() : e{}
//{
//
//}
//
//
//Vec3::~Vec3()
//{
//
//}
//
//Vec3& Vec3::operator+=(const Vec3& v2)
//{
//	this->e[0] += v2.e[0];
//	this->e[1] += v2.e[1];
//	this->e[2] += v2.e[2];
//	return *this;
//}
//
//Vec3& Vec3::operator-=(const Vec3& v2)
//{
//	this->e[0] -= v2.e[0];
//	this->e[1] -= v2.e[1];
//	this->e[2] -= v2.e[2];
//	return *this;
//}
//
//Vec3& Vec3::operator*=(const Vec3& v2)
//{
//	this->e[0] *= v2.e[0];
//	this->e[1] *= v2.e[1];
//	this->e[2] *= v2.e[2];
//	return *this;
//}
//
//Vec3& Vec3::operator/=(const Vec3& v2)
//{
//	this->e[0] /= v2.e[0];
//	this->e[1] /= v2.e[1];
//	this->e[2] /= v2.e[2];
//	return *this;
//}
//
//Vec3& Vec3::operator*=(float t)
//{
//	this->e[0] *= t;
//	this->e[1] *= t;
//	this->e[2] *= t;
//	return *this;
//}
//
//Vec3& Vec3::operator/=(float t)
//{
//	this->e[0] /= t;
//	this->e[1] /= t;
//	this->e[2] /= t;
//	return *this;
//}
//
//void Vec3::MakeUnitVector()
//{
//	float length = Length();
//	e[0] = (e[0] / length);
//	e[1] = (e[1] / length);
//	e[2] = (e[2] / length);
//}
