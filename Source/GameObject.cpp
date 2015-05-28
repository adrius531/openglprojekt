/*
 * GameObject.cpp
 *
 *  Created on: May 4, 2015
 *      Author: adrian
 */
#include "GameObject.h"

GameObject::GameObject(const char* objectPath, const char* texturePath, const char* normalmapPath, const char* heightmapPath, GLint shaderProgram, string name){
	model = new ModelLoader(objectPath, texturePath, normalmapPath, heightmapPath, shaderProgram);
	model->loadFile();

	model->setBuffers();
	model->setStandardUniformLocations();
	this->name = name;
}

GameObject::GameObject(const char* objectPath, const char* texturePath, const char* normalmapPath, GLint shaderProgram, string name){
	model = new ModelLoader(objectPath, texturePath, normalmapPath, shaderProgram);
	model->loadFile();

	model->setBuffers();
	model->setStandardUniformLocations();
	this->name = name;
}

GameObject::GameObject(const char* objectPath, const char* texturePath, GLint shaderProgram, string name){
	model = new ModelLoader(objectPath, texturePath, shaderProgram);
	model->loadFile();

	model->setBuffers();
	model->setStandardUniformLocations();
	this->name = name;
}


GameObject::~GameObject(){
	delete model;
}

void GameObject::draw(){
	model->draw();
}

void GameObject::setView(mat4 &view){
	model->setView(view);
}

void GameObject::setProjection(float &fov, float &ratio, float &near, float &far){
	mat4 projection = perspective(fov, ratio, near, far);
	model->setProjection(projection);
}

void GameObject::translate(vec3 trans){
	this->position += trans;
	model->translate(trans);
}

void GameObject::rotateAroundSelf(float angle, vec3 axis){
	this->rotation += angle * axis;
	model->rotateAroundSelf(angle, axis);
}

void GameObject::rotateAroundAxis(float angle, vec3 axis){
	model->rotateAroundAxis(angle, axis);
}

void GameObject::scale(vec3 scale){
	this->scalation += scale;
	model->scale(scale);
}

void GameObject::backToCenter(){
	model->backToCenter();
	position = vec3(0,0,0);
}

void GameObject::setLightPosition(vec3 lightPosition){
	model->lightPosition = lightPosition;
}

void GameObject::setCameraPosition(vec3 cameraPosition){
	model->cameraPosition = cameraPosition;
}
