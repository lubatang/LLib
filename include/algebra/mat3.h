//===- mat3.h -------------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_MATRIX_3X3_H
#define LUBA_MATRIX_3X3_H

#include <algebra/vec3.h>
#include <iosfwd>

namespace luba {

class vec2;

/** \class mat3
 *  \brief mat3 is a 3x3 matrix
 */
class mat3
{
public:
  mat3();
  mat3(const mat3& m);

  explicit mat3(double a00, double a01, double a02,
                double a10, double a11, double a12,
                double a20, double a21, double a22);

  explicit mat3(const vec3& v0, const vec3& v1, const vec3& v2);

  mat3 operator - () const;

  mat3& operator  = (const mat3& m);
  mat3& operator += (const mat3& m);
  mat3& operator -= (const mat3& m);
  mat3& operator *= (double d);
  mat3& operator /= (double d);

  vec3& operator [] (unsigned int i);
  vec3  operator [] (unsigned int i) const;

  void set(const vec3& v0, const vec3& v1, const vec3& v2);
  mat3 transpose() const;
  mat3 inverse() const;

  template<typename Action>
  mat3& apply() {
    m_Vec[0].apply<Action>();
    m_Vec[1].apply<Action>();
    m_Vec[2].apply<Action>();
    return *this;
  }

public:
  vec3 m_Vec[3];

};

} // namespace of luba

namespace std {

luba::mat3 operator + (const luba::mat3& a, const luba::mat3& b);
luba::mat3 operator - (const luba::mat3& a, const luba::mat3& b);
luba::mat3 operator * (const luba::mat3& a, const luba::mat3& b);
luba::mat3 operator * (const luba::mat3& a, double d);
luba::mat3 operator * (double d, const luba::mat3& a);
luba::mat3 operator / (const luba::mat3& a, double d);
bool operator == (const luba::mat3& a, const luba::mat3& b);
bool operator != (const luba::mat3& a, const luba::mat3& b);
ostream& operator << (ostream& s, luba::mat3& m);
void swap(luba::mat3& a, luba::mat3& b);

luba::vec3 operator * (const luba::mat3& a, const luba::vec3& v);
luba::vec3 operator * (const luba::vec3& v, const luba::mat3& a);

} // namespace of std

#endif

