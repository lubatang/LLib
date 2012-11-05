//===- ColorIterator.h ----------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_COLOR_ITERATOR_H
#define LUBA_COLOR_ITERATOR_H
#include <Triangle/Color.h>

namespace luba {

class Line;

class ColorIterator
{
public:
  ColorIterator(const Line& pLine, float pDistance);

  ColorIterator();
  ~ColorIterator() { }
  ColorIterator(const ColorIterator& pCopy);
  ColorIterator& operator=(const ColorIterator& pCopy);

  ColorIterator& next();

  const Color& operator* () const { return m_Color;  }
  const Color* operator->() const { return &m_Color; }

private:
  Color m_Color;
  Color m_Delta;

};

} // namespace luba

#endif

