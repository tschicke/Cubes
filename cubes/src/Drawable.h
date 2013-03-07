/*
 * Drawable.h
 *
 *  Created on: Feb 2, 2013
 *      Author: Tyler
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <GL/glew.h>

#include "Common.h"

#include "Renderer.h"

class Drawable {
public:
	Drawable();
	virtual ~Drawable();

	virtual void update(time_t dt) = 0;
	virtual void draw(Renderer * renderer) = 0;
};

#endif /* DRAWABLE_H_ */
