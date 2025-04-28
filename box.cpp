#include "box.h"
#include "Object.h"

Cube::Cube() {
    // Initialize VAO, VBO, EBO and set up vertex data
    GLfloat cubeVertices[] = {
        // COORDINATES
        -0.1f, -0.1f,  0.1f,
        -0.1f, -0.1f, -0.1f,
         0.1f, -0.1f, -0.1f,
         0.1f, -0.1f,  0.1f,
        -0.1f,  0.1f,  0.1f,
        -0.1f,  0.1f, -0.1f,
         0.1f,  0.1f, -0.1f,
         0.1f,  0.1f,  0.1f
    };

    GLuint cubeIndices[] = {
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

    //model identity matrix for the transformation, rotation and scaling
    modelMatrix = glm::mat4(1.0f);
    // Initialize the shader program
   
    // Generate and bind VAO
    vao.Bind();

    // Generate VBO and link it to vertices
    vbo = VBO(cubeVertices, sizeof(cubeVertices));

    // Generate EBO and link it to indices
    
    ebo = EBO(cubeIndices, sizeof(cubeIndices));
    
    // Link VBO attributes such as coordinates to VAO
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    // Unbind all to prevent accidental modifications
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}

void Cube::setModelMatrix(const glm::mat4& model) {
    // Update the model matrix based on transformations
    modelMatrix = model;
}

void Cube::updateModelMatrix(const glm::mat4& model) {
    // Update the model matrix
    modelMatrix = model;  // Identity matrix for now
}

Cube::~Cube() {
    //cleanup (OpenGL resources are typically cleaned up when the context is destroyed)
    
}
void Cube::BindVAO() {
    vao.Bind();
}
void Cube::render() {
    BindVAO();//bindVAO B4 DRAWING
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}