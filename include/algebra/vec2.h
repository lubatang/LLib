//===- vec2.h -------------------------------------------------------------===//
//
// copyright (c), 2012-
// luba tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_VECTOR_2X1_H
#define LUBA_VECTOR_2X1_H

#include <iosfwd>

namespace luba {

class vec3;

/** \class vec2
 *  \brief vec2 is 2x1 vector
 */
class vec2
{
public:
  vec2();
  vec2(const vec2& v);
  explicit vec2(double x, double y);

  // unary operators
  vec2& operator  = ( const vec2& v );
  vec2& operator += ( const vec2& v );
  vec2& operator -= ( const vec2& v );
  vec2& operator *= ( double d );
  vec2& operator /= ( double d );

  const double& x() const { return m_N[0]; }
  double        x()       { return m_N[0]; }

  const double& y() const { return m_N[1]; }
  double        y()       { return m_N[1]; }

  double  operator[] (unsigned int idx) const;
  double& operator[] (unsigned int idx);

  vec2 operator-() const;

  vec2& set(double x, double y );

  double length() const;

  vec2& normalize();

  template<typename Action>
  vec2& apply() {
    m_N[0] = Action(m_N[0]);
    m_N[1] = Action(m_N[1]);
    return *this;
  }

  double* native() { return m_N; }

private:
  double m_N[2];

};

} // namespace luba

namespace std {

luba::vec2 operator + (const luba::vec2& a, const luba::vec2& b);
luba::vec2 operator - (const luba::vec2& a, const luba::vec2& b);
double operator * (const luba::vec2& a, const luba::vec2& b);
luba::vec2 operator * (const luba::vec2& a, double d);
luba::vec2 operator * (double d, const luba::vec2& a);

luba::vec2 operator / (const luba::vec2& a, double d);

bool operator == (const luba::vec2& a, const luba::vec2& b);
bool operator != (const luba::vec2& a, const luba::vec2& b);

void swap(luba::vec2& a, luba::vec2& b);
luba::vec2 min(const luba::vec2& a, const luba::vec2& b);
luba::vec2 max(const luba::vec2& a, const luba::vec2& b);

std::ostream& operator << (std::ostream& s, const luba::vec2& v);

} // namespace std

#endif

