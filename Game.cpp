#include "Game.h"
#include <iostream>

#include "grid.h"
#include "Terrain.h"
#include "shaderClass.h"
#include "Cube.h"
#include"Camera.h"


//constructors and inits
Game::Game(unsigned int width, unsigned int height) :State(GAME_ACTIVE), Width(width), Height(height), zoom(1.0f), offset(0.0f,0.0f) {}

Game::~Game() {
	delete terrShader;
	delete terrain;
	delete box;
}

void Game::Init() {
	try {
		std::cout << "Game initialization starting..." << std::endl;
		std::cout.flush();

		// First, ensure all pointers are nullptr BEFORE initialization
		gridShader = nullptr;
		terrShader = nullptr;
		boxShader = nullptr;
		terrain = nullptr;
		box = nullptr;
		grid = nullptr;
		cam = nullptr;

		// Init the camera
		std::cout << "Initializing camera..." << std::endl;
		std::cout.flush();
		cam = new Camera(Width, Height, glm::vec3(0.0f, 0.0f, 3.0f));
		if (!cam) {
			throw std::runtime_error("Failed to create camera");
		}

		// Check if shader files exist before trying to load them
		std::cout << "Checking shader files..." << std::endl;
		const char* shaderFiles[] = {
			"../mandelbrot.vert",
			"../mandelbrot.frag",
			"../terrain.vert",
			"../terrain.frag",
			"../cube.vert",
			"../cube.frag"
		};

		for (const char* file : shaderFiles) {
			std::ifstream f(file);
			if (!f.good()) {
				throw std::runtime_error(std::string("Shader file not found: ") + file);
			}
			f.close();
		}

		// Init shader programs
		std::cout << "Loading shaders..." << std::endl;

		try {
			std::cout << "Creating mandelbrot shader..." << std::endl;
			gridShader = new Shader("../mandelbrot.vert", "../mandelbrot.frag");
			if (!gridShader || gridShader->ID == 0) {
				throw std::runtime_error("Failed to create mandelbrot shader");
			}

			std::cout << "Creating terrain shader..." << std::endl;
			terrShader = new Shader("../terrain.vert", "../terrain.frag");
			if (!terrShader || terrShader->ID == 0) {
				throw std::runtime_error("Failed to create terrain shader");
			}

			std::cout << "Creating cube shader..." << std::endl;
			boxShader = new Shader("../cube.vert", "../cube.frag");
			if (!boxShader || boxShader->ID == 0) {
				throw std::runtime_error("Failed to create cube shader");
			}

			std::cout << "All shaders created successfully" << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << "Shader creation failed: " << e.what() << std::endl;
			// Cleanup any successfully created shaders
			delete gridShader; gridShader = nullptr;
			delete terrShader; terrShader = nullptr;
			delete boxShader; boxShader = nullptr;
			throw;
		}

		// Initialize objects
		std::cout << "Initializing objects..." << std::endl;
		
		try {
			grid = new GridSystem(Width, Height);
			if (!grid) throw std::runtime_error("Failed to create grid system");

			terrain = new Terrain();
			if (!terrain) throw std::runtime_error("Failed to create terrain");

			box = new Cube();
			if (!box) throw std::runtime_error("Failed to create cube");
		}
		catch (const std::exception& e) {
			std::cerr << "Object initialization failed: " << e.what() << std::endl;
			// Cleanup
			delete grid; grid = nullptr;
			delete terrain; terrain = nullptr;
			delete box; box = nullptr;
			throw;
		}

		std::cout << "Initialization complete!" << std::endl;
		std::cout.flush();
	}
	catch (const std::exception& e) {
		std::cerr << "Error during game initialization: " << e.what() << std::endl;
		std::cerr.flush();
		throw;
	}
}
void Game::Update(float dt) {
	//make the model rotate and remember to scale it downafter other transformations
	cam->updateMatrix(45.0f, 0.1f, 100.0f);
	box->updateModelMatrix();
}

//
//kEY INPUTS HERE
//

void Game::ProcessInput(GLFWwindow*window) {
	cam->Inputs(window);
	//camera inputs for the cube
	//abstract later
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		box->Move(glm::vec3(0.0f, 0.0f, -0.1f));//forward

	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		box->Move(glm::vec3(0.0f, 0.0f,0.1f)); //backward one unit
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		box->Move(glm::vec3(0.1f, 0.0f, 0.0f));//right one unit

	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		box->Move(glm::vec3(-0.1f, 0.0f, 0.0f));//left one unit
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE == GLFW_PRESS)) {
		box->Move(glm::vec3(0.0f, 1.0f, 0.0f));

	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) zoom *= 1.05f;  // Zoom in
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) zoom /= 1.05f;  // Zoom out
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) offset.x -= 0.05f / zoom;  // Pan left
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) offset.x += 0.05f / zoom;  // Pan right
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) offset.y += 0.05f / zoom; // Pan up
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) offset.y -= 0.05f / zoom; //



}

void Game::Render(){

	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//
	//render the grid
	//

	gridShader->Activate();
	glm::mat4 view = cam->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)Width / Height, 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(gridShader->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(gridShader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glm::mat4 modelMatrix = glm::mat4(1.0f); // Identity matrix if no transformation
	glUniformMatrix4fv(glGetUniformLocation(gridShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	cam->Matrix(*gridShader,"camMatrix");
	glm::vec2 resolution(Width, Height);
	grid->renderMandelbrot(*gridShader, zoom, offset, resolution);

	//grid->renderGrid();
	/*cubeShader->Activate();
	glUniformMatrix4fv(glGetUniformLocation(cubeShader->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(cubeShader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	/*the render calls for the terrain*/
	//activate the shader program
	terrShader->Activate();
	
	//set up MODEL transformations matrices FOR THE TERRAIN
	//glm::mat4 model = glm::mat4(1.0f); //identity matrix lol
	glm::mat4 modelMatrix1(1.0f);
	modelMatrix1 = glm::translate(modelMatrix1, glm::vec3(0.0f, -1.0f, -5.0f));//move terrain back  and down

	modelMatrix1 = glm::scale(modelMatrix1,glm::vec3(5.0f, 1.0f, 5.0f));//scale down to half the screen


	//pass the matrices to the shader
	glUniformMatrix4fv(glGetUniformLocation(terrShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix1));
	glUniformMatrix4fv(glGetUniformLocation(terrShader->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(terrShader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	cam->Matrix(*terrShader, "camMatrix");
	//render terrain
	terrain->render();

	/*this are the render calls for the box*/
	//Activate the shader for the object
	boxShader->Activate();
	box->updateModelMatrix();
	glm::mat4 boxModel(1.0f);
	//boxModel = glm::translate(boxModel, glm::vec3(0.0f, 0.0f, -3.0f));
	boxModel = glm::scale(boxModel, glm::vec3(1.0f, 1.0f, 1.0f));
	//glm::mat4 viewbox = cam->cameraMatrix(*terrShader, "camMatrix");
	glm::mat4 projbox = glm::perspective(glm::radians(45.0f), (float)Width / Height, 0.1f, 100.0f);  // Perspective projection

	//pass to the shader
	glUniformMatrix4fv(glGetUniformLocation(boxShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(box->modelMatrix));
	//glUniformMatrix4fv(glGetUniformLocation(boxShader->ID, "view"), 1, GL_FALSE, glm::value_ptr(viewbox));
	glUniformMatrix4fv(glGetUniformLocation(boxShader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projbox));
	cam->Matrix(*boxShader, "camMatrix");
	//render the cube
	box->render();
}
