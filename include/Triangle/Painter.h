//===- Painter.h ----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_PAINTER_H
#define LUBA_PAINTER_H
#include <Triangle/Vertex.h>

namespace luba {

class FrameBuffer;
class Space;
class Camera;
class Vertex;
class Line;
class Triangle;
class Model;
class Color;

class Painter
{
public:
  explicit Painter(FrameBuffer& pFB);

  bool draw(const Space& pSpace, const Camera& pCam, Model& pModel, bool pSolid) const;
  bool draw(const Triangle& pTriangle) const;
  bool draw(const Line& pLine) const;
  bool draw(const Vertex& pVertex) const;

private:
  FrameBuffer& m_FB;
};

} // end of namespace luba

#endif

