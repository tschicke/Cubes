/*
 * Vectors.h
 *
 *  Created on: Mar 20, 2013
 *      Author: Tyler
 */

#ifndef VECTORS_H_
#define VECTORS_H_

namespace ts {

//TODO finish overloading operators
//TODO move to .cpp file

template<typename T = float>
class Vector2;
template<typename T = float>
class Vector3;
template<typename T = float>
class Vector4;

typedef Vector2<float> vec2;
typedef Vector3<float> vec3;
typedef Vector4<float> vec4;

typedef Vector2<int> vec2i;
typedef Vector3<int> vec3i;
typedef Vector4<int> vec4i;

typedef Vector2<double> vec2d;
typedef Vector3<double> vec3d;
typedef Vector4<double> vec4d;

template<typename T>
class Vector2 {
public:
	Vector2() {
		x = 0;
		y = 0;
	}
	Vector2(T x, T y) {
		this->x = x;
		this->y = y;
	}
	virtual ~Vector2();

	Vector2& operator=(Vector2 const& other) {
		if (this != &other) {
			x = other.x;
			y = other.y;
		}
		return *this;
	}

	Vector2 operator+(Vector2 const& other) {
		T newX = x + other.x;
		T newY = y + other.y;
		return Vector2(newX, newY);
	}

	Vector2 operator-(Vector2 const& other) {
		T newX = x - other.x;
		T newY = y - other.y;
		return Vector2(newX, newY);
	}

	T x, y;
};

template<typename T>
class Vector3 {
public:
	Vector3() {
		x = 0;
		y = 0;
		z = 0;
	}
	Vector3(T x, T y, T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	virtual ~Vector3();

	Vector3& operator=(Vector3 const& other) {
		if (this != &other) {
			x = other.x;
			y = other.y;
			z = other.z;
		}
		return *this;
	}

	Vector3& operator+=(const Vector3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector3& operator-=(const Vector3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vector3 operator+(Vector3 const& other) {
		T newX = x + other.x;
		T newY = y + other.y;
		T newZ = z + other.z;
		return Vector3(newX, newY, newZ);
	}

	Vector3 operator-(Vector3 const& other) {
		T newX = x - other.x;
		T newY = y - other.y;
		T newZ = z - other.z;
		return Vector3(newX, newY, newZ);
	}

	template <typename U>
	Vector3 operator*(U factor){
		T newX = x * factor;
		T newY = y * factor;
		T newZ = z * factor;
		return Vector3(newX, newY, newZ);
	}

	T x, y, z;
};

template<typename T>
class Vector4 {
public:
	Vector4() {
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}
	Vector4(T x, T y, T z, T w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	virtual ~Vector4();

	Vector4& operator=(Vector4 const& other) {
		if (this != &other) {
			x = other.x;
			y = other.y;
			z = other.z;
		}
		return *this;
	}

	Vector4 operator+(Vector4 const& other) {
		T newX = x + other.x;
		T newY = y + other.y;
		T newZ = z + other.z;
		T newW = w + other.w;
		return Vector4(newX, newY, newZ, newW);
	}

	Vector4 operator-(Vector4 const& other) {
		T newX = x - other.x;
		T newY = y - other.y;
		T newZ = z - other.z;
		T newW = w - other.w;
		return Vector4(newX, newY, newZ, newW);
	}

	T x, y, z, w;
};

} /* namespace ts */
#endif /* VECTORS_H_ */
