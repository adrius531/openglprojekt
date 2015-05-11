/*
 * Game.h
 *
 *  Created on: Apr 30, 2015
 *      Author: adrian
 */

#ifndef GAME_H_
#define GAME_H_
#include <algorithm>
#include <GL/glew.h>
#include "GLerror.h"
#include <GLFW/glfw3.h>
#include "ModelLoader.h"
#include "GameObject.h"
#include "Camera.h"
using namespace std;

class Game
{
public:
	Game(vector<GameObject*> &gameObjects, GLFWwindow* window, int windowHeight, int windowWidth, vec3 lightPosition);
	~Game();
	void render(float renderstep);
	void update();
	void processInput();
	void setWindow(GLFWwindow* window);
	void setDeltaTime(double time);
private:
	vector<GameObject*> gameObjects;
	GLFWwindow* window;
	int windowHeight;
	int windowWidth;
	double deltaTime;
	Camera* camera;
	vec3 lightPosition;
};

#endif /* GAME_H_ */
