//===- DrawTriangle.cpp ---------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/DrawTriangle.h>
#include <Triangle/Space.h>

#include <cmath>
#include <algorithm>

using namespace luba;

//===----------------------------------------------------------------------===//
// DrawTriangle
//===----------------------------------------------------------------------===//
DrawTriangle::DrawTriangle(const Vertex& pA, const Vertex& pB, const Vertex& pC)
  : m_A(pA), m_B(pB), m_C(pC),
    m_LongEdge(pC, pA), m_UpEdge(pB, pA), m_DownEdge(pC, pB) {
}

DrawTriangle::const_iterator DrawTriangle::begin() const
{
  return const_iterator(*this, m_LongEdge.begin(), m_DownEdge.begin());
}

DrawTriangle::const_iterator DrawTriangle::end() const
{
  return const_iterator(*this, m_LongEdge.end(), m_UpEdge.end());
}

bool DrawTriangle::hasArea() const
{
  if ((m_A.y() - m_B.y()) < 1 && (m_B.y() - m_C.y()) < 1) {
    // a horizontal line. v1.y must >= v2.y, and v2.y must >= v3.y
    return false;
  }

  if (fabs(m_A.x() - m_B.x()) < 1 && fabs(m_B.x() - m_C.x()) < 1) {
    // a vertical line
    return false;
  }

  return true;
}

