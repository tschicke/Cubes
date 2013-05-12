/*
 * SpriteSheet.h
 *
 *  Created on: May 12, 2013
 *      Author: Tyler
 */

#ifndef SPRITESHEET_H_
#define SPRITESHEET_H_

#include "Texture.h"

namespace ts {

class SpriteSheet : public Texture {
public:
	SpriteSheet();
	SpriteSheet(const char * texturePath);
	virtual ~SpriteSheet();

	static SpriteSheet *defaultSpriteSheet;

	static void initSpriteSheets();//should just be done when first trying to use it and not loaded?

	int getElementSizePixels();
protected:
};

} /* namespace ts */
#endif /* SPRITESHEET_H_ */
