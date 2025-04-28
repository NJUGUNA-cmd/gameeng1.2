#include "Terrain.h"
// Terrain.cpp

Terrain::Terrain() {
    // Define vertices and indices for a flat terrain
    vertices = {
        -1.0f, -1.0f, 0.0f, //bottom-left
         1.0f, -1.0f, 0.0f,//bottom-right
         1.0f, 1.0f,  0.0f,//top-right
        -1.0f, 1.0f,  0.0f//top-left
    };
    indices = {
        0, 1, 2,
        0, 2, 3
    };
    //SETS UP THE TERRAIN OPENGL BUFFERS
     glm::mat4 modelMatrix(1.0f);  // Initialize model matrix to identity
   
    setupTerrain();
   
}

void Terrain::setupTerrain() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}


void Terrain::render() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
