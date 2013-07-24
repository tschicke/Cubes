/*
 * CubeModel.h
 *
 *  Created on: Jul 23, 2013
 *      Author: Tyler
 */

#ifndef CUBEMODEL_H_
#define CUBEMODEL_H_

#include "BaseRenderer.h"

#include "ColorBlock.h"

class Entity;

class CubeModel: public BaseRenderer {
public:
	CubeModel();
	CubeModel(const char * fileName, Entity * parentEnity);
	virtual ~CubeModel();

	void init(const char * fileName, Entity * parentEnity);

	void markNeedsMatrixUpdate();

	void render();

	void loadModel(const char * fileName);
	void saveModel();
private:
	Entity * parentEntity;

	int numVertices, numVerticesToDraw;

	bool modelLoaded;

	ColorBlock * blockArray;

	bool modelMatNeedsUpdate;

	const char * fileName;
};

#endif /* CUBEMODEL_H_ */
