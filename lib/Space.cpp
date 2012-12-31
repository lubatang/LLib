//===- Space.cpp ----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Space.h>

using namespace luba;

//===----------------------------------------------------------------------===//
// Space
//===----------------------------------------------------------------------===//
Space::Space(unsigned int pWidth, unsigned int pHeight, unsigned int pDepth)
  : m_Width(pWidth), m_Height(pHeight), m_Depth(pDepth),
    m_OrgX(0), m_OrgY(0), m_OrgZ(0) {
}

void Space::setOrigin(unsigned int pX, unsigned int pY, unsigned int pZ)
{
  m_OrgX = pX;
  m_OrgY = pY;
  m_OrgZ = pZ;
}

mat4 Space::scale() const
{
  mat4 result( m_Width/2,      0.0,     0.0, 0.0,
                   0.0, m_Height/2,     0.0, 0.0,
                   0.0,      0.0, m_Depth/2, 0.0,
                   0.0,      0.0,     0.0, 1.0);
  return result;
}

mat4 Space::translate() const
{
  mat4 result(1.0, 0.0, 0.0, (double)m_Width/2  + m_OrgX,
              0.0, 1.0, 0.0, (double)m_Height/2 + m_OrgY,
              0.0, 0.0, 1.0, (double)m_Depth/2  + m_OrgZ,
              0.0, 0.0, 0.0, 1.0);
  return result;
}
