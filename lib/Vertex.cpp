//===- Vertex.cpp ---------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Vertex.h>
#include <iostream>

using namespace luba;

//===----------------------------------------------------------------------===//
// Vertex
//===----------------------------------------------------------------------===//
Vertex& Vertex::setCoord(double pX, double pY, double pZ)
{
  m_Coord[0] = pX;
  m_Coord[1] = pY;
  m_Coord[2] = pZ;
  return *this;
}

Vertex& Vertex::setNorm(double pX, double pY, double pZ)
{
  m_Norm[0] = pX;
  m_Norm[1] = pY;
  m_Norm[2] = pZ;
  return *this;
}

Vertex& Vertex::operator+=(const Vertex& pOther)
{
  m_Coord += pOther.m_Coord;
  m_Color += pOther.m_Color;
  m_Norm += pOther.m_Norm;
  return *this;
}

Vertex& Vertex::operator-=(const Vertex& pOther)
{
  m_Coord -= pOther.m_Coord;
  m_Color -= pOther.m_Color;
  m_Norm -= pOther.m_Norm;
  return *this;
}

Vertex& Vertex::operator*=(double pC)
{
  m_Coord *= pC;
  m_Color *= pC;
  m_Norm *= pC;
  return *this;
}

Vertex& Vertex::operator/=(double pC)
{
  m_Coord /= pC;
  m_Color /= pC;
  m_Norm /= pC;
  return *this;
}

//===----------------------------------------------------------------------===//
// Non member function
//===----------------------------------------------------------------------===//
Vertex luba::operator + (const Vertex& pA, const Vertex& pB)
{
  Vertex result(pA);
  return (result += pB);
}

Vertex luba::operator - (const Vertex& pA, const Vertex& pB)
{
  Vertex result(pA);
  return (result -= pB);
}

Vertex luba::operator * (const Vertex& pA, double pC)
{
  Vertex result(pA);
  result *= pC;
  return result;
}

Vertex luba::operator / (const Vertex& pA, double pC)
{
  Vertex result(pA);
  result /= pC;
  return result;
}

std::ostream& std::operator << (std::ostream& pOStream, const Vertex& pVertex)
{
  pOStream << "coord: " << pVertex.coord() << endl;
  pOStream << "  color: " << pVertex.color() << endl;
  pOStream << "  norm:  " << pVertex.norm();
  return pOStream;
}

