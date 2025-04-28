#ifndef CUBE_H
#define CUBE_H


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

class Cube {
public:
	GLuint VAO, VBO, EBO;
	std::vector<GLfloat>cubeVertices;
	std::vector<GLint>cubeIndices;
	glm::mat4 modelMatrix;
	glm::vec3 position;
	glm::vec3 direction;
	float angle;
	glm::vec3 axis;


	Cube();
	void Move(const glm::vec3& direction);

	void Rotate(const glm::vec3& axis);
	
	void updateModelMatrix();
	void render();
};
#endif