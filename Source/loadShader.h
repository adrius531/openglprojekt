/*
 * readFile.h
 *
 *  Created on: Apr 25, 2015
 *      Author: adrian
 */

#ifndef LOADSHADER_H_
#define LOADSHADER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>

using namespace std;

GLint loadShader(const char *vsPath, const char *fsPath);




#endif /* LOADSHADER_H_ */
