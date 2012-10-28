//===- Triangle.h ---------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_TRIANGLE_H
#define LUBA_TRIANGLE_H
#include <Triangle/Drawable.h>
#include <Triangle/FrameBuffer.h>
#include <GLM/glm.h>

namespace luba {

class Triangle : public Drawable
{
public:
  Triangle(const GLMtriangle& pGLMTriangle);

  bool draw(FrameBuffer& pFB);
};

} // namespace of luba

#endif

