//===- DrawLine.cpp -------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/DrawLine.h>
#include <Triangle/Space.h>

#include <cmath>
#include <cstdlib>
#include <algorithm>

#include <iostream>
using namespace std;

using namespace luba;

//===----------------------------------------------------------------------===//
// DrawLine
//===----------------------------------------------------------------------===//
DrawLine::DrawLine()
  : m_bSteepXY(false) {
}

DrawLine::DrawLine(const Vertex& pA, const Vertex& pB)
{
  setTerminals(pA, pB);
}

DrawLine& DrawLine::setTerminals(const Vertex& pA, const Vertex& pB)
{
  m_A = pA;
  m_B = pB;
  m_bSteepXY = false;
  m_AUZ = m_AVZ = m_BUZ = m_BVZ = 0.0;


  // Extended Bresenham's line algorithm
  // @ref http://rosettacode.org/wiki/Bitmap/Bresenham's_line_algorithm
  // @ref Course Slides, "Scan Converting Lines, " pp. 20, GP03-Rasterization
  // Set Up.
  m_bSteepXY = (fabs(m_B.y() - m_A.y()) > fabs(m_B.x() - m_A.x()));

  if(m_bSteepXY) {
    // if the line is steep on X-Y plane, exchange x-axis and y-axis
    std::swap(m_A.x(), m_A.y());
    std::swap(m_B.x(), m_B.y());
  }

  m_DX = fabs(m_B.x() - m_A.x());
  m_DY = fabs(m_B.y() - m_A.y());

  m_XStep = (m_A.x() < m_B.x()) ? 1 : -1;
  m_YStep = (m_A.y() < m_B.y()) ? 1 : -1;

  unsigned int d = distance();
  if (0 != d) {
    m_DDA = (pB - pA)/distance();
    m_DDA.x() = 0;
    m_DDA.y() = 0;

    m_AUZ = m_A.u()/m_A.w();
    m_AVZ = m_A.v()/m_A.w();
    m_BUZ = m_B.u()/m_B.w();
    m_BVZ = m_B.v()/m_B.w();

  }
  return *this;
}

DrawLine::const_iterator DrawLine::begin() const
{
  return const_iterator(*this, m_DX/2.0f, m_A);
}

DrawLine::const_iterator DrawLine::end() const
{
  return const_iterator(*this, m_DX/2.0f, m_B);
}

unsigned int DrawLine::distance() const
{
  return ::abs((int)(m_B.x()) - (int)(m_A.x()));
}

void DrawLine::dda(Vertex& pVertex) const
{
  pVertex += m_DDA;
}

void DrawLine::texture(Vertex& pVertex, unsigned int pCount) const
{
  double alpha = (double)pCount/(double)distance();
  double base = (1.0 - alpha)/m_A.w() + alpha/m_B.w();

  double u = ((1.0 - alpha) * m_AUZ + alpha*m_BUZ) / base;
  double v = ((1.0 - alpha) * m_AVZ + alpha*m_BVZ) / base;

  pVertex.u() = u;
  pVertex.v() = v;
}

