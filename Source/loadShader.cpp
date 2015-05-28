/*
 * readFile.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: adrian
 */
#include "loadShader.h"

using namespace std;

string readFile(const char *filePath){
	string content;
	ifstream fileStream(filePath, ios::in);
	if(!fileStream.is_open()){
		cerr << "Kann nicht geoeffnet werden. " << filePath << " existiert nicht." << endl;
		return "";
	}
	string line = "";
	while (getline(fileStream, line)){
		content.append(line +"\n");
	}
	fileStream.close();
	return content;
}

void printShaderSuccess(GLint shader){
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		cerr << "Fehler VertexShader: " << endl << infoLog << endl;
	}
}

void printProgramSuccess(GLint program){
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if(!success){
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		cerr << "Fehler ShaderProgram: " << infoLog << endl;
	}
}

GLint loadShader(const char *vsPath, const char *fsPath){

	string vsSourceStr = readFile(vsPath);
	string fsSourceStr = readFile(fsPath);
	const GLchar* vsSource = vsSourceStr.c_str();
	const GLchar* fsSource = fsSourceStr.c_str();
	GLint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vsSource, NULL);
	glCompileShader(vShader);
	//Erfolgreich?
	printShaderSuccess(vShader);
	GLint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fsSource, NULL);
	glCompileShader(fShader);
	//Erfolgreich?
	printShaderSuccess(fShader);
	GLint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);
	glLinkProgram(shaderProgram);
	//Shader nicht mehr gebraucht da Programm erzeugt
	cout << "Shader " << vsPath << " and " << fsPath << " successfully linked" << endl;
	glDeleteShader(vShader);
	glDeleteShader(fShader);
	return shaderProgram;
}


