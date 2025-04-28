#include"Scene.h"


Scene::Scene() {}

Scene::~Scene() {
	//clean up resources if nedded 
	for (Object* obj : objects) {
		delete obj;//if scene owns objects and is responsible for removing them
	}
}

void Scene::addObject(Object* obj) {
	if (obj) {
		objects.push_back(obj);
	}
}

void Scene::render(Shader& shader, Camera& camera) {
	
	shader.Activate();
	camera.Matrix(shader, "view", "projection");

	for (Object* obj : objects) {
		
		if (obj) {
			//set the model matrix for the shader
			shader.setMat4("model", obj->modelMatrix);

			//render obj
			obj->render();
		}
	}
}