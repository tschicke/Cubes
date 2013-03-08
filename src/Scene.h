/*
 * Scene.h
 *
 *  Created on: Jan 30, 2013
 *      Author: Tyler
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <GL/glew.h>
#include <vector>
#include <SFML/Window/Event.hpp>

#include "Chunk.h"
#include "Common.h"

class Scene {//: public Drawable{
public:
	Scene();
	virtual ~Scene();

	void handleInput(sf::Event event);
	void update(time_t dt);
	void draw(Renderer * renderer);

	void addChild(Chunk * drawable);
private:
	std::vector<Chunk *> children;//TODO necessary in Scene class??
};

#endif /* SCENE_H_ */
