//===- Space.cpp ----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Space.h>
#include <Triangle/Vertex.h>

using namespace luba;

//===----------------------------------------------------------------------===//
// Space
//===----------------------------------------------------------------------===//
Space::Space(unsigned int pWidth, unsigned int pHeight, unsigned int pDepth)
  : m_Width(pWidth), m_Height(pHeight), m_Depth(pDepth),
    m_X(0), m_Y(0), m_Z(0) {
}

void Space::map(const Coord& pCoord,
                unsigned int& pX, unsigned int& pY, unsigned int& pZ) const
{
  pX = m_X + ((m_Width  + (int)(m_Width  * pCoord[0])) >> 1);
  pY = m_Y + ((m_Height + (int)(m_Height * pCoord[1])) >> 1);
  pZ = m_Z + ((m_Depth  + (int)(m_Depth  * pCoord[2])) >> 1);
}

void Space::map(const Vertex& pVertex,
                unsigned int& pX, unsigned int& pY, unsigned int& pZ) const
{
  Coord coord;
  pVertex.getCoord(coord);
  map(coord, pX, pY, pZ);
}

void Space::map(const Coord& pCoord, double& pX, double& pY, double& pZ) const
{
  pX = m_X + ((double)(m_Width  + m_Width  * pCoord[0])/2.0);
  pY = m_Y + ((double)(m_Height + m_Height * pCoord[1])/2.0);
  pZ = m_Z + ((double)(m_Depth  + m_Depth  * pCoord[2])/2.0);
}

void Space::map(const Vertex& pVertex, double& pX, double& pY, double& pZ) const
{
  Coord coord;
  pVertex.getCoord(coord);
  map(coord, pX, pY, pZ);
}

void Space::setOrigin(unsigned int pX, unsigned int pY, unsigned int pZ)
{
  m_X = pX;
  m_Y = pY;
  m_Z = pZ;
}
