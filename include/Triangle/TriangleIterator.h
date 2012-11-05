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

  TriangleIterator(const DrawTriangle& pDrawer);
public:
  TriangleIterator();
  ~TriangleIterator() { }
  TriangleIterator(const TriangleIterator& pCopy);
  TriangleIterator& operator=(const TriangleIterator& pCopy);

  TriangleIterator& next();

  const Color& c1() const { return m_C1; }
  Color&       c1()       { return m_C1; }
  const Color& c2() const { return m_C2; }
  Color&       c2()       { return m_C2; }

  const DrawLine* operator->() const { return m_pDrawLine; }
  DrawLine*       operator->()       { return m_pDrawLine; }

  const DrawLine& operator*() const { return *m_pDrawLine; }
  DrawLine&       operator*()       { return *m_pDrawLine; }

private:
  const DrawTriangle* m_pDrawTriangle;

  DrawLine* m_pDrawLine;
  Color m_C1;
  Color m_C2;
};

bool operator==(const luba::TriangleIterator& pX, const luba::TriangleIterator& pY);
bool operator!=(const luba::TriangleIterator& pX, const luba::TriangleIterator& pY);

} // namespace luba

#endif

