//===- vec3.h -------------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_VECTOR_3X1_H
#define LUBA_VECTOR_3X1_H

#include <iosfwd>
#include <algorithm>

namespace luba {

class vec2;

/** \class vec3
 *  \brief vec3 is a 3x1 vector
 */
class vec3
{
public:
  vec3();
  vec3(const vec3& v);
  explicit vec3(double x, double y, double z);
  explicit vec3(const vec2& v, double d);

  vec3  operator - () const;

  vec3& operator  = ( const vec3& v );
  vec3& operator += ( const vec3& v );
  vec3& operator -= ( const vec3& v );
  vec3& operator *= ( double d );
  vec3& operator /= ( double d );

  void set(double x, double y, double z);

  double  operator [] (unsigned int i) const;
  double& operator [] (unsigned int i);

  double  x() const { return m_N[0]; }
  double& x()       { return m_N[0]; }

  double  y() const { return m_N[1]; }
  double& y()       { return m_N[1]; }

  double  z() const { return m_N[2]; }
  double& z()       { return m_N[2]; }

  double length() const;
  vec3& normalize();
  vec3& homogenize();

  template<typename Action>
  vec3& apply() {
    m_N[0] = Action(m_N[0]);
    m_N[1] = Action(m_N[1]);
    m_N[2] = Action(m_N[2]);
    return *this;
  }

  double* native() { return m_N; }

protected:
  double m_N[3];

};

vec3 operator + (const vec3& a, const vec3& b);
vec3 operator - (const vec3& a, const vec3& b);
double operator * (const vec3& a, const vec3& b);
vec3 operator * (const vec3& a, double d);
vec3 operator * (double d, const vec3& a);

vec3 operator / (const vec3& a, double d);

bool operator == (const vec3& a, const vec3& b);
bool operator != (const vec3& a, const vec3& b);

/// cross product
vec3 CrossProduct(const vec3& a, const vec3& b);

} // namespace luba

namespace std {

ostream& operator << (ostream& pOStream, const luba::vec3& pVector);

template<>
void swap(luba::vec3& a, luba::vec3& b);

} // namespace std

#endif

