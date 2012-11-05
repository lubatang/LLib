//===- TriangleIterator.cpp -----------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/TriangleIterator.h>
#include <Triangle/DrawTriangle.h>

#include <cassert>
#include <cmath>

using namespace luba;

//===----------------------------------------------------------------------===//
// Helper Functions
//===----------------------------------------------------------------------===//
bool luba::operator==(const TriangleIterator& pA, const TriangleIterator& pB)
{
  assert(pA.m_pDrawTriangle == pB.m_pDrawTriangle);
  return true;
}

bool luba::operator!=(const TriangleIterator& pA, const TriangleIterator& pB)
{
  assert(pA.m_pDrawTriangle == pB.m_pDrawTriangle);
  return !(pA == pB);
}

//===----------------------------------------------------------------------===//
// TriangleIterator
//===----------------------------------------------------------------------===//
TriangleIterator::TriangleIterator(const DrawTriangle& pDrawTriangle)
  : m_pDrawTriangle(&pDrawTriangle), m_pDrawLine(NULL) {
}

TriangleIterator::TriangleIterator()
  : m_pDrawTriangle(NULL), m_pDrawLine(NULL) {
}

TriangleIterator::TriangleIterator(const TriangleIterator& pCopy)
  : m_pDrawTriangle(pCopy.m_pDrawTriangle), m_pDrawLine(pCopy.m_pDrawLine) {
}

TriangleIterator& TriangleIterator::operator=(const TriangleIterator& pCopy)
{
  m_pDrawTriangle = pCopy.m_pDrawTriangle;
  m_pDrawLine = pCopy.m_pDrawLine;
  return *this;
}

TriangleIterator& TriangleIterator::next()
{
}

