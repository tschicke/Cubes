/*
 * Noise.h
 *
 *  Created on: Mar 9, 2013
 *      Author: Tyler
 */

#ifndef NOISE_H_
#define NOISE_H_

class Noise {
public:
	Noise();
	virtual ~Noise();
	double smoothNoise(double x, double y);
private:
	double noise2D(double x, double y);
	double interpolate(double a, double b, double x);
};

#endif /* NOISE_H_ */
