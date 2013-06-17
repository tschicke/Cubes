/*
 * Vectors.cpp
 *
 *  Created on: Jun 3, 2013
 *      Author: Tyler
 */

#include "Vectors.h"

namespace ts {

ts::Vector3f::Vector3f() {
	x = y = z = 0;
}
ts::Vector3f::Vector3f(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
ts::Vector3f::Vector3f(const Vector3f& copy) {
	x = copy.x;
	y = copy.y;
	z = copy.z;
}
Vector3f& ts::Vector3f::operator =(const Vector3f& vec) {
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	return *this;
}
Vector3f& ts::Vector3f::operator +=(const Vector3f& vec) {
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
	return *this;
}
Vector3f& ts::Vector3f::operator +=(const float num) {
	x += num;
	y += num;
	z += num;
	return *this;
}
Vector3f& ts::Vector3f::operator -=(const Vector3f& vec) {
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
	return *this;
}
Vector3f& ts::Vector3f::operator -=(const float num) {
	x -= num;
	y -= num;
	z -= num;
	return *this;
}
Vector3f& ts::Vector3f::operator *=(const Vector3f& vec) {
	this->x *= vec.x;
	this->y *= vec.y;
	this->z *= vec.z;
	return *this;
}
Vector3f& ts::Vector3f::operator *=(const float num) {
	x *= num;
	y *= num;
	z *= num;
	return *this;
}
Vector3f& ts::Vector3f::operator /=(const Vector3f& vec) {
	this->x /= vec.x;
	this->y /= vec.y;
	this->z /= vec.z;
	return *this;
}
Vector3f& ts::Vector3f::operator /=(const float num) {
	x /= num;
	y /= num;
	z /= num;
	return *this;
}
Vector3f operator+(const Vector3f vec, const float num) {
	return Vector3f(vec) += num;
}
Vector3f operator+(const float num, const Vector3f vec) {
	return Vector3f(vec) += num;
}
Vector3f operator+(const Vector3f vec1, const Vector3f vec2) {
	return Vector3f(vec1) += Vector3f(vec2);
}
Vector3f operator-(const Vector3f vec, const float num) {
	return Vector3f(vec) -= num;
}
Vector3f operator-(const float num, const Vector3f vec) {
	return Vector3f(vec) -= num;
}
Vector3f operator-(const Vector3f vec1, const Vector3f vec2) {
	return Vector3f(vec1) -= Vector3f(vec2);
}
Vector3f operator*(const Vector3f vec, const float num) {
	return Vector3f(vec) *= num;
}
Vector3f operator*(const float num, const Vector3f vec) {
	return Vector3f(vec) *= num;
}
Vector3f operator*(const Vector3f vec1, const Vector3f vec2) {
	return Vector3f(vec1) *= Vector3f(vec2);
}
Vector3f operator/(const Vector3f vec, const float num) {
	return Vector3f(vec) /= num;
}
Vector3f operator/(const float num, const Vector3f vec) {
	return Vector3f(vec) /= num;
}
Vector3f operator/(const Vector3f vec1, const Vector3f vec2) {
	return Vector3f(vec1) /= Vector3f(vec2);
}
bool operator==(const Vector3f& v1, const Vector3f& v2) {
	return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
}
bool operator!=(const Vector3f& v1, const Vector3f& v2) {
	return (v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z);
}



//Vec4
ts::Vector4f::Vector4f() {
	x = y = z = w = 0;
}
ts::Vector4f::Vector4f(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
ts::Vector4f::Vector4f(Vector3f vec, float w){
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	this->w = w;
}
ts::Vector4f::Vector4f(const Vector4f& copy) {
	x = copy.x;
	y = copy.y;
	z = copy.z;
	w = copy.w;
}
Vector4f& ts::Vector4f::operator =(const Vector4f& vec) {
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	this->w = vec.w;
	return *this;
}
Vector4f& ts::Vector4f::operator +=(const Vector4f& vec) {
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
	this->w += vec.w;
	return *this;
}
Vector4f& ts::Vector4f::operator +=(const float num) {
	x += num;
	y += num;
	z += num;
	w += num;
	return *this;
}
Vector4f& ts::Vector4f::operator -=(const Vector4f& vec) {
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
	this->w -= vec.w;
	return *this;
}
Vector4f& ts::Vector4f::operator -=(const float num) {
	x -= num;
	y -= num;
	z -= num;
	w -= num;
	return *this;
}
Vector4f& ts::Vector4f::operator *=(const Vector4f& vec) {
	this->x *= vec.x;
	this->y *= vec.y;
	this->z *= vec.z;
	this->w *= vec.w;
	return *this;
}
Vector4f& ts::Vector4f::operator *=(const float num) {
	x *= num;
	y *= num;
	z *= num;
	w *= num;
	return *this;
}
Vector4f& ts::Vector4f::operator /=(const Vector4f& vec) {
	this->x /= vec.x;
	this->y /= vec.y;
	this->z /= vec.z;
	this->w /= vec.w;
	return *this;
}
Vector4f& ts::Vector4f::operator /=(const float num) {
	x /= num;
	y /= num;
	z /= num;
	w /= num;
	return *this;
}
Vector4f operator+(const Vector4f vec, const float num) {
	return Vector4f(vec) += num;
}
Vector4f operator+(const float num, const Vector4f vec) {
	return Vector4f(vec) += num;
}
Vector4f operator+(const Vector4f vec1, const Vector4f vec2) {
	return Vector4f(vec1) += Vector4f(vec2);
}
Vector4f operator-(const Vector4f vec, const float num) {
	return Vector4f(vec) -= num;
}
Vector4f operator-(const float num, const Vector4f vec) {
	return Vector4f(vec) -= num;
}
Vector4f operator-(const Vector4f vec1, const Vector4f vec2) {
	return Vector4f(vec1) -= Vector4f(vec2);
}
Vector4f operator*(const Vector4f vec, const float num) {
	return Vector4f(vec) *= num;
}
Vector4f operator*(const float num, const Vector4f vec) {
	return Vector4f(vec) *= num;
}
Vector4f operator*(const Vector4f vec1, const Vector4f vec2) {
	return Vector4f(vec1) *= Vector4f(vec2);
}
Vector4f operator/(const Vector4f vec, const float num) {
	return Vector4f(vec) /= num;
}
Vector4f operator/(const float num, const Vector4f vec) {
	return Vector4f(vec) /= num;
}
Vector4f operator/(const Vector4f vec1, const Vector4f vec2) {
	return Vector4f(vec1) /= Vector4f(vec2);
}
bool operator==(const Vector4f& v1, const Vector4f& v2) {
	return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z) && (v1.w ==  v2.w);
}
bool operator!=(const Vector4f& v1, const Vector4f& v2) {
	return (v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z) || (v1.w != v2.w);
}

} /* namespace ts */
