//===- LineIterator.cpp ---------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/LineIterator.h>
#include <Triangle/DrawLine.h>
#include <Triangle/Vertex.h>

#include <cassert>
#include <cmath>

using namespace luba;

//===----------------------------------------------------------------------===//
// Helper Functions
//===----------------------------------------------------------------------===//
bool luba::operator==(const LineIterator& pA, const LineIterator& pB)
{
  if (pA.m_pDrawLine != pB.m_pDrawLine)
    return false;
  return (pA.m_X == pB.m_X);
}

bool luba::operator!=(const LineIterator& pA, const LineIterator& pB)
{
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
                           const Vertex& pVertex)
  : m_pDrawLine(&pDrawLine), m_ErrorXY(pErrorXY), m_ErrorXZ(pErrorXZ), m_Vertex(pVertex) {
  m_X = (unsigned int)pVertex.x();
  m_Y = (unsigned int)pVertex.y();
  m_Z = (unsigned int)pVertex.z();

  if (m_pDrawLine->m_bSteepXZ) {
    m_Vertex.setX(m_Z);
    m_Vertex.setZ(m_X);
  }

  if (m_pDrawLine->m_bSteepXY) {
    m_Vertex.setX(m_Y);
    if (m_pDrawLine->m_bSteepXZ)
      m_Vertex.setY(m_Z);
    else
      m_Vertex.setY(m_X);
  }
}

LineIterator::LineIterator()
  : m_pDrawLine(NULL), m_ErrorXY(0.0), m_ErrorXZ(0.0), m_X(0), m_Y(0), m_Z(0) {
}

LineIterator::LineIterator(const LineIterator& pCopy)
  : m_pDrawLine(pCopy.m_pDrawLine),
    m_ErrorXY(pCopy.m_ErrorXY), m_ErrorXZ(pCopy.m_ErrorXZ),
    m_X(pCopy.m_X), m_Y(pCopy.m_Y), m_Z(pCopy.m_Z), m_Vertex(pCopy.m_Vertex) {
}

LineIterator& LineIterator::operator=(const LineIterator& pCopy)
{
  m_pDrawLine = pCopy.m_pDrawLine;
  m_ErrorXY = pCopy.m_ErrorXY;
  m_ErrorXZ = pCopy.m_ErrorXZ;
  m_X = pCopy.m_X;
  m_Y = pCopy.m_Y;
  m_Z = pCopy.m_Z;
  m_Vertex = pCopy.m_Vertex;
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

  m_Vertex.setCoord(m_X, m_Y, m_Z);
  if (m_pDrawLine->m_bSteepXZ) {
    m_Vertex.setX(m_Z);
    m_Vertex.setZ(m_X);
  }

  if (m_pDrawLine->m_bSteepXY) {
    m_Vertex.setX(m_Y);
    if (m_pDrawLine->m_bSteepXZ)
      m_Vertex.setY(m_Z);
    else
      m_Vertex.setY(m_X);
  }
}

unsigned int LineIterator::x() const
{
  return m_Vertex.x();
}

unsigned int LineIterator::y() const
{
  return m_Vertex.y();
}

unsigned int LineIterator::z() const
{
  return m_Vertex.z();
}

const Vertex& LineIterator::operator*() const
{
  return m_Vertex;
}

Vertex& LineIterator::operator*()
{
  return m_Vertex;
}

const Vertex* LineIterator::operator->() const
{
  return &m_Vertex;
}

Vertex* LineIterator::operator->()
{
  return &m_Vertex;
}

