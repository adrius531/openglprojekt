/*
 * GameObject.h
 *
 *  Created on: May 4, 2015
 *      Author: adrian
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include <string>
#include "ModelLoader.h"
#include <glm/glm.hpp>

using namespace std;
class GameObject{
public:
	GameObject(const char* objectPath, const char* texturePath, const char* normalmapPath, const char* heightmapPath, GLint shaderProgram, string name);
	GameObject(const char* objectPath, const char* texturePath, const char* normalmapPath, GLint shaderProgram, string name);
	GameObject(const char* objectPath, const char* texturePath, GLint shaderProgram, string name);
	~GameObject();
	void draw();
	void translate(vec3 trans);
	void rotateAroundSelf(float angle, vec3 axis);
	void scale(vec3 scale);
	void rotateAroundAxis(float angle, vec3 axis);
	void backToCenter();
	void setView(mat4 &view);
	void setProjection(float &fov, float &ratio, float &near, float &far);
	void setCameraPosition(vec3 cameraPosition);
	void setLightPosition(vec3 lightPosition);
private:
	vec3 position = vec3(0.0f, 0.0f, 0.0f);
	vec3 rotation = vec3(0.0f, 0.0f, 0.0f);
	vec3 scalation = vec3(0.0f, 0.0f, 0.0f);
	string name;
	ModelLoader* model;
};




#endif /* GAMEOBJECT_H_ */
