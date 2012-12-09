//===- DrawLine.cpp -------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/DrawLine.h>
#include <Triangle/Space.h>

#include <cmath>
#include <algorithm>

using namespace luba;

//===----------------------------------------------------------------------===//
// DrawLine
//===----------------------------------------------------------------------===//
DrawLine::DrawLine(const Space& pSpace, const Coord& pA, const Coord& pB)
  : m_Space(pSpace), m_bSteepXY(false), m_bSteepXZ(false) {

  pSpace.map(pA, m_A[0], m_A[1], m_A[2]);
  pSpace.map(pB, m_B[0], m_B[1], m_B[2]);

  // Extended Bresenham's line algorithm
  // @ref http://rosettacode.org/wiki/Bitmap/Bresenham's_line_algorithm
  // @ref Course Slides, "Scan Converting Lines, " pp. 20, GP03-Rasterization
  // Set Up.
  m_bSteepXY = (fabs(m_B[1] - m_A[1]) > fabs(m_B[0] - m_A[0]));

  if(m_bSteepXY) {
    // if the line is steep on X-Y plane, exchange x-axis and y-axis
    std::swap(m_A[0], m_A[1]);
    std::swap(m_B[0], m_B[1]);
  }

  m_bSteepXZ = (fabs(m_B[2] - m_A[2]) > fabs(m_B[0] - m_A[0]));

  if(m_bSteepXZ) {
    // if the line is steep on X-Z plane, exchange x-axis and z-axis
    std::swap(m_A[0], m_A[2]);
    std::swap(m_B[0], m_B[2]);
  }

  m_DX = fabs(m_B[0] - m_A[0]);
  m_DY = fabs(m_B[1] - m_A[1]);
  m_DZ = fabs(m_B[2] - m_A[2]);

  m_XStep = (m_A[0] < m_B[0]) ? 1 : -1;
  m_YStep = (m_A[1] < m_B[1]) ? 1 : -1;
  m_ZStep = (m_A[2] < m_B[2]) ? 1 : -1;

}

DrawLine::const_iterator DrawLine::begin() const
{
  return const_iterator(*this, m_DX/2.0f, m_DX/2.0f, m_A[0], m_A[1], m_A[2]);
}

DrawLine::const_iterator DrawLine::end() const
{
  return const_iterator(*this, m_DX/2.0f, m_DX/2.0f, m_B[0], m_B[1], m_B[2]);
}

unsigned int DrawLine::distance() const
{
  return abs(m_A[0] - m_B[0]);
}

