#include "Texture.h"


Texture::Texture(const char * * path, unsigned int numberTex ,GLenum * format ,const Shader & shader , const char ** uniformNames)
{
	Num = numberTex;
	ID = new unsigned int[numberTex];
	glGenTextures(numberTex, ID);
	stbi_set_flip_vertically_on_load(true);
	for (size_t i = 0; i < numberTex; i++)
	{
		int width, height, nrChannels;
		unsigned char * data = stbi_load(path[i], &width, &height, &nrChannels, 0);
		if (data)
		{
			glBindTexture(GL_TEXTURE_2D, ID[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, width, height, 0, format[i], GL_UNSIGNED_BYTE, data);//TODO auto dectec format using nrChannesl
			glGenerateMipmap(GL_TEXTURE_2D); 

			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else {
			std::cout << "Failed to load texture" << "\n";
		}
		stbi_image_free(data);
	}
	shader.use();
	for (size_t i = 0; i < Num; i++)
	{
		shader.setInt(uniformNames[i],i);
	}
}

void Texture::Bind()
{
	for (size_t i = 0; i < Num; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, ID[i]);
	}
}

Texture::~Texture()
{
	delete[] ID;
}
