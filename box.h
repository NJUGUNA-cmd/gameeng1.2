#ifndef CUBE_H
#define CUBE_H

#include "Object.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

class Cube : public Object {
public://inherited from the Object class.

	//constructor to initialize the cube
	Cube();
	//destructor to clean up resources
	~Cube();

	void BindVAO();
	void updateModelMatrix(const glm::mat4& model)override;
	void setModelMatrix(const glm::mat4& model)override;
	void render()override;

private:
	glm::mat4 modelMatrix;
	VAO vao;
	VBO vbo;
	EBO ebo;

};
#endif