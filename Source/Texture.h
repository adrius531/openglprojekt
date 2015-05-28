/*
 * Texture.h
 *
 *  Created on: Apr 28, 2015
 *      Author: adrian
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL/SOIL.h>
#include "GLerror.h"

using namespace std;
using namespace glm;
class Texture
{
public:
	Texture(const char* filePath);
	~Texture();
	void setTexture(GLint shaderProgram, GLint location, const char *texture_name);
	GLuint getTextureLoc();
	void bind();
	void unbind();
	GLuint getTexture();
private:
	int width, height;
	unsigned char* image;
	GLuint texture;
	GLint location;
	GLuint textureLocation;
};



#endif /* TEXTURE_H_ */
