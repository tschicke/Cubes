/*
 * GUIButton.h
 *
 *  Created on: Jul 15, 2013
 *      Author: Tyler
 */

#ifndef GUIBUTTON_H_
#define GUIBUTTON_H_

#include "GUIElement.h"

class GUIButton : public GUIElement {
public:
	GUIButton();
	GUIButton(int width, int height);
	GUIButton(int x, int y, int width, int height);
	virtual ~GUIButton();

	void update();

	bool wasPressed();
private:
	bool pressed;
};

#endif /* GUIBUTTON_H_ */
