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
Color::Color()
  : vec3(0.0, 0.0, 0.0) {
}

Color::Color(double pR, double pG, double pB)
  : vec3(pR, pG, pB) {
}

Color::Color(const Color& pCopy)
  : vec3(pCopy[0], pCopy[1], pCopy[2]) {
}

Color& Color::operator=(const Color& pCopy)
{
  m_N[0] = pCopy[0];
  m_N[1] = pCopy[1];
  m_N[2] = pCopy[2];
  return *this;
}

