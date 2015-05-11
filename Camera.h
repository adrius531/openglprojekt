/*
 * Camera.h
 *
 *  Created on: May 4, 2015
 *      Author: adrian
 */

#ifndef CAMERA_H_
#define CAMERA_H_
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include <iostream>
using namespace std;
using namespace glm;
class Camera{
public:
	Camera();
	~Camera();
	//getCameraMatrix();
	//setProjection(float &fov, float &ratio, float &near, float &far);
	mat4& getViewMatrix();
	void moveCamera(double &xpos, double &ypos, GLFWwindow* window);
	void setDeltaTime(double &time);
	vec3 getPosition();
private:
	// Initial position : on +Z
	vec3 position = vec3( 0, 0, 5 );
	// Initial horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// Initial vertical angle : none
	float verticalAngle = 0.0f;
	// Initial Field of View
	float initialFoV = 45.0f;
	vec3 direction;
	vec3 up;
	vec3 right;
	mat4 view;
	float speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.0005f;
	double deltaTime;
};




#endif /* CAMERA_H_ */
