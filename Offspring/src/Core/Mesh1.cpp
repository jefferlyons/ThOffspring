#include "Mesh1.h"


Mesh::Mesh(float  * vertices, unsigned int numVertices, unsigned int numAttrib)
{
	m_drawCount = numVertices;

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(NUM_BUFFERS, m_VAB);
	glBindBuffer(GL_ARRAY_BUFFER, m_VAB[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_drawCount * sizeof(float) * numAttrib, vertices, GL_STATIC_DRAW );

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, numAttrib * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, numAttrib * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, numAttrib * sizeof(float), (void*) (6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}



//Mesh::Mesh(Vertex * vertices, unsigned int numVertices)
//{
//	m_drawCount = numVertices;
//
//	glGenVertexArrays(1, &m_VAO);
//	glBindVertexArray(m_VAO);
//
//	glGenBuffers(NUM_BUFFERS, m_VAB);
//	glBindBuffer(GL_ARRAY_BUFFER, m_VAB[NUM_BUFFERS]);
//	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) + sizeof(glm::vec2), (void*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) + sizeof(glm::vec2), (void*) sizeof(glm::vec3));
//	glEnableVertexAttribArray(1);
//	glBindVertexArray(0);
//}


void Mesh::Draw() {
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
	glBindVertexArray(0);
}

void Mesh::Bind() {
	glBindVertexArray(m_VAO);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VAO);
}
