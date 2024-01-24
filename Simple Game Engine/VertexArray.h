#pragma once

constexpr float vertices[] = {
	-0.5f,0.5f,0,	//0,0, //Top Left
	0.5f,0.5f,0,	//1,0, //Top Right
	-0.5f,-0.5f,0,	//1,1, //Bottom Left
	0.5f,-0.5f,0	//0,1, //Bottom Right
};

constexpr unsigned int indices[] = {
	0,1,2,
	2,3,0
};

class VertexArray
{
public:
	VertexArray(const float* verticesP, unsigned int nbVerticesP, const unsigned int* indicesP, unsigned int nbIndicesP);
	~VertexArray();

	void setActive();

	unsigned int getNbVertices() const { return nbVertices; };
	unsigned int getNbIndices() const { return nbIndices; };

private:
	unsigned int nbVertices;
	unsigned int nbIndices;

	unsigned int vertexArray;
	unsigned int vertexBuffer;
	unsigned int indexBuffer;
};

