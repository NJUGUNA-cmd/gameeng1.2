#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#include "Game.h"
#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

const unsigned int width = 1080;
const unsigned int height = 1050;

Game gamestart(1680, 1050);
int main() {
    try {
        std::cout << "Starting program..." << std::endl;
        std::cout.flush();

        // Initialize GLFW
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            std::cerr.flush();
            system("pause");  // Add pause
            return -1;
        }
        std::cout << "GLFW initialized" << std::endl;
        std::cout.flush();

        // Tell GLFW what version of OpenGL we are using 
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create a GLFWwindow object
        GLFWwindow* window = glfwCreateWindow(width, height, "mkurugenzifcs", NULL, NULL);
        if (window == NULL) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            std::cerr.flush();
            glfwTerminate();
            return -1;
        }
        std::cout << "Window created" << std::endl;
        std::cout.flush();
        
        // Introduce the window into the current context
        glfwMakeContextCurrent(window);

        // Load GLAD
        if (!gladLoadGL()) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            std::cerr.flush();
            return -1;
        }
        std::cout << "GLAD initialized" << std::endl;
        std::cout.flush();

        // Specify the viewport
        glViewport(0, 0, width, height);

        // Enable depth testing
        glEnable(GL_DEPTH_TEST);

        // Initialize game
        std::cout << "Initializing game..." << std::endl;
        std::cout.flush();
        gamestart.Init();

        // Main game loop
        while (!glfwWindowShouldClose(window)) {
            gamestart.ProcessInput(window);
            gamestart.Update(0.016f);
            gamestart.Render();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
    }
    catch (int e) {
        std::cerr << "Fatal error: Integer exception thrown with value " << e << std::endl;
        std::cerr.flush();
        system("pause");  // Add pause
        return -1;
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        std::cerr.flush();
        system("pause");  // Add pause
        return -1;
    }
    catch (...) {
        std::cerr << "Unknown fatal error occurred" << std::endl;
        std::cerr.flush();
        system("pause");  // Add pause
        return -1;
    }
}



