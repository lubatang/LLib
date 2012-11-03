//===- LineIterator.h -----------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_LINE_ITERATOR_H
#define LUBA_LINE_ITERATOR_H

namespace luba {

class DrawLine;

class LineIterator
{
private:
  friend class DrawLine;
  friend bool operator==(const LineIterator& pX, const LineIterator& pY);
  friend bool operator!=(const LineIterator& pX, const LineIterator& pY);

  LineIterator(const DrawLine& pDrawLine, float pErrorXY, float pErrorXZ,
               float pX, float pY, float pZ);

public:
  LineIterator();
  ~LineIterator() { }
  LineIterator(const LineIterator& pCopy);
  LineIterator& operator=(const LineIterator& pCopy);

  unsigned int x() const;
  unsigned int y() const;
  unsigned int z() const;

  LineIterator& next();

private:
  const DrawLine* m_pDrawLine;
  float m_ErrorXY;
  float m_ErrorXZ;
  unsigned int m_X;
  unsigned int m_Y;
  unsigned int m_Z;
};

bool operator==(const luba::LineIterator& pX, const luba::LineIterator& pY);
bool operator!=(const luba::LineIterator& pX, const luba::LineIterator& pY);

} // namespace luba

#endif

