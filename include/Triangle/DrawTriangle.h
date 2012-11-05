//===- DrawTriangle.h -----------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_DRAW_TRIANGLE_H
#define LUBA_DRAW_TRIANGLE_H
#include <Triangle/TriangleIterator.h>

namespace luba {

class Space;
class Color;

/** \class DrawTriangle
 *  \brief DrawTriangle is an action to draw a triangle on certain space.
 */
class DrawTriangle
{
public:
  friend class TriangleIterator;
  typedef TriangleIterator const_iterator;

public:
  DrawTriangle(const Space& pSpace,
               const Coord& pA, const Coord& pB, const Coord& pC,
               const Color& pCA, const Color& pCB, const Color& pCC);

  const_iterator begin() const;
  const_iterator end  () const;

private:
  const Space& m_Space;
};

} // namespace luba

#endif

