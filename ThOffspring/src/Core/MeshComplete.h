#pragma once
#ifndef _MESH_COMPLETE_H
#define _MESH_COMPLETE_H
#include <iostream>
#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <string>
#include "Shader.h"
#include <assimp\Importer.hpp>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
	aiString path;
};

class MeshComplete
{
public:
	MeshComplete(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader shader);
	~MeshComplete();
private:
	void setupMesh();
public:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<Texture> m_textures;
private:
	unsigned int VAO, VBO, EBO;
};

#endif // !_MESH_COMPLETE_H

