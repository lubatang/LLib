//===- Color.h ------------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_COLOR_H
#define LUBA_COLOR_H
#include <stdint.h>

namespace luba {

/** \class Color
 *  \brief Color represents the color of a pixel.
 */
class Color
{
public:
  float r;
  float g;
  float b;

public:
  Color() :r(0.0), g(0.0), b(0.0) {}
  Color(float pR, float pG, float pB) : r(pR), g(pG), b(pB) {}

  Color(const Color& pCopy);
  Color& operator=(const Color& pCopy);

  Color& operator+=(const Color& pAddend);
  Color& operator-=(const Color& pAddend);
};

} // namespace of luba
#endif

