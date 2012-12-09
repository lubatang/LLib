//===- Vertex.h -----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_VERTEX_H
#define LUBA_VERTEX_H
#include <algebra/vec4.h>
#include <Triangle/Color.h>

namespace luba {

typedef vec4 Coord;

class Vertex
{
public:
  virtual void getCoord(Coord& pCoord) const = 0;

  virtual void getColor(Color& pColor) const = 0;
};

} // namespace of luba

#endif

