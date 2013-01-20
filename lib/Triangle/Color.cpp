//===- Color.cpp ----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Color.h>
#include <Triangle/Vectors.h>

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

Color::Color(const vec3& pColor)
  : vec3(pColor) {
}

Color::Color(const vec4& pColor)
  : vec3(pColor[0], pColor[1], pColor[2]) {
}

Color& Color::operator=(const Color& pCopy)
{
  m_N[0] = pCopy[0];
  m_N[1] = pCopy[1];
  m_N[2] = pCopy[2];
  return *this;
}

Color& Color::operator*=(double pC)
{
  m_N[0] *= pC;
  m_N[1] *= pC;
  m_N[2] *= pC;
  return *this;
}

Color& Color::operator*=(const vec3& pCoeff)
{
  m_N[0] *= pCoeff[0];
  m_N[1] *= pCoeff[1];
  m_N[2] *= pCoeff[2];
  return *this;
}

/**
Color& Color::operator+=(const vec3D& pVec)
{
  m_N[0] += pVec[0];
  m_N[1] += pVec[1];
  m_N[2] += pVec[2];
  return *this;
}
**/
