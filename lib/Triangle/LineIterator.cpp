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

//===----------------------------------------------------------------------===//
// LineIterator
//===----------------------------------------------------------------------===//
LineIterator::LineIterator(const DrawLine& pDrawLine,
                           float pErrorXY,
                           const Vertex& pVertex)
  : m_pDrawLine(&pDrawLine), m_ErrorXY(pErrorXY), m_Vertex(pVertex),
    m_Count(0) {
  m_X = (int)pVertex.x();
  m_Y = (int)pVertex.y();
  m_Z = (int)pVertex.z();

  if (m_pDrawLine->m_bSteepXY) {
    m_Vertex.setX(m_Y);
    m_Vertex.setY(m_X);
  }
  else {
    m_Vertex.setX(m_X);
    m_Vertex.setY(m_Y);
  }
}

LineIterator::LineIterator()
  : m_pDrawLine(NULL), m_ErrorXY(0.0), m_X(0), m_Y(0), m_Z(0), m_Count(0) {
}

LineIterator::LineIterator(const LineIterator& pCopy)
  : m_pDrawLine(pCopy.m_pDrawLine),
    m_ErrorXY(pCopy.m_ErrorXY),
    m_X(pCopy.m_X), m_Y(pCopy.m_Y), m_Z(pCopy.m_Z), m_Vertex(pCopy.m_Vertex),
    m_Count(0) {
}

LineIterator& LineIterator::operator=(const LineIterator& pCopy)
{
  m_pDrawLine = pCopy.m_pDrawLine;
  m_ErrorXY = pCopy.m_ErrorXY;
  m_X = pCopy.m_X;
  m_Y = pCopy.m_Y;
  m_Z = pCopy.m_Z;
  m_Vertex = pCopy.m_Vertex;
  m_Count = 0;
  return *this;
}

LineIterator& LineIterator::next()
{
  m_ErrorXY -= m_pDrawLine->m_DY;

  if (m_ErrorXY < 0) {
    m_Y += m_pDrawLine->m_YStep;
    m_ErrorXY += m_pDrawLine->m_DX;
  }

  m_X += m_pDrawLine->m_XStep;

  m_pDrawLine->dda(m_Vertex);
  m_pDrawLine->texture(m_Vertex, m_Count);
  ++m_Count;

  if (m_pDrawLine->m_bSteepXY) {
    m_Vertex.setX(m_Y);
    m_Vertex.setY(m_X);
  }
  else {
    m_Vertex.setX(m_X);
    m_Vertex.setY(m_Y);
  }
  return *this;
}

int LineIterator::x() const
{
  return m_Vertex.x();
}

int LineIterator::y() const
{
  return m_Vertex.y();
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

