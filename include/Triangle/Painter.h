//===- Painter.h ----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_PAINTER_H
#define LUBA_PAINTER_H

namespace luba {

class FrameBuffer;
class Coord;
class Vertex;
class Line;
class Model;
class Color;

void map(FrameBuffer& pFB, Coord& pCoord, unsigned int& pX, unsigned int& pY);

class Painter
{
public:
  bool draw(FrameBuffer& pFB, Model& pModel) const;
  bool draw(FrameBuffer& pFB, Line& pLine) const;
  bool draw(FrameBuffer& pFB, Vertex& pVertex) const;
  bool draw(FrameBuffer& pFB, Coord& pCoord, Color& pColor) const;
  bool draw(FrameBuffer& pFB, unsigned int pX, unsigned int pY, Color& pColor) const;
};

} // end of namespace luba

#endif

