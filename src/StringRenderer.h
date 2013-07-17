/*
 * StringRenderer.h
 *
 *  Created on: Jul 16, 2013
 *      Author: Tyler
 */

#ifndef STRINGRENDERER_H_
#define STRINGRENDERER_H_

#include "BaseRenderer.h"

#include "Common.h"

#include <string>

class StringRenderer: public BaseRenderer {
public:
	StringRenderer();
	StringRenderer(int x, int y, const char * string);
	virtual ~StringRenderer();

	void render();

	void setString(const char * string);
	void appendToString(const char * string, int numChars);
private:
	int x, y;

	int numVertices, numVerticesToDraw;

	bool modelMatNeedsUpdate;

	uint allocLength;

	void rebuildData();

	std::string renderString;
};

#endif /* STRINGRENDERER_H_ */
