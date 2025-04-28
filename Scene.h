#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include"Camera.h"
#include"shaderClass.h"
#include"object.h"

class Scene {
public:
	Scene();
	~Scene();
	
	void addObject(Object* obj);
	//void Update(float dt);
	void render(Shader& shader, Camera& camera);


	std::vector<Object*>objects;


};
#endif 