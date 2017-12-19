#ifndef _MESH_H
#define _MESH_H
#include <iostream>
#include <GLEW\include\GL\glew.h>
#include <glm\glm.hpp>


struct Vertex
{
	glm::vec3 pos;
	glm::vec2 TexCoord;
};

class Mesh
{
public:
	//Mesh(Vertex * vertices , unsigned int numVertices);
	Mesh(float  * vertices , unsigned int numVertices , unsigned int numAttrib);
	void Bind();
	void Draw();

	virtual ~Mesh();
private: 
	enum 
	{
		POSITION_VB,

		NUM_BUFFERS
	};

	GLuint m_VAO;
	GLuint m_VAB[NUM_BUFFERS];
	unsigned int m_drawCount;
};

#endif // !_MESH_H



