//===- GenVertex.h --------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_GENERAL_VERTEX_H
#define LUBA_GENERAL_VERTEX_H
#include <cstddef>

#include <Triangle/Vertex.h>
#include <Triangle/Coord.h>
#include <Triangle/Color.h>

namespace luba {

class Color;
class Coord;

class GenVertex : public Vertex
{
public:
  GenVertex();

  void getCoord(Coord& pCoord) const { pCoord = m_Coord; }

  void setCoord(const Coord& pCoord) { m_Coord = pCoord; }

  void getColor(Color& pColor) const { pColor = m_Color; }

  void setColor(const Color& pColor) { m_Color = pColor; }

  const Coord& coord() const { return m_Coord; }
  Coord&       coord()       { return m_Coord; }

  const Color& color() const { return m_Color; }
  Color&       color()       { return m_Color; }

private:
  Coord m_Coord;
  Color m_Color;
};

} // namespace of luba

#endif

