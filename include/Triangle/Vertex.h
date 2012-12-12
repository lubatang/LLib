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
  const Coord& coord() const { return m_Coord; }
  Coord&       coord()       { return m_Coord; }

  const Color& color() const { return m_Color; }
  Color&       color()       { return m_Color; }

public:
  Coord m_Coord;
  Color m_Color;

};

} // namespace of luba

#endif

