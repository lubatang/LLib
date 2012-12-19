//===- Vertex.h -----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_VERTEX_H
#define LUBA_VERTEX_H
#include <algebra/algebra.h>
#include <Triangle/Color.h>

namespace luba {

typedef vec3D Coord;

class Vertex
{
public:
  const Coord& coord() const { return m_Coord; }
  Coord&       coord()       { return m_Coord; }

  Vertex& setCoord(double pX, double pY, double pZ);
  void setX(double pX) { m_Coord[0] = pX; }
  void setY(double pY) { m_Coord[1] = pY; }
  void setZ(double pZ) { m_Coord[2] = pZ; }


  const Color& color() const { return m_Color; }
  Color&       color()       { return m_Color; }

  // -----  accessors  ----- //
  double  x() const { return m_Coord[0]; }
  double& x()       { return m_Coord[0]; }
  double  y() const { return m_Coord[1]; }
  double& y()       { return m_Coord[1]; }
  double  z() const { return m_Coord[2]; }
  double& z()       { return m_Coord[2]; }

public:
  Coord m_Coord;
  Color m_Color;

};

} // namespace of luba

#endif

