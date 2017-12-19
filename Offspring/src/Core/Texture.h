
#ifndef TEXTURE_H
#define TEXTURE_H
#include <iostream>
#include <GL\glew.h>
#include "stb_image.h"
#include "Shader.h"

class Texture
{
private:
	unsigned int * ID;
	unsigned int Num;

public:
	Texture(const char * * path, unsigned int numberTex,GLenum * format, const Shader & shader, const char ** uniformNames);
	void Bind();
	unsigned int getID() {
		return *ID;
	}
	~Texture();
};

#endif // !TEXTURE_H

