//===- DrawTriangle.h -----------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_DRAW_TRIANGLE_H
#define LUBA_DRAW_TRIANGLE_H
#include <Triangle/TriangleIterator.h>
#include <Triangle/Vertex.h>

namespace luba {

/** \class DrawTriangle
 *  \brief DrawTriangle is an action to draw a triangle on certain space.
 */
class DrawTriangle
{
public:
  friend class TriangleIterator;
  typedef TriangleIterator const_iterator;

public:
  DrawTriangle(const Vertex& pA, const Vertex& pB, const Vertex& pC);

  bool hasArea() const;

  const_iterator begin() const;
  const_iterator end() const;

private:
  const Vertex& m_A;
  const Vertex& m_B;
  const Vertex& m_C;

  DrawLine m_LongEdge;
  DrawLine m_UpEdge;
  DrawLine m_DownEdge;
};

} // namespace luba

#endif

