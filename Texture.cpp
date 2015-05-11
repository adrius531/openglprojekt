/*
 * Texture.cpp
 *
 *  Created on: Apr 28, 2015
 *      Author: adrian
 */
#include "Texture.h"
#include <iostream>
Texture::Texture(const char* imagePath) : width(0), height(0), image(0), location(0), textureLocation(0){
	//image = SOIL_load_image(imagePath, &width, &height, 0, SOIL_LOAD_RGB);
	texture = SOIL_load_OGL_texture(imagePath, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT);
	//SOIL_free_image_data(image);
	//image = imagePath;
	if (texture == NULL){
		cout << imagePath << " Problem! Fehler: " << SOIL_last_result()  << endl;
	}
}

Texture::~Texture(){
	 glDeleteTextures(1, &texture);
}

void Texture::setTexture(GLint shaderProgram, GLint location, const char* texture_name){
	textureLocation = glGetUniformLocation(shaderProgram, texture_name);
	this->location = location;
	//glGenTextures(1, &texture);
	//glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//glActiveTexture(GL_TEXTURE0 + location);

	// when texture area is small, bilinear filter the closest mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// when texture area is large, bilinear filter the first mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);


	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);

	// texture should tile
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// build our texture mipmaps
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);

}

void Texture::bind(){
	glActiveTexture(GL_TEXTURE0 + location);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(textureLocation, location);

}

void Texture::unbind(){
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getTextureLoc(){
	return textureLocation;
}

GLuint Texture::getTexture(){
	return texture;
}
