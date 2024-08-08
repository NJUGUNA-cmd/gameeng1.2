#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb_image.h>
#include"shaderClass.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	//assign a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	//binds a texture
	void Bind();
	//unbinds
	void Unbind();
	//deletes a Texture
	void Delete();

};
#endif