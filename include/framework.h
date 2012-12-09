#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <algebra/algebra.h>
#include <algebra/vec3.h>

#include <stdio.h>
#include <vector>
#include <cstring>
#include <Triangle/FrameBuffer.h>

using std::vector;
using namespace luba;


enum RENDER_MODE
{
  WIRE = 0,
  SOLID= 1,
  NUM
};

class LCamera
{
protected:
  vec3 _pos;
  vec3 _target;
  vec3 _up;

public:
  LCamera(const vec3 pos, const vec3 tgt, const vec3 up): _pos(pos), _target(tgt), _up(up) {};
  void getVectors( vec3 &pos, vec3 &target, vec3 &up)  const {  pos = _pos; target = _target; up = _up;}
};

class LLight
{
protected:
  vec3 _pos;

public:
  LLight(const vec3 pos): _pos(pos) {};
  inline const vec3& getPos() const { return _pos;}
};

int initAndRunLViewer( const int winW, const int winH, void (*render)(const LCamera cam, const LLight lit, FrameBuffer * colorBuff, RENDER_MODE mode), void (*initFun)());

#endif
