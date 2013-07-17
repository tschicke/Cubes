/*
 * GUIElement.h
 *
 *  Created on: Jul 14, 2013
 *      Author: Tyler
 */

#ifndef GUIELEMENT_H_
#define GUIELEMENT_H_

#include "GUIRenderer.h"

#include <glm/glm.hpp>

class GUIElement {
public:
	GUIElement();
	GUIElement(int width, int height);
	GUIElement(int x, int y, int width, int height);

	void init(int x, int y, int width, int height);

	virtual ~GUIElement();

	virtual void update() = 0;

	virtual void draw();

	bool isPointInBounds(glm::vec2 point);

	friend class GUIRenderer;

protected:
	int x, y;
	int width, height;

	bool needsUpdate;

	GUIRenderer renderer;
};

#endif /* GUIELEMENT_H_ */
