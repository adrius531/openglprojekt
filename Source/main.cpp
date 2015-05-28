/*
 * main.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: adrian
 */
#define MS_PER_UPDATE 0.017

#include <iostream>
#include <chrono>
#include <thread>

#include "keyCallback.h"
#include "loadShader.h"
#include "ModelLoader.h"
#include "Game.h"
#include <GL/glew.h>
#include "GLerror.h"
#include <GLFW/glfw3.h>

using namespace std;
using namespace glm;
int WIDTH = 800, HEIGHT = 600;
vec3 lightPos = vec3(1.0f, -5.0f, 2.0f);

int main(){
	float fov = 45.0f;
	float ratio = (float)WIDTH / (float)HEIGHT;
	float near = 0.01f;
	float far = 1000.0f;

	vec3 trans;
	vec3 scale;
	vec3 rotate;
	if(!glfwInit()){
		cerr << "Failed to initialize GLFW" << endl;
		return -1;
	}

	//glfwWindowHint(GLFW_SAMPLES, 4); //4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //No old OpenGL
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Tut1", NULL, NULL);
	if(window == NULL){
		cerr << "Failed to open GLFW window." << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK){
		cerr << "Failed to initialize GLEW" << endl;
		return -1;
	}

	glViewport(0, 0, WIDTH, HEIGHT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_TEXTURE_2D);

	//Shader Program erzeugen
	GLint shaderProgram = loadShader("Shader/normalmapping.vs", "Shader/normalmapping.fs");
	GLint simpleShader = loadShader("Shader/simple.vs", "Shader/simple.fs");
	GLint reliefShader = loadShader("Shader/reliefmapping.vs", "Shader/reliefmapping.fs");
	GLint tesselationShader = loadShader("Shader/tesselation.vs", "Shader/tesselation.fs");
	cout << "shader position: "<< shaderProgram << endl;
	cout << "shader position: "<< simpleShader << endl;
	//Primitve erzeugen
	GameObject *sphere2;
	sphere2 = new GameObject("Models/sphere2.obj", "Models/cobblestone1.jpg", "Models/cobblestone_displace.png", tesselationShader, "Sphere2");
	sphere2->setProjection(fov, ratio, near, far);
	sphere2->translate(vec3(-3.0f, 0.0f, 2.0f));

	GameObject *sphere;
	sphere = new GameObject("Models/sphere2.obj", "Models/wood_texture.jpg", "Models/wood_normalmap.jpg", tesselationShader, "Sphere");
	sphere->setProjection(fov, ratio, near, far);
	sphere->translate(vec3(0.0f, 2.0f, -1.0f));
/*
	GameObject *cube;
	cube = new GameObject("Models/kubus.obj", "Models/wood_texture.jpg", "Models/wood_normalmap.jpg", "Models/wood_height.jpg", tesselationShader, "Cube");
	cube->setProjection(fov, ratio, near, far);
	cube->translate(vec3(2.0f, 0.0f, -3.0f));
*/
	vector<GameObject*> gameObjects;
	gameObjects.push_back(sphere2);
	gameObjects.push_back(sphere);

	//gameObjects.push_back(cube);
	Game game = Game(gameObjects, window, HEIGHT, WIDTH, lightPos);

	double previous = glfwGetTime();
	double lag = 0.0;
	while(!(glfwWindowShouldClose(window))){

		double current = glfwGetTime();
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;
		//cout << "LAG " << lag << endl;
		game.setDeltaTime(elapsed);
		game.processInput();

		while (lag >= MS_PER_UPDATE)
		{
			game.update();
			lag -= MS_PER_UPDATE;
		}

		game.render(lag/MS_PER_UPDATE);



		//model = rotate(model, 0.5f, vec3(0.0f, 1.0f, 0.0f));


		//Draw
		//modelLoader->rotateAroundAxis(a, r);
		//modelLoader->draw();
		//Buffer Swap
		glfwSwapBuffers(window);
	}
	//Delete

	//delete modelLoader;
	glfwTerminate();
	return 0;

}


