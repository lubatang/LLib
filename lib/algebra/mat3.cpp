//===- mat3.cpp -----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <algebra/mat3.h>
#include <cassert>
#include <cmath>
#include <iostream>

using namespace luba;
using namespace std;

//===----------------------------------------------------------------------===//
// mat3
//===----------------------------------------------------------------------===//
mat3::mat3()
{
  m_Vec[0].set(1.0, 0.0, 0.0);
  m_Vec[1].set(0.0, 1.0, 0.0);
  m_Vec[2].set(0.0, 0.0, 1.0);
}

mat3::mat3(const mat3& m)
{
  m_Vec[0] = m.m_Vec[0];
  m_Vec[1] = m.m_Vec[1];
  m_Vec[2] = m.m_Vec[2];
}

mat3::mat3(double a00, double a01, double a02,
           double a10, double a11, double a12,
           double a20, double a21, double a22)
{
  m_Vec[0].set(a00, a01, a02);
  m_Vec[1].set(a10, a11, a12);
  m_Vec[2].set(a20, a21, a22);
}

mat3::mat3(const vec3& v0, const vec3& v1, const vec3& v2)
{
  m_Vec[0] = v0;
  m_Vec[1] = v1;
  m_Vec[2] = v2;
}

mat3 mat3::operator-() const
{
  return mat3(-m_Vec[0], -m_Vec[1], -m_Vec[2]);
}

mat3& mat3::operator = (const mat3& m)
{
  m_Vec[0] = m.m_Vec[0];
  m_Vec[1] = m.m_Vec[1];
  m_Vec[2] = m.m_Vec[2];
  return *this;
}

mat3& mat3::operator += (const mat3& m)
{
  m_Vec[0] += m.m_Vec[0];
  m_Vec[1] += m.m_Vec[1];
  m_Vec[2] += m.m_Vec[2];
  return *this;
}

mat3& mat3::operator -= (const mat3& m)
{
  m_Vec[0] -= m.m_Vec[0];
  m_Vec[1] -= m.m_Vec[1];
  m_Vec[2] -= m.m_Vec[2];
  return *this;
}

mat3& mat3::operator *= (double d )
{
  m_Vec[0] *= d;
  m_Vec[1] *= d;
  m_Vec[2] *= d;
  return *this;
}

mat3& mat3::operator /= (double d )
{
  m_Vec[0] /= d;
  m_Vec[1] /= d;
  m_Vec[2] /= d;
  return *this;
}

vec3 mat3::operator [] (unsigned int i) const
{
  assert(i < 3 && "index is out of range");
  return m_Vec[i];
}

vec3& mat3::operator [] (unsigned int i)
{
  assert(i < 3 && "index is out of range");
  return m_Vec[i];
}

void mat3::set(const vec3& v0, const vec3& v1, const vec3& v2)
{
  m_Vec[0] = v0;
  m_Vec[1] = v1;
  m_Vec[2] = v2;
}

mat3 mat3::transpose() const
{
  return mat3(vec3(m_Vec[0][0], m_Vec[1][0], m_Vec[2][0]),
              vec3(m_Vec[0][1], m_Vec[1][1], m_Vec[2][1]),
              vec3(m_Vec[0][2], m_Vec[1][2], m_Vec[2][2]));
}

mat3 mat3::inverse() const
{
  // Gauss-Jordan elimination with partial pivoting
  mat3 a(*this); // As a evolves from original mat into identity
  mat3 b;        // b evolves from identity into inverse(a)

  unsigned int   i, j, i1;

  // Loop over cols of a from left to right, eliminating above and below diag
  for (j=0; j<3; ++j) {   // Find largest pivot in column j among rows j..2
    i1 = j;        // Row with largest pivot candidate
    for (i=j+1; i<3; ++i)
      if (fabs(a[i][j]) > fabs(a[i1][j]))
        i1 = i;

    // Swap rows i1 and j in a and b to put pivot on diagonal
    std::swap(a[i1], a[j]);
    std::swap(b[i1], b[j]);

    // Scale row j to have a unit diagonal
    assert(0.0 != a[j][j] && "mat3::inverse: singular matrix; can't invert");
    b[j] /= a[j][j];
    a[j] /= a[j][j];

    // Eliminate off-diagonal elems in col j of a, doing identical ops to b
    for (i=0; i<3; ++i)
      if (i!=j) {
        b[i] -= a[i][j] * b[j];
        a[i] -= a[i][j] * a[j];
      }
  }
  return b;
}

//===----------------------------------------------------------------------===//
// binary operators
//===----------------------------------------------------------------------===//
mat3 std::operator + (const mat3& a, const mat3& b)
{
  return mat3(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
}

mat3 std::operator - (const mat3& a, const mat3& b)
{
  return mat3(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
}

mat3 std::operator * (const mat3& a, const mat3& b)
{
#define ROWCOL(i, j) a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j]

  return mat3(vec3(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2)),
              vec3(ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2)),
              vec3(ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2)));
#undef ROWCOL
}

mat3 std::operator * (const mat3& a, double d)
{
  mat3 result(a);
  result[0] *= d;
  result[1] *= d;
  result[2] *= d;
  return result;
}

mat3 std::operator * (double d, const mat3& a)
{
  mat3 result(a);
  result[0] *= d;
  result[1] *= d;
  result[2] *= d;
  return result;
}

mat3 std::operator / (const mat3& a, double d)
{
  assert(0.0 != d && "divided by zero");
  mat3 result(a);
  result[0] /= d;
  result[1] /= d;
  result[2] /= d;
  return result;
}

bool std::operator == (const mat3& a, const mat3& b)
{
  return ((a[0] == b[0]) &&
          (a[1] == b[1]) &&
          (a[2] == b[2]));
}

bool std::operator != (const mat3& a, const mat3& b)
{
  return !(a == b);
}

std::ostream& std::operator << (std::ostream& s, mat3& m)
{
  return s << m[0] << '\n' << m[1] << '\n' << m[2];
}

void std::swap(mat3& a, mat3& b)
{
  mat3 tmp(a);
  a = b;
  b = tmp;
}

vec3 std::operator* (const mat3& a, const vec3& v)
{
  vec3 result;

  result[0] = a[0][0]*v[0] + a[0][1]*v[1] + a[0][2]*v[2];
  result[1] = a[1][0]*v[0] + a[1][1]*v[1] + a[1][2]*v[2];
  result[2] = a[2][0]*v[0] + a[2][1]*v[1] + a[2][2]*v[2];
  return result;
}

vec3 std::operator* (const vec3& v, const mat3& a)
{
  vec3 result;

  result[0] = v[0]*a[0][0] + v[1]*a[1][0] + v[2]*a[2][0];
  result[1] = v[0]*a[0][1] + v[1]*a[1][1] + v[2]*a[2][1];
  result[2] = v[0]*a[0][2] + v[1]*a[1][2] + v[2]*a[2][2];
  return result;
}

