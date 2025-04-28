#ifndef OBJECT_H
#define OBJECT_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include "shaderClass.h"

class Object {
public:
	virtual ~Object() = default;
	virtual void updateModelMatrix(const glm::mat4&model)=0;
	virtual void setModelMatrix(const glm::mat4& model) = 0;
	virtual void render() = 0;


	glm::mat4 modelMatrix;
};
#endif