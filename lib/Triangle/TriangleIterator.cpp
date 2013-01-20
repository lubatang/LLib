//===- TriangleIterator.cpp -----------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/TriangleIterator.h>
#include <Triangle/DrawTriangle.h>

#include <cassert>
#include <cmath>

#include <iostream>
using namespace std;
using namespace luba;

//===----------------------------------------------------------------------===//
// Helper Functions
//===----------------------------------------------------------------------===//
bool luba::operator==(const TriangleIterator& pA, const TriangleIterator& pB)
{
  if (pA.m_pParent != pB.m_pParent)
    return false;

  if (pA.m_Y == pB.m_Y)
    return true;
  return false;
}

bool luba::operator!=(const TriangleIterator& pA, const TriangleIterator& pB)
{
  return !(pA == pB);
}

//===----------------------------------------------------------------------===//
// TriangleIterator
//===----------------------------------------------------------------------===//
TriangleIterator::TriangleIterator()
  : m_pParent(NULL), m_Y(0), m_bDrawingUp(false) {
}

TriangleIterator::TriangleIterator(const DrawTriangle& pParent,
                                   DrawLine::const_iterator pStart,
                                   DrawLine::const_iterator pRear)
  : m_pParent(&pParent), m_Start(pStart), m_Rear(pRear),
    m_Horizon(*pStart, *pRear), m_Y(pStart.y()), m_bDrawingUp(false) {
}

TriangleIterator::~TriangleIterator()
{
}

TriangleIterator::TriangleIterator(const TriangleIterator& pCopy)
  : m_pParent(pCopy.m_pParent), m_Start(pCopy.m_Start), m_Rear(pCopy.m_Rear),
    m_Horizon(pCopy.m_Horizon), m_Y(pCopy.m_Y), m_bDrawingUp(pCopy.m_bDrawingUp) {
}

TriangleIterator& TriangleIterator::operator=(const TriangleIterator& pCopy)
{
  m_pParent = pCopy.m_pParent;
  m_Start = pCopy.m_Start;
  m_Rear = pCopy.m_Rear;
  m_Horizon = pCopy.m_Horizon;
  m_Y = pCopy.m_Y;
  m_bDrawingUp = pCopy.m_bDrawingUp;
  return *this;
}

TriangleIterator& TriangleIterator::next()
{
  ++m_Y;
  while (m_Start.y() != m_Y && m_Start != m_pParent->m_LongEdge.end()) {
    m_Start.next();
  }

  if (!m_bDrawingUp) {
    while (m_Rear.y() != m_Y && m_Rear != m_pParent->m_DownEdge.end())
      m_Rear.next();
  }

  if (m_Rear == m_pParent->m_DownEdge.end()) {
    m_bDrawingUp = true;
    m_Rear = m_pParent->m_UpEdge.begin();
  }

  if (m_bDrawingUp && m_Rear.y() != m_Y) {
    while (m_Rear.y() != m_Y && m_Rear != m_pParent->m_UpEdge.end()) {
      m_Rear.next();
    }
  }

  if (m_Rear.y() != m_Start.y()) {
    cerr << "!! assert " << m_Start.y() << " != " << m_Rear.y() << "\tm_Y==" << m_Y << " drawing up:" << m_bDrawingUp << endl;
    if (m_Rear == m_pParent->m_UpEdge.end()) {
      cerr << "  rear(" << m_Rear.x() << ", " << m_Rear.y() << ") == up edge's end" << m_pParent->m_UpEdge.end()->coord() << endl;
    }
    if (m_Start == m_pParent->m_LongEdge.end()) {
      cerr << "  start(" << m_Start.x() << ", " << m_Start.y() << ") == long edge's end" << m_pParent->m_LongEdge.end()->coord() << endl;
    }
      cerr << "\tup:   " << m_pParent->m_UpEdge.begin()->coord() << " to " << m_pParent->m_UpEdge.end()->coord() << endl;
      cerr << "\tdown: " << m_pParent->m_DownEdge.begin()->coord() << " to " << m_pParent->m_DownEdge.end()->coord() << endl;
      cerr << "\tlong: " << m_pParent->m_LongEdge.begin()->coord() << " to " << m_pParent->m_LongEdge.end()->coord() << endl;
  }

  m_Horizon.setTerminals(*m_Start, *m_Rear);
  return *this;
}

DrawLine& TriangleIterator::operator*()
{
  return m_Horizon;
}

DrawLine* TriangleIterator::operator->()
{
  return &m_Horizon;
}

