/*
 * Layer.h
 *
 *  Created on: Jan 30, 2013
 *      Author: Tyler
 */

#ifndef LAYER_H_
#define LAYER_H_

#include <vector>

#include "Drawable.h"
#include "Common.h"

class Layer : public Drawable {
public:
	Layer();
	virtual ~Layer();

	void update(time_t dt);
	void draw(Renderer * renderer);

	void addChild(Drawable * drawable);
private:
	std::vector<Drawable *> children;
};

#endif /* LAYER_H_ */
