//===- Color.cpp ----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Color.h>

using namespace luba;

//===----------------------------------------------------------------------===//
// Color
//===----------------------------------------------------------------------===//
Color::Color(const Color& pCopy)
  : r(pCopy.r), g(pCopy.g), b(pCopy.b) {
}

Color& Color::operator=(const Color& pCopy)
{
  r = pCopy.r;
  g = pCopy.g;
  b = pCopy.b;
  return *this;
}
