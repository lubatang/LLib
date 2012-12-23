#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <algebra/vec3.h>

#include <stdio.h>
#include <vector>
#include <cstring>
#include <Triangle/FrameBuffer.h>
#include <Triangle/Camera.h>

using std::vector;
using namespace luba;


enum RENDER_MODE
{
  WIRE = 0,
  SOLID= 1,
  NUM
};

class LLight
{
protected:
  vec3 _pos;

public:
  LLight(const vec3 pos): _pos(pos) {};
  inline const vec3& getPos() const { return _pos;}
};

typedef void (*RenderFuncType)(const Camera&, const LLight&, FrameBuffer* , RENDER_MODE);
typedef void (*InitFuncType)();

int initAndRunLViewer(unsigned int pWinW, unsigned int pWinH, RenderFuncType, InitFuncType);

#endif
