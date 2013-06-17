/*
 * Vectors.h
 *
 *  Created on: Jun 3, 2013
 *      Author: Tyler
 */

#ifndef VECTORS_H_
#define VECTORS_H_

namespace ts {

class Vector3f {
public:
	Vector3f();
	Vector3f(float x, float y, float z);
	Vector3f(const Vector3f& copy);

	Vector3f& operator=(const Vector3f& vec);

	Vector3f& operator+=(const Vector3f& vec);
	Vector3f& operator+=(const float num);

	Vector3f& operator-=(const Vector3f& vec);
	Vector3f& operator-=(const float num);

	Vector3f& operator*=(const Vector3f& vec);
	Vector3f& operator*=(const float num);

	Vector3f& operator/=(const Vector3f& vec);
	Vector3f& operator/=(const float num);

	float x, y, z;
private:
};

class Vector4f {
public:
	Vector4f();
	Vector4f(float x, float y, float z, float w);
	Vector4f(Vector3f vec, float w);
	Vector4f(const Vector4f& copy);

	Vector4f& operator=(const Vector4f& vec);

	Vector4f& operator+=(const Vector4f& vec);
	Vector4f& operator+=(const float num);

	Vector4f& operator-=(const Vector4f& vec);
	Vector4f& operator-=(const float num);

	Vector4f& operator*=(const Vector4f& vec);
	Vector4f& operator*=(const float num);

	Vector4f& operator/=(const Vector4f& vec);
	Vector4f& operator/=(const float num);

	float x, y, z, w;
private:
};

} /* namespace ts */
#endif /* VECTORS_H_ */
