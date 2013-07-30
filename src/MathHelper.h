/*
 * MathHelper.h
 *
 *  Created on: Jul 29, 2013
 *      Author: Tyler
 */

#ifndef MATHHELPER_H_
#define MATHHELPER_H_

#define MATH_PI 3.14159265f

class MathHelper {
public:
	static void init();
	static void cleanup();

	static float sin_float(float radians);
	static float cos_float(float radians);

	static float toRadians(float degrees);
	static float toDegrees(float radians);
private:
	MathHelper(){};
	virtual ~MathHelper(){};

	static float * SIN_TABLE;
};

#endif /* MATHHELPER_H_ */
