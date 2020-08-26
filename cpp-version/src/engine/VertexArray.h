#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

class VertexArray
{
public:
	VertexArray(const float* verticesP, unsigned int nbVerticesP, const unsigned int* indicesP, unsigned int nbIndicesP);
	~VertexArray();

	void setActive();

	unsigned int getNbVertices() const { return nbVertices; }
	unsigned int getNbIndices() const { return nbIndices; }
private:
	unsigned int nbVertices;
	unsigned int nbIndices;

	// OpenGL ID of the vertex buffer
	unsigned int vertexBuffer;
	// OpenGL ID of the index buffer
	unsigned int indexBuffer;
	// OpenGL ID of the vertex array object
	unsigned int vertexArray;
};
#endif


