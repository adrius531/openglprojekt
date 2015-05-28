/*
 * GLerror.h
 *
 *  Created on: Apr 27, 2015
 *      Author: adrian
 */

#ifndef GLERROR_H_
#define GLERROR_H_
#include <string>
#include <iostream>
void _check_gl_error(const char *file, int line);

///
/// Usage
/// [... some opengl calls]
/// glCheckError();
///
#define check_gl_error() _check_gl_error(__FILE__,__LINE__)

#endif // GLERROR_H_
