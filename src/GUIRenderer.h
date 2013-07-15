/*
 * GUIRenderer.h
 *
 *  Created on: Jul 14, 2013
 *      Author: Tyler
 */

#ifndef GUIRENDERER_H_
#define GUIRENDERER_H_

#include "BaseRenderer.h"

#include "Texture.h"

class GUIElement;

class GUIRenderer : public BaseRenderer {
public:
	GUIRenderer();
	GUIRenderer(GUIElement * parentElement, Texture * texture);

	void init(GUIElement * parentElement, Texture * texture);
	virtual ~GUIRenderer();

	void setCurrentTexture(Texture * texture);

	void render();
private:
	bool modelMatNeedsUpdate;//Should be in BaseRenderer?
	int numVerticesToDraw;//Should be in BaseRenderer?
	int numVertices;//Should be in BaseRenderer?

	GUIElement * parentElement;

	Texture * currentTexture;
};

#endif /* GUIRENDERER_H_ */
