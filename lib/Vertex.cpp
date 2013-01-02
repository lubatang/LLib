//===- Vertex.cpp ---------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Vertex.h>

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

