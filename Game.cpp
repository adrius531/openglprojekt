/*
 * Game.cpp
 *
 *  Created on: Apr 30, 2015
 *      Author: adrian
 */
#include "Game.h"

Game::Game(vector<GameObject*> &gameObjects, GLFWwindow* window, int windowHeight, int windowWidth, vec3 lightPosition) : deltaTime(0){
	this->gameObjects = gameObjects;
	this->window = window;
	this->windowHeight = windowHeight;
	this->windowWidth = windowWidth;
	this->lightPosition = lightPosition;
	camera = new Camera();
}

Game::~Game(){
	for (GameObject* gameObject : gameObjects){
		delete gameObject;
	}
	delete camera;
}

void Game::render(float renderstep){

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (GameObject* gameObject : gameObjects){
		gameObject->draw();
	}


}

void Game::processInput(){
	glfwPollEvents();
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	camera->moveCamera(xpos, ypos, window);
	for (GameObject* gameObject : gameObjects){
		gameObject->setView(camera->getViewMatrix());
	}

}

void Game::update(){
	for (GameObject* gameObject : gameObjects){
		gameObject->setCameraPosition(camera->getPosition());
		gameObject->setLightPosition(lightPosition);
		//gameObject->rotateAroundSelf(0.5f, vec3(1.0f, 0.0f, 0.0f));
	}
}

void Game::setDeltaTime(double time){
	deltaTime = time;
	camera->setDeltaTime(time);
}



