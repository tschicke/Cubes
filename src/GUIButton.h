/*
 * GUIButton.h
 *
 *  Created on: Jul 15, 2013
 *      Author: Tyler
 */

#ifndef GUIBUTTON_H_
#define GUIBUTTON_H_

#include "GUIElement.h"

#include "StringRenderer.h"

class GUIButton : public GUIElement {
public:
	GUIButton();
	GUIButton(int width, int height, const char * buttonString);
	GUIButton(int x, int y, int width, int height, const char * buttonString);
	virtual ~GUIButton();

	void init(int x, int y, int width, int height, const char * buttonString);

	void update();
	void draw();

	bool wasPressed();
private:
	bool pressed;

	StringRenderer buttonString;
};

#endif /* GUIBUTTON_H_ */
