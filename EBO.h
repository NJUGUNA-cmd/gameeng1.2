#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	//ID reference of Elements Buffer Object
	GLuint ID;
	//Constructor that generates Elements buffer objects and links it to indices
	EBO(GLuint* indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();

};

#endif
