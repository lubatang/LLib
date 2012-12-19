//===- TriangleIterator.h -------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_TRIANGLE_ITERATOR_H
#define LUBA_TRIANGLE_ITERATOR_H
#include <Triangle/DrawLine.h>
#include <Triangle/Color.h>

namespace luba {

class DrawTriangle;

class TriangleIterator
{
private:
  friend class DrawTriangle;
  friend bool operator==(const TriangleIterator& pX, const TriangleIterator& pY);
  friend bool operator!=(const TriangleIterator& pX, const TriangleIterator& pY);

  TriangleIterator(const DrawTriangle& pParent,
                   DrawLine::const_iterator pStart,
                   DrawLine::const_iterator pRear);

public:
  TriangleIterator();
  ~TriangleIterator();
  TriangleIterator(const TriangleIterator& pCopy);
  TriangleIterator& operator=(const TriangleIterator& pCopy);

  TriangleIterator& next();

  DrawLine& operator*();
  DrawLine* operator->();

private:
  const DrawTriangle* m_pParent;
  DrawLine m_Horizon;
  DrawLine::const_iterator m_Start;
  DrawLine::const_iterator m_Rear;

};

bool operator==(const luba::TriangleIterator& pX, const luba::TriangleIterator& pY);
bool operator!=(const luba::TriangleIterator& pX, const luba::TriangleIterator& pY);

} // namespace luba

#endif

