//===- LineIterator.h -----------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_LINE_ITERATOR_H
#define LUBA_LINE_ITERATOR_H
#include <Triangle/Vertex.h>

namespace luba {

class DrawLine;

class LineIterator
{
private:
  friend class DrawLine;
  friend bool operator==(const LineIterator& pX, const LineIterator& pY);
  friend bool operator!=(const LineIterator& pX, const LineIterator& pY);

  LineIterator(const DrawLine& pDrawLine, float pErrorXY, const Vertex& pVertex);

public:
  LineIterator();
  ~LineIterator() { }
  LineIterator(const LineIterator& pCopy);
  LineIterator& operator=(const LineIterator& pCopy);

  int x() const;
  int y() const;

  LineIterator& next();

  const Vertex& operator*() const;
  Vertex& operator*();

  const Vertex* operator->() const;
  Vertex* operator->();

private:
  const DrawLine* m_pDrawLine;
  float m_ErrorXY;
  float m_ErrorXZ;
  int m_X;
  int m_Y;
  int m_Z;
  Vertex m_Vertex;
  unsigned int m_Count;
};

bool operator==(const luba::LineIterator& pX, const luba::LineIterator& pY);
bool operator!=(const luba::LineIterator& pX, const luba::LineIterator& pY);

} // namespace luba

#endif

