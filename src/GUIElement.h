/*
 * GUIElement.h
 *
 *  Created on: Jul 14, 2013
 *      Author: Tyler
 */

#ifndef GUIELEMENT_H_
#define GUIELEMENT_H_

class GUIElement {
public:
	GUIElement();
	GUIElement(int width, int height);
	GUIElement(int x, int y, int width, int height);

	void init(int x, int y, int width, int height);

	virtual ~GUIElement();

	virtual void update() = 0;

	void draw();

protected:
	int x, y;
	int width, height;

	bool needsUpdate;
};

#endif /* GUIELEMENT_H_ */
