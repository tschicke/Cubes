/*
 * Texture.h
 *
 *  Created on: Feb 20, 2013
 *      Author: Tyler
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

class Texture {//TODO Make spritesheet class?
public:
	Texture();
	Texture(const char * texturePath);
	virtual ~Texture();

	static Texture *grassTexture, *dirtTexture, *stoneTexture;
	static void initTextures();
	static void unbindTextures();

	void useTexture();//TODO should be static useTexture(Texture *texture)?

private:
	bool loadDDS(const char * texturePath);

	bool loaded;
	unsigned int texID;

};

#endif /* TEXTURE_H_ */
