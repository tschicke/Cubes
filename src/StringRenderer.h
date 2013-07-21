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
	virtual ~StringRenderer();

	void init(int x, int y, const char * string, int fontSize);

	static int getWidthOfString(const char * string, int fontSize);

	void render();

	void setPosition(int x, int y);

	void setString(const char * string);
	void appendToString(const char * string, int numChars);
private:
	int x, y;

	int numVertices, numVerticesToDraw;

	bool modelMatNeedsUpdate;

	uint allocLength;

	void rebuildData();

	std::string renderString;

	int fontSize;
};

#endif /* STRINGRENDERER_H_ */
