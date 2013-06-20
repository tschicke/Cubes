/*
 * Renderer.h
 *
 *  Created on: Feb 8, 2013
 *      Author: Tyler
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include <glm/glm.hpp>
#include <vector>

#include "Common.h"

enum ColorType {
	ColorType_Color, ColorType_Texture, ColorType_Default
};//Do this Differently?

struct MeshID {
public:

	MeshID();
	MeshID(ColorType type);
	virtual ~MeshID();

	uint *getVertexIDAddress(), *getIndexIDAddress();
	uint getVertexID(), getIndexID();

	void setNumVertices(uint numVertices);
	uint getNumVertices();

	ColorType getColorType();
	bool setColorType(ColorType newType);

	void reset();

	void operator=(MeshID meshID);
	bool operator==(MeshID meshID);
private:
	uint vertexID, indexID;
	uint numOfVertices;
	ColorType type;
};

class Renderer {
public:
	static Renderer& getMainRenderer();

	void renderMesh(MeshID meshID);

	void createMesh(MeshID * meshID); //Mesh type:COLOR, TEXTURE, etc. ??
	void endMesh(MeshID * meshID);
	void deleteMesh(MeshID * meshID);

	int addVertexToMesh(MeshID meshID, glm::vec3 position, glm::vec3 normal, float r, float g, float b);
	int addVertexToMesh(MeshID meshID, glm::vec3 position, glm::vec3 normal, float u, float v);

	void addTriangleToMesh(MeshID meshID, int vIndex1, int vIndex2, int vIndex3);
	void addLineToMesh(MeshID meshID, int vIndex1, int vIndex2);

	void addNullTriangle(MeshID meshID);
	void addNullQuad(MeshID meshID);
	void addNullCube(MeshID meshID);

	void startSubstituteData(MeshID meshID);
	void endSubstituteData(MeshID meshID, int startVertexIndex, int numberOfVertices);

	void createRectangle(MeshID meshID, glm::vec3 origin, float dx, float dy, float dz, float r, float g, float b);
	void createPrism(MeshID meshID, glm::vec3 origin, float dx, float dy, float dz);

	static void setProjectionMatrix(float fov, float width, float height, float zNear, float zFar);
	static glm::mat4* getProjectionMatrix();
private:
	Renderer();
	Renderer(const Renderer  &);
	Renderer& operator=(Renderer const& copy);

	MeshID currentMeshID; //??
	std::vector<float> currentData;
	std::vector<int> currentIndices;
	static glm::mat4 projectionMatrix;
};

#endif /* RENDERER_H_ */
