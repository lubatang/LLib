//===- Painter.h ----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_PAINTER_H
#define LUBA_PAINTER_H

namespace luba {

class FrameBuffer;
class Space;
class Coord;
class Vertex;
class Line;
class Triangle;
class Model;
class Color;

class Painter
{
public:
  explicit Painter(FrameBuffer& pFB);

  bool draw(const Space& pSpace, Model& pModel) const;
  bool draw(const Space& pSpace, Triangle& pTriangle) const;
  bool draw(const Space& pSpace, Line& pLine) const;
  bool draw(const Space& pSpace, Vertex& pVertex) const;
  bool draw(const Space& pSpace, Coord& pCoord, Color& pColor) const;

private:
  FrameBuffer& m_FB;
};

} // end of namespace luba

#endif

