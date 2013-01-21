#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <algebra/vec3.h>

#include <stdio.h>
#include <cstring>
#include <Triangle/FrameBuffer.h>
#include <Triangle/Camera.h>
#include <Triangle/Light.h>

using namespace luba;

typedef void (*RenderFuncType)(const Camera&, const Light& pLight, FrameBuffer*);
typedef void (*InitFuncType)();

int initAndRunLViewer(unsigned int pWinW, unsigned int pWinH, RenderFuncType, InitFuncType);

#endif
