#include "grid.h"

// Implementation of constructor
GridSystem::GridSystem(int windowWidth, int windowHeight) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    float vertices[] = {
        -1.0f,  1.0f, 0.0f,  // Top-left
         1.0f,  1.0f, 0.0f,  // Top-right
         1.0f, -1.0f, 0.0f,  // Bottom-right
        -1.0f, -1.0f, 0.0f   // Bottom-left
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// Implementation of renderMandelbrot
void GridSystem::renderMandelbrot(Shader& shader, float zoom, glm::vec2 offset, glm::vec2 resolution) {
    shader.Activate();
    glUniform2f(glGetUniformLocation(shader.ID, "uResolution"), resolution.x, resolution.y);
    glUniform1f(glGetUniformLocation(shader.ID, "uZoom"), zoom);
    glUniform2f(glGetUniformLocation(shader.ID, "uOffset"), offset.x, offset.y);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}

