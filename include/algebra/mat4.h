//===- mat4.h -------------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_MATRIX_4X4_H
#define LUBA_MATRIX_4X4_H

#include <algebra/vec4.h>
#include <iosfwd>

namespace luba {

/** \class mat4
 *  \brief mat4 is a 4x4 matrix
 */
class mat4
{
public:
  enum Subspace {
    Row,
    Column
  };

public:
  mat4();
  mat4(const mat4& pCopy);

  explicit mat4(const vec4& v0, const vec4& v1, const vec4& v2, const vec4& v3);
  explicit mat4(double a00, double a01, double a02, double a03,
                double a10, double a11, double a12, double a13,
                double a20, double a21, double a22, double a23,
                double a30, double a31, double a32, double a33 );

  mat4  operator  - () const;

  mat4& operator  = (const mat4& m);
  mat4& operator += (const mat4& m);
  mat4& operator -= (const mat4& m);
  mat4& operator *= (double d);
  mat4& operator /= (double d);
  vec4  operator [] (unsigned int idx) const;
  vec4& operator [] (unsigned int idx);

  mat4 transpose() const;
  mat4 inverse() const;

  template<Subspace S>
  void swap(unsigned int i, unsigned int j);

  template<typename Action>
  mat4& apply() {
    m_Vec[0].apply<Action>();
    m_Vec[1].apply<Action>();
    m_Vec[2].apply<Action>();
    m_Vec[3].apply<Action>();
    return *this;
  }

public:
  vec4 m_Vec[4];

};

template<> void mat4::swap<mat4::Row>   (unsigned int i, unsigned int j);
template<> void mat4::swap<mat4::Column>(unsigned int i, unsigned int j);

} // namespace of luba

namespace std {

luba::mat4 operator + (const luba::mat4& a, const luba::mat4& b);
luba::mat4 operator - (const luba::mat4& a, const luba::mat4& b);
luba::mat4 operator * (const luba::mat4& a, const luba::mat4& b);
luba::mat4 operator * (const luba::mat4& a, double d);
luba::mat4 operator * (double d, const luba::mat4& a);
luba::vec4 operator * (const luba::mat4& a, const luba::vec4& v);
luba::vec4 operator * (const luba::vec4& v, const luba::mat4& a);
luba::mat4 operator / (const luba::mat4& a, double d);

bool operator == (const luba::mat4& a, const luba::mat4& b);
bool operator != (const luba::mat4& a, const luba::mat4& b);

ostream& operator << (ostream& s, const luba::mat4& m);

void swap(luba::mat4& a, luba::mat4& b);

} // namespace of std

#endif

