#ifndef TERRAIN_H
#define TERRAIN_H


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>


class Terrain{
public:
    Terrain();//constructor
    
    void render();//method

    //OPEN GL OBJECTS
    GLuint VAO, VBO, EBO;
    //TERRAIN DATA
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    //modelMatrix = glm::mat4(1.0f);
   // modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));

    
    //glm::mat4 modelMatrix;
    void setupTerrain();
  
};

#endif
