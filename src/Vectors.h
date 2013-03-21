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
class vec2 {
public:
	vec2() {
		x = 0;
		y = 0;
	}
	vec2(T x, T y) {
		this->x = x;
		this->y = y;
	}
	virtual ~vec2();

	vec2& operator=(vec2 const& other) {
		if (this != &other) {
			x = other.x;
			y = other.y;
		}
		return *this;
	}

	vec2 operator+(vec2 const& other) {
		T newX = x + other.x;
		T newY = y + other.y;
		return vec2(newX, newY);
	}

	vec2 operator-(vec2 const& other) {
		T newX = x - other.x;
		T newY = y - other.y;
		return vec2(newX, newY);
	}

	T x, y;
};

template<typename T = float>
class vec3 {
public:
	vec3() {
		x = 0;
		y = 0;
		z = 0;
	}
	vec3(T x, T y, T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	virtual ~vec3();

	vec3& operator=(vec3 const& other) {
		if (this != &other) {
			x = other.x;
			y = other.y;
			z = other.z;
		}
		return *this;
	}

	vec3& operator+=(const vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	vec3& operator-=(const vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	vec3 operator+(vec3 const& other) {
		T newX = x + other.x;
		T newY = y + other.y;
		T newZ = z + other.z;
		return vec3(newX, newY, newZ);
	}

	vec3 operator-(vec3 const& other) {
		T newX = x - other.x;
		T newY = y - other.y;
		T newZ = z - other.z;
		return vec3(newX, newY, newZ);
	}

	template <typename U>
	vec3 operator*(U factor){
		T newX = x * factor;
		T newY = y * factor;
		T newZ = z * factor;
		return vec3(newX, newY, newZ);
	}

	T x, y, z;
};

template<typename T = float>
class vec4 {
public:
	vec4() {
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}
	vec4(T x, T y, T z, T w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	virtual ~vec4();

	vec4& operator=(vec4 const& other) {
		if (this != &other) {
			x = other.x;
			y = other.y;
			z = other.z;
		}
		return *this;
	}

	vec4 operator+(vec4 const& other) {
		T newX = x + other.x;
		T newY = y + other.y;
		T newZ = z + other.z;
		T newW = w + other.w;
		return vec4(newX, newY, newZ, newW);
	}

	vec4 operator-(vec4 const& other) {
		T newX = x - other.x;
		T newY = y - other.y;
		T newZ = z - other.z;
		T newW = w - other.w;
		return vec4(newX, newY, newZ, newW);
	}

	T x, y, z, w;
};

} /* namespace ts */
#endif /* VECTORS_H_ */
