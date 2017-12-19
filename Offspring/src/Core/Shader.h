
#ifndef SHADER_H
#define SHADER_H

#include <GL\glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm.hpp>

class Shader
{
public:
	//the program ID
	GLuint ID;

public:
	Shader( const GLchar* vertexPath, const GLchar * fragmentPath);
	Shader(const GLchar * vertexPath, const GLchar* geometryPath, const GLchar* fragmentPath);
	~Shader();
	void use() const { glUseProgram(ID); };
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec2(const std::string &name, const glm::vec2 &value) const;
	void setVec2(const std::string &name, float x, float y) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec4(const std::string &name, const glm::vec4 &value)const;
	void setVec4(const std::string &name, float x,float y,float z, float w)const;
	void setMat2(const std::string &name, glm::mat2 &mat) const;
	void setMat3(const std::string &name, glm::mat3 &mat) const;
	void setMat4(const std::string &name, glm::mat4 &mat) const;
};

#endif