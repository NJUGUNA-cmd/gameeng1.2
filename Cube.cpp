#include"Cube.h"
//#include<glad/glad.h>

Cube::Cube() {
	//Initialize VAO, VBO, EBO and set up vertex data
	//(Add your vertex data and buffer setup here)
	 cubeVertices = {
		//     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f

	};
	 cubeIndices = {
		0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
	};
	//generate shader objects using shaders default.vert and default.frag
	//initializing the shader program
	//Shader cubeShader("light.vert", "light.frag");
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//bind the attributes
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, cubeVertices.size() * sizeof(GLfloat), &cubeVertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeIndices.size() * sizeof(GLfloat), &cubeIndices[0], GL_STATIC_DRAW);

	//link the attributes
	glVertexAttribPointer(0, 3,GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	//init model Matrix
	modelMatrix = glm::mat4(1.0f);
	position = glm::vec3(0.0f, 0.0f,0.0f);
	direction = glm::vec3(0.0f, 0.0f, 0.0f);
	angle = glm::radians(5.0f);
	axis = glm::vec3(0.0f, 0.0f, 0.0f);
	

}
void Cube::Move(const glm::vec3& direction) {
	position += direction;
	updateModelMatrix();
}
void Cube::Rotate(const glm::vec3& axis) {
	float angle = glm::radians(5.0f);
	modelMatrix = glm::rotate(modelMatrix, angle, axis);
}

void Cube::updateModelMatrix() {
	//Update the model matrix based on transformations
	modelMatrix = glm::translate(glm::mat4(1.0f), position);//Identity matrix for now
}

void Cube::render() {
	//bind vao
	glBindVertexArray(VAO);

	//now render the cube
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);//Assuming 36 indices for a cube

	//UNBIND VAO 
	glBindVertexArray(0);
}
//add a delete call if unbinding doesnt work