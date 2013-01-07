//===- Color.h ------------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_COLOR_H
#define LUBA_COLOR_H
#include <stdint.h>
#include <algebra/vec3.h>

namespace luba {

class vec4;

/** \class Color
 *  \brief Color represents the color of a pixel.
 */
class Color : public vec3
{
public:
  Color();
  Color(double pR, double pG, double pB);
  Color(const Color& pCopy);
  Color(const vec3& pColor);
  Color(const vec4& pColor);

  Color& operator=(const Color& pCopy);

  double  r() const { return m_N[0]; }
  double& r()       { return m_N[0]; }

  double  g() const { return m_N[1]; }
  double& g()       { return m_N[1]; }

  double  b() const { return m_N[2]; }
  double& b()       { return m_N[2]; }

  Color& operator *=(double pC);
  Color& operator *=(const vec3& pCoeff);

};

} // namespace of luba
#endif

