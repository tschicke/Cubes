/*
 * Texture.cpp
 *
 *  Created on: Feb 20, 2013
 *      Author: Tyler
 */

#include <iostream>

#include <fstream>
#include <gl/glew.h>

#include "Texture.h"

Texture * Texture::buttonDefault, *Texture::buttonMouseOver, *Texture::buttonPressed;

int max(int a, int b) { //Temp?
	if (a > b)
		return a;
	else
		return b;
}

Texture::Texture() {
	loaded = false;
	texID = -1;
	textureWidth = -1;
	textureHeight = -1;
}

Texture::Texture(const char * texturePath) {
	loaded = loadDDS(texturePath);
}

Texture::~Texture() {

}

void Texture::initTextures(){
	buttonDefault = new Texture("res/Button1_default.DDS");
	buttonMouseOver = new Texture("res/Button1_mouseOver.DDS");
	buttonPressed = new Texture("res/Button1_pressed.DDS");
}

bool Texture::loadDDS(const char * texturePath) {
	if (!loaded) {
		std::ifstream file(texturePath, std::ios::binary);
		if (!file.is_open()) {
			std::cerr << "Couldn't open texture file, check path" << std::endl;
			return false;
		}

		char fileCode[4];
		file.read(fileCode, 4);
		if (*(unsigned int *) &fileCode[0] != 0x20534444) { //Make sure it is a DDS file
			file.close();
			std::cerr << "Wrong file format" << std::endl;
		}

		char header[124];
		file.read(header, 124);

		unsigned int image_height = *(unsigned int *) &header[2 * 4];
		unsigned int image_width = *(unsigned int *) &header[3 * 4];
		unsigned int linear_size = *(unsigned int *) &header[4 * 4];
		unsigned int mipmap_count = *(unsigned int *) &header[6 * 4];
		unsigned int pixel_format = *(unsigned int *) &header[20 * 4];

		textureWidth = image_width;
		textureHeight = image_height;

		unsigned int bufferSize = (mipmap_count > 1 ? linear_size * 1.5 : linear_size);
		unsigned char *buffer = new unsigned char[bufferSize];
		file.read((char *)buffer, bufferSize);
		file.close();

		unsigned int format;
		switch (pixel_format) {
		case 0x31545844: // Equivalent to "DXT1" in ASCII
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		case 0x33545844: // Equivalent to "DXT3" in ASCII
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
		case 0x35545844: // Equivalent to "DXT5" in ASCII
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
		default:
			std::cerr << "Unrecognized DDS format, not DXT1, DXT3, or DXT5" << std::endl;
			delete buffer;
			return false;
		}

		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);

		unsigned int block_size = ((format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16);
		unsigned int offset = 0;

		/*Load texture and mipmaps*/
		for (unsigned int level = 0; level < 1 && (image_width || image_height); level++) {
			unsigned int size = max((image_width / 4), 1) * max((image_height / 4), 1) * block_size;
			glCompressedTexImage2D(GL_TEXTURE_2D, level, format, image_width, image_height, 0, size, buffer + offset);

			offset += size;
			image_width /= 2;
			image_height /= 2;
		}
		delete buffer;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//Just for pixelated textures
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//Just for pixelated textures

		glBindTexture(GL_TEXTURE_2D, 0);

		return true;
	} else {
		return true;
	}
}

int Texture::getWidth(){
	return textureWidth;
}

int Texture::getHeight(){
	return textureHeight;
}

void Texture::useTexture(){
	if (loaded) {
		glBindTexture(GL_TEXTURE_2D, texID);
	}
}

void Texture::unbindTextures(){
	glBindTexture(GL_TEXTURE_2D, 0);
}
