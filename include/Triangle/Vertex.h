//===- Vertex.h -----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_VERTEX_H
#define LUBA_VERTEX_H
#include <Triangle/Vectors.h>
#include <Triangle/Color.h>
#include <algebra/vec2.h>
#include <iosfwd>

namespace luba {

typedef vec3D Coord;

class Vertex
{
private:
  friend Vertex operator-(const Vertex& pA, const Vertex& pB);

public:
  const Coord& coord() const { return m_Coord; }
  Coord&       coord()       { return m_Coord; }

  Vertex& setCoord(double pX, double pY, double pZ);
  void setX(double pX) { m_Coord[0] = pX; }
  void setY(double pY) { m_Coord[1] = pY; }
  void setZ(double pZ) { m_Coord[2] = pZ; }

  const Color& color() const { return m_Color; }
  Color&       color()       { return m_Color; }

  const vec3D& norm() const { return m_Norm; }
  vec3D&       norm()       { return m_Norm; }
  Vertex& setNorm(double pX, double pY, double pZ);

  const vec2& texture() const { return m_Texture; }
  vec2&       texture()       { return m_Texture; }
  Vertex& setTexture(double pU, double pV);

  // -----  accessors  ----- //
  double  x() const { return m_Coord[0]; }
  double& x()       { return m_Coord[0]; }
  double  y() const { return m_Coord[1]; }
  double& y()       { return m_Coord[1]; }
  double  z() const { return m_Coord[2]; }
  double& z()       { return m_Coord[2]; }
  double  w() const { return m_Coord[3]; }
  double& w()       { return m_Coord[3]; }

  // -----  operator ----- //
  Vertex& operator+=(const Vertex& pOther);
  Vertex& operator-=(const Vertex& pOther);

  Vertex& operator*=(double pC);
  Vertex& operator/=(double pC);
public:
  Coord m_Coord;
  Color m_Color;
  vec3D m_Norm;
  vec2  m_Texture;
};

Vertex operator + (const Vertex& pA, const Vertex& pB);
Vertex operator - (const Vertex& pA, const Vertex& pB);
Vertex operator * (const Vertex& pA, double pC);
Vertex operator / (const Vertex& pA, double pC);

} // namespace of luba

namespace std {

ostream& operator << (ostream& pOStream, const luba::Vertex& pVertex);

} // namespace of std

#endif

