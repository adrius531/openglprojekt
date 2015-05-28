/*
 * Camera.cpp
 *
 *  Created on: May 4, 2015
 *      Author: adrian
 */
#include "Camera.h"

Camera::Camera():deltaTime(0){

}
Camera::~Camera(){

}

mat4& Camera::getViewMatrix(){
	view = lookAt(
            position,           // Camera is here
            position+direction, // and looks here : at the same position, plus "direction"
            up                  // Head is up (set to 0,-1,0 to look upside-down)
			);
	return view;
}

void Camera::moveCamera(double &xpos, double &ypos, GLFWwindow* window){

	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window, width/2, height/2);
	horizontalAngle += mouseSpeed * float(width/2 - xpos );
	verticalAngle   += mouseSpeed * float( height/2 - ypos );
    direction = vec3(
				cos(verticalAngle) * sin(horizontalAngle),
				sin(verticalAngle),
				cos(verticalAngle) * cos(horizontalAngle)
				);
    // Right vector
	right = vec3(
			sin(horizontalAngle - 3.14f/2.0f),
			0,
			cos(horizontalAngle - 3.14f/2.0f)
	);
	// Up vector
	up = cross( right, direction );
	// Move forward
	if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
			position += direction * (float)deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
			position -= direction * (float)deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
			position += right * (float)deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
			position -= right * (float)deltaTime * speed;
	}
}

void Camera::setDeltaTime(double &time){
	deltaTime = time;
}

vec3 Camera::getPosition(){
	cout << "Position: (" << this->position.x <<", " << this->position.y<<", " <<this->position.z<<")"<<endl;
	return this->position;
}
