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
  if (pA.m_pParent != pB.m_pParent)
    return false;

  if (pA.m_Start == pB.m_Start)
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
  : m_pParent(NULL) {
}

TriangleIterator::TriangleIterator(const DrawTriangle& pParent,
                                   DrawLine::const_iterator pStart,
                                   DrawLine::const_iterator pRear)
  : m_pParent(&pParent), m_Start(pStart), m_Rear(pRear),
    m_Horizon(*pStart, *pRear) {
}

TriangleIterator::~TriangleIterator()
{
}

TriangleIterator::TriangleIterator(const TriangleIterator& pCopy)
  : m_pParent(pCopy.m_pParent), m_Start(pCopy.m_Start), m_Rear(pCopy.m_Rear),
    m_Horizon(pCopy.m_Horizon) {
}

TriangleIterator& TriangleIterator::operator=(const TriangleIterator& pCopy)
{
  m_pParent = pCopy.m_pParent;
  m_Start = pCopy.m_Start;
  m_Rear = pCopy.m_Rear;
  m_Horizon = pCopy.m_Horizon;
  return *this;
}

TriangleIterator& TriangleIterator::next()
{
  m_Start.next();
  m_Rear.next();
  if (m_Rear == m_pParent->m_DownEdge.end())
    m_Rear = m_pParent->m_UpEdge.begin();

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

