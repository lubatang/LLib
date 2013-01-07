#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <algebra/vec3.h>

#include <stdio.h>
#include <cstring>
#include <Triangle/FrameBuffer.h>
#include <Triangle/Camera.h>
#include <Triangle/Light.h>

using namespace luba;

enum RENDER_MODE
{
  WIRE = 0,
  SOLID= 1,
  NUM
};

typedef void (*RenderFuncType)(const Camera&, const Light& pLight, FrameBuffer* , RENDER_MODE);
typedef void (*InitFuncType)();

int initAndRunLViewer(unsigned int pWinW, unsigned int pWinH, RenderFuncType, InitFuncType);

#endif
