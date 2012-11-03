//===- DrawLine.h ---------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_DRAW_LINE_H
#define LUBA_DRAW_LINE_H
#include <Triangle/LineIterator.h>

namespace luba {

class Space;
class Line;

/** \class DrawLine
 *  \brief DrawLine is an action to draw a line on certain space.
 */
class DrawLine
{
public:
  friend class LineIterator;
  typedef LineIterator const_iterator;

public:
  DrawLine(const Space& pSpace, const Line& pLine);

  const_iterator begin() const;
  const_iterator end  () const;

  /// distance - the number of pixels that need to be painted.
  unsigned int distance() const;

private:
  struct Point {
    float x;
    float y;
    float z;
  };

private:
  Point m_A;
  Point m_B;

  int m_XStep;
  int m_YStep;
  int m_ZStep;

  float m_DX;
  float m_DY;
  float m_DZ;

  bool m_bSteepXY : 1;
  bool m_bSteepXZ : 1;

  const Space& m_Space;
  const Line& m_Line;
};

} // namespace luba

#endif

