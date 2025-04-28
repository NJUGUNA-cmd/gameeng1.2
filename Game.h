#ifndef GAME_H
#define GAME_H

#include <glad.h>
#include<GLFW/glfw3.h>
#include"Cube.h"
#include"Terrain.h"
#include"shaderClass.h"
#include"Camera.h"
#include"grid.h"
//VARIABLE TO REPRESENT THE CURRENT STATE OF THE GAME
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN,
};
//holds all game-related state and functionality.
//combines all game-related data into a single class for easy access to each of the components and manageability.
class Game
{
public:

	//game state
	GameState State;

	unsigned int Width, Height;
	GLuint VAO, VBO, EBO;

	//camera object
	Camera* cam;
	

	//terrain object and shader
	Terrain* terrain;
	Shader* terrShader;

	Cube* cube;
	Shader* cubeShader;

	//cube object and shader
	Cube* box;
	Shader* boxShader;

	//grid object and shader
	GridSystem* grid;
	Shader* gridShader;

	float zoom;
	glm::vec2 offset;



	//constructor/destructor
	Game(unsigned int width, unsigned int height);
	~Game();
	//init game state load all shaders /textures/levels
	void Init();
	//Gameloop 
	void ProcessInput(GLFWwindow*window);
	void Update(float dt);
	void Render();
};
#endif // GAME_H