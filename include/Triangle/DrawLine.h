//===- DrawLine.h ---------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_DRAW_LINE_H
#define LUBA_DRAW_LINE_H
#include <Triangle/LineIterator.h>
#include <Triangle/Vertex.h>

namespace luba {

/** \class DrawLine
 *  \brief DrawLine is an action to draw a line on X-Y plane.
 */
class DrawLine
{
public:
  friend class LineIterator;
  typedef LineIterator const_iterator;

public:
  DrawLine();

  DrawLine(const Vertex& pA, const Vertex& pB);

  DrawLine& setTerminals(const Vertex& pA, const Vertex& pB);

  const_iterator begin() const;
  const_iterator end  () const;

  /// distance - the number of pixels that need to be painted.
  unsigned int distance() const;

private:
  Vertex m_A;
  Vertex m_B;

  int m_XStep;
  int m_YStep;

  float m_DX;
  float m_DY;

  bool m_bSteepXY : 1;

};

} // namespace luba

#endif

