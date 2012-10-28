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
  uint8_t r;
  uint8_t g;
  uint8_t b;

public:
  Color() :r(0u), g(0u), b(0u) {}
  Color(uint8_t pR, uint8_t pG, uint8_t pB) : r(pR), g(pG), b(pB) {}

  Color(const Color& pCopy);
  Color& operator=(const Color& pCopy);

};

} // namespace of luba
#endif

