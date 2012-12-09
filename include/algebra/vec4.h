//===- vec4.h -------------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_VECTOR_4X1_H
#define LUBA_VECTOR_4X1_H

#include <iosfwd>

namespace luba {

class vec3;
class mat3;
class mat4;

/** \class vec4
 *  \brief vec4 is a 4x1 vector
 */
class vec4
{
public:
  vec4();
  vec4(const vec4& v);

  explicit vec4(double x, double y, double z, double w);
  explicit vec4(const vec3& v, double d);

  vec4 operator-() const;

  vec4& operator  = ( const vec4& v );
  vec4& operator += ( const vec4& v );
  vec4& operator -= ( const vec4& v );
  vec4& operator *= ( double d );
  vec4& operator /= ( double d );

  double  operator [] (unsigned int idx) const;
  double& operator [] (unsigned int idx);

  double length() const;

  vec4& normalize();

  void set(double x, double y, double z, double w);

  template<typename Action>
  vec4& apply() {
    m_N[0] = Action(m_N[0]);
    m_N[1] = Action(m_N[1]);
    m_N[2] = Action(m_N[2]);
    m_N[3] = Action(m_N[3]);
    return *this;
  }

  double* native() { return m_N; }

private:
  double m_N[4];

};

} // namespace of luba

namespace std {

luba::vec4 operator + (const luba::vec4& a, const luba::vec4& b);
luba::vec4 operator - (const luba::vec4& a, const luba::vec4& b);
luba::vec4 operator * (const luba::vec4& a, double d);
luba::vec4 operator * (double d, const luba::vec4& a);
double operator * (const luba::vec4& a, const luba::vec4& b);
luba::vec4 operator / (const luba::vec4& a, double d);
bool operator == (const luba::vec4& a, const luba::vec4& b);
bool operator != (const luba::vec4& a, const luba::vec4& b);

std::ostream& operator<< (ostream& s, const luba::vec4& v);
void swap(luba::vec4& a, luba::vec4& b);

} // namespace of std

#endif

