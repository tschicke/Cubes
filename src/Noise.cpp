/*
 * Noise.cpp
 *
 *  Created on: Mar 9, 2013
 *      Author: Tyler
 */

#include "Noise.h"
#include <math.h>

Noise::Noise() {
}

Noise::~Noise() {
}

double Noise::smoothNoise(double x, double y) {
	double floorx=(double)((int)x);//This is kinda a cheap way to floor a double integer.
	 double floory=(double)((int)y);
	 double s,t,u,v;//Integer declaration
	 s=noise2D(floorx,floory);
	 t=noise2D(floorx+1,floory);
	 u=noise2D(floorx,floory+1);//Get the surrounding pixels to calculate the transition.
	 v=noise2D(floorx+1,floory+1);
	 double int1=interpolate(s,t,x-floorx);//Interpolate between the values.
	 double int2=interpolate(u,v,x-floorx);//Here we use x-floorx, to get 1st dimension. Don't mind the x-floorx thingie, it's part of the cosine formula.
	 return interpolate(int1,int2,y-floory);
}

double Noise::interpolate(double a, double b, double x) {
	double ft = x * 3.1415927;
	double f = (1.0 - cos(ft)) * 0.5;
	return a * (1.0 - f) + b * f;
}

double Noise::noise2D(double x, double y) {
	int n = (int) x + (int) y * 57;
	n = (n << 13) ^ n;
	int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return 1.0 - ((double) nn / 1073741824.0);
}

