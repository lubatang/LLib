//===- Space.cpp ----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Space.h>
#include <algebra/algebra.h>

using namespace luba;

//===----------------------------------------------------------------------===//
// Space
//===----------------------------------------------------------------------===//
Space::Space(unsigned int pWidth, unsigned int pHeight, unsigned int pDepth)
  : m_Width(pWidth), m_Height(pHeight), m_Depth(pDepth),
    m_X(0), m_Y(0), m_Z(0) {
}

void Space::setOrigin(unsigned int pX, unsigned int pY, unsigned int pZ)
{
  m_X = pX;
  m_Y = pY;
  m_Z = pZ;
}

void Space::map(Vertex& pVertex) const
{
  scaling(pVertex.coord(), (double)m_Width/2, (double)m_Height/2, (double)m_Depth/2);
  translate(pVertex.coord(), (double)m_Width/2, (double)m_Height/2, (double)m_Depth/2);
}

