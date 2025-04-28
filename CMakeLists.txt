cmake_minimum_required(VERSION 3.10)
project(gameeng)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set dependency paths
set(OPENGL_DEPS_DIR "C:/Users/IAN/source/repos/OpenGL")
set(GLFW_ROOT "C:/Program Files/GLFW")
set(GLFW_INCLUDE_DIR "${GLFW_ROOT}/include")
set(GLFW_LIBRARY "${GLFW_ROOT}/lib/libglfw3.a")

# Add source files
set(SOURCES
    Camera.cpp
    Cube.cpp
    EBO.cpp
    Game.cpp
    glad.c
    grid.cpp
    main.cpp
    shaderClass.cpp
    stb.cpp
    terrain.cpp
    Texture.cpp
    VAO.cpp
    VBO.cpp
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${OPENGL_DEPS_DIR}/include
    ${OPENGL_DEPS_DIR}/include/glad    # This makes <glad/glad.h> work
    ${OPENGL_DEPS_DIR}/include/glm     # This makes <glm/glm.hpp> work
    ${GLFW_INCLUDE_DIR}
)

# Link libraries directly
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${GLFW_LIBRARY}
    OpenGL::GL
    gdi32
)






