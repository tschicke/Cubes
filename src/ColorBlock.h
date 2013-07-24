/*
 * ColorBlock.h
 *
 *  Created on: Jul 24, 2013
 *      Author: Tyler
 */

#ifndef COLORBLOCK_H_
#define COLORBLOCK_H_

#include <glm/glm.hpp>

class ColorBlock {
public:
	ColorBlock();
	virtual ~ColorBlock();

	void setDrawn(bool drawn);
	bool isDrawn();

	void setColor(glm::vec3 color);
	glm::vec3 getColor();

private:
	bool drawn;
	glm::vec3 color;
};

#endif /* COLORBLOCK_H_ */
