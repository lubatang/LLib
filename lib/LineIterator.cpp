//===- LineIterator.cpp ---------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/LineIterator.h>
#include <Triangle/DrawLine.h>

#include <cassert>
#include <cmath>

using namespace luba;

//===----------------------------------------------------------------------===//
// Helper Functions
//===----------------------------------------------------------------------===//
bool luba::operator==(const LineIterator& pA, const LineIterator& pB)
{
  assert(pA.m_pDrawLine == pB.m_pDrawLine);
  return (pA.m_X == pB.m_X);
}

bool luba::operator!=(const LineIterator& pA, const LineIterator& pB)
{
  assert(pA.m_pDrawLine == pB.m_pDrawLine);
  return !(pA == pB);
}

unsigned int luba::operator-(const LineIterator& pA, const LineIterator& pB)
{
  assert(pA.m_pDrawLine == pB.m_pDrawLine);
  return abs(pA.m_X - pB.m_X);
}

//===----------------------------------------------------------------------===//
// LineIterator
//===----------------------------------------------------------------------===//
LineIterator::LineIterator(const DrawLine& pDrawLine,
                           float pErrorXY, float pErrorXZ,
                           float pX, float pY, float pZ)
  : m_pDrawLine(&pDrawLine), m_ErrorXY(pErrorXY), m_ErrorXZ(pErrorXZ) {
  m_X = (unsigned int)pX;
  m_Y = (unsigned int)pY;
  m_Z = (unsigned int)pZ;
}

LineIterator::LineIterator()
  : m_pDrawLine(NULL), m_ErrorXY(0.0), m_ErrorXZ(0.0), m_X(0), m_Y(0), m_Z(0) {
}

LineIterator::LineIterator(const LineIterator& pCopy)
  : m_pDrawLine(pCopy.m_pDrawLine),
    m_ErrorXY(pCopy.m_ErrorXY), m_ErrorXZ(pCopy.m_ErrorXZ),
    m_X(pCopy.m_X), m_Y(pCopy.m_Y), m_Z(pCopy.m_Z) {
}

LineIterator& LineIterator::operator=(const LineIterator& pCopy)
{
  m_pDrawLine = pCopy.m_pDrawLine;
  m_ErrorXY = pCopy.m_ErrorXY;
  m_ErrorXZ = pCopy.m_ErrorXZ;
  m_X = pCopy.m_X;
  m_Y = pCopy.m_Y;
  m_Z = pCopy.m_Z;
  return *this;
}

LineIterator& LineIterator::next()
{
  m_ErrorXY -= m_pDrawLine->m_DY;
  m_ErrorXZ -= m_pDrawLine->m_DZ;

  if (m_ErrorXY < 0) {
    m_Y += m_pDrawLine->m_YStep;
    m_ErrorXY += m_pDrawLine->m_DX;
  }

  if (m_ErrorXZ < 0) {
    m_Z += m_pDrawLine->m_ZStep;
    m_ErrorXZ += m_pDrawLine->m_DX;
  }

  m_X += m_pDrawLine->m_XStep;

}

unsigned int LineIterator::x() const
{
  unsigned int x = m_X;
  if (m_pDrawLine->m_bSteepXZ)
    x = m_Z;
  if (m_pDrawLine->m_bSteepXY)
    x = m_Y;

  return x;
}

unsigned int LineIterator::y() const
{
  unsigned int y = m_Y;
  unsigned int x = m_X;
  if (m_pDrawLine->m_bSteepXZ)
    x = m_Z;
  if (m_pDrawLine->m_bSteepXY)
    y = x;

  return y;
}

unsigned int LineIterator::z() const
{
  if (m_pDrawLine->m_bSteepXZ)
    return m_X;
  return m_Z;
}

