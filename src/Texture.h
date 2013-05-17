/*
 * Texture.h
 *
 *  Created on: Feb 20, 2013
 *      Author: Tyler
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

class Texture {
public:
	Texture();
	Texture(const char * texturePath);
	virtual ~Texture();

	static Texture *grassTexture, *dirtTexture, *stoneTexture, *blockSheet;
	static void initTextures();
	static void unbindTextures();

	void useTexture();

	int getHeight(), getWidth();

protected:
	bool loadDDS(const char * texturePath);

	bool loaded;
	unsigned int texID;

	int textureWidth, textureHeight;

};

#endif /* TEXTURE_H_ */
