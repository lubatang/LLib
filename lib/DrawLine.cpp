//===- DrawLine.cpp -------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/DrawLine.h>
#include <Triangle/Space.h>
#include <Triangle/Line.h>

#include <cmath>
#include <algorithm>

using namespace luba;

//===----------------------------------------------------------------------===//
// DrawLine
//===----------------------------------------------------------------------===//
DrawLine::DrawLine(const Space& pSpace, const Line& pLine)
  : m_Space(pSpace), m_Line(pLine), m_bSteepXY(false), m_bSteepXZ(false) {

  pSpace.map(pLine.front(), m_A.x, m_A.y, m_A.z);
  pSpace.map(pLine.rear(), m_B.x, m_B.y, m_B.z);

  // Extended Bresenham's line algorithm
  // @ref http://rosettacode.org/wiki/Bitmap/Bresenham's_line_algorithm
  // @ref Course Slides, "Scan Converting Lines, " pp. 20, GP03-Rasterization
  // Set Up.
  m_bSteepXY = (fabs(m_B.y - m_A.y) > fabs(m_B.x - m_A.x));

  if(m_bSteepXY) {
    // if the line is steep on X-Y plane, exchange x-axis and y-axis
    std::swap(m_A.x, m_A.y);
    std::swap(m_B.x, m_B.y);
  }

  m_bSteepXZ = (fabs(m_B.z - m_A.z) > fabs(m_B.x - m_A.x));

  if(m_bSteepXZ) {
    // if the line is steep on X-Z plane, exchange x-axis and z-axis
    std::swap(m_A.x, m_A.z);
    std::swap(m_B.x, m_B.z);
  }

  m_DX = fabs(m_B.x - m_A.x);
  m_DY = fabs(m_B.y - m_A.y);
  m_DZ = fabs(m_B.z - m_A.z);

  m_XStep = (m_A.x < m_B.x) ? 1 : -1;
  m_YStep = (m_A.y < m_B.y) ? 1 : -1;
  m_ZStep = (m_A.z < m_B.z) ? 1 : -1;

}

DrawLine::const_iterator DrawLine::begin() const
{
  return const_iterator(*this, m_DX/2.0f, m_DX/2.0f, m_A.x, m_A.y, m_A.z);
}

DrawLine::const_iterator DrawLine::end() const
{
  return const_iterator(*this, m_DX/2.0f, m_DX/2.0f, m_B.x, m_B.y, m_B.z);
}

unsigned int DrawLine::distance() const
{
  return abs(m_A.x - m_B.x);
}
