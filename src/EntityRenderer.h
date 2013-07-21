/*
 * EntityRenderer.h
 *
 *  Created on: Jun 29, 2013
 *      Author: Tyler
 */

#ifndef ENTITYRENDERER_H_
#define ENTITYRENDERER_H_

#include "BaseRenderer.h"

class Entity;

class EntityRenderer: public BaseRenderer {
public:
	EntityRenderer();
	virtual ~EntityRenderer();

	void init(Entity * parent, const char * modelFile);

	void render();

	void markNeedsMatrixUpdate();
protected:
	Entity * parentEntity;

	bool modelMatNeedsUpdate;

	virtual void loadModel(const char * modelFile);

	int numVerticesToDraw;
	int numVertices;
};

#endif /* ENTITYRENDERER_H_ */
