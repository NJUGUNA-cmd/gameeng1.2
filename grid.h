#ifndef GRID_SYSTEM_H
#define GRID_SYSTEM_H

#include <glad.h>
#include <vector>
#include "Cube.h"
#include "shaderClass.h"
#include <glm/glm.hpp>

class GridSystem {
private:
    unsigned int VAO, VBO;

public:
    // Only declarations here, NO implementations
    GridSystem(int windowWidth, int windowHeight);
    void renderMandelbrot(Shader& shader, float zoom, glm::vec2 offset, glm::vec2 resolution);
};

#endif
