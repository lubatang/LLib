//===- Line.h -------------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_LINE_H
#define LUBA_LINE_H

namespace luba {

class Vertex;

class Line
{
public:
  Line(const Vertex& pA, const Vertex& pB);

  const Vertex& front() const { return m_A; }
  const Vertex& rear () const { return m_B; }

private:
  const Vertex& m_A;
  const Vertex& m_B;
};

} // namespace luba
#endif

