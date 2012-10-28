// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//standard library
#include <iostream>
#include <cstdlib>
using namespace std;

#ifdef __APPLE__
//openGL related library
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

//the framework library
#include <framework.h>

//the OBJ model library
#include <GLM/glm.h>

//the math library
using namespace LLib::Math;


// TODO: reference additional headers your program requires here
