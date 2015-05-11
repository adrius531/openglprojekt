/*
 * keyCallback.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: adrian
 */
#include "keyCallback.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


