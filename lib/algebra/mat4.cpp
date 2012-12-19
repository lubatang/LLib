//===- mat4.cpp -----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <algebra/mat4.h>
#include <cassert>
#include <cmath>
#include <iostream>

using namespace luba;

//===----------------------------------------------------------------------===//
// mat4
//===----------------------------------------------------------------------===//
mat4::mat4()
{
  m_Vec[0].set(1.0, 0.0, 0.0, 0.0); 
  m_Vec[1].set(0.0, 1.0, 0.0, 0.0); 
  m_Vec[2].set(0.0, 0.0, 1.0, 0.0); 
  m_Vec[3].set(0.0, 0.0, 0.0, 1.0); 
}

mat4::mat4(const mat4& pCopy)
{
  m_Vec[0] = pCopy.m_Vec[0];
  m_Vec[1] = pCopy.m_Vec[1];
  m_Vec[2] = pCopy.m_Vec[2];
  m_Vec[3] = pCopy.m_Vec[3];
}

mat4::mat4(const vec4& v0, const vec4& v1, const vec4& v2, const vec4& v3)
{
  m_Vec[0] = v0;
  m_Vec[1] = v1;
  m_Vec[2] = v2;
  m_Vec[3] = v3;
}

mat4::mat4(double a00, double a01, double a02, double a03,
           double a10, double a11, double a12, double a13,
           double a20, double a21, double a22, double a23,
           double a30, double a31, double a32, double a33 )
{
  m_Vec[0][0] = a00;  m_Vec[0][1] = a01;  m_Vec[0][2] = a02;  m_Vec[0][3] = a03;
  m_Vec[1][0] = a10;  m_Vec[1][1] = a11;  m_Vec[1][2] = a12;  m_Vec[1][3] = a13;
  m_Vec[2][0] = a20;  m_Vec[2][1] = a21;  m_Vec[2][2] = a22;  m_Vec[2][3] = a23;
  m_Vec[3][0] = a30;  m_Vec[3][1] = a31;  m_Vec[3][2] = a32;  m_Vec[3][3] = a33;
}

mat4 mat4::operator - () const
{
  return mat4(-m_Vec[0][0], -m_Vec[0][1], -m_Vec[0][2], -m_Vec[0][3], 
              -m_Vec[1][0], -m_Vec[1][1], -m_Vec[1][2], -m_Vec[1][3], 
              -m_Vec[2][0], -m_Vec[2][1], -m_Vec[2][2], -m_Vec[2][3], 
              -m_Vec[3][0], -m_Vec[3][1], -m_Vec[3][2], -m_Vec[3][3]);
}

mat4& mat4::operator = (const mat4& pCopy)
{
  m_Vec[0] = pCopy.m_Vec[0];
  m_Vec[1] = pCopy.m_Vec[1];
  m_Vec[2] = pCopy.m_Vec[2];
  m_Vec[3] = pCopy.m_Vec[3];
  return *this;
}

mat4& mat4::operator += (const mat4& pAddend)
{
  m_Vec[0] += pAddend.m_Vec[0];
  m_Vec[1] += pAddend.m_Vec[1];
  m_Vec[2] += pAddend.m_Vec[2];
  m_Vec[3] += pAddend.m_Vec[3];
  return *this;
}

mat4& mat4::operator -= (const mat4& pAddend)
{
  m_Vec[0] -= pAddend.m_Vec[0];
  m_Vec[1] -= pAddend.m_Vec[1];
  m_Vec[2] -= pAddend.m_Vec[2];
  m_Vec[3] -= pAddend.m_Vec[3];
  return *this;
}

mat4& mat4::operator *= (double d)
{
  m_Vec[0] *= d;
  m_Vec[1] *= d;
  m_Vec[2] *= d;
  m_Vec[3] *= d;
  return *this;
}

mat4& mat4::operator /= (double d)
{
  assert(0.0 != d && "divided by zero");
  m_Vec[0] /= d;
  m_Vec[1] /= d;
  m_Vec[2] /= d;
  m_Vec[3] /= d;
  return *this;
}

vec4 mat4::operator [] (unsigned int i) const
{
  assert(i < 4 && "index is out of range");
  return m_Vec[i];
}

vec4& mat4::operator [] (unsigned int i)
{
  assert(i < 4 && "index is out of range");
  return m_Vec[i];
}

mat4 mat4::transpose() const
{
  return mat4(m_Vec[0][0], m_Vec[1][0], m_Vec[2][0], m_Vec[3][0],
              m_Vec[0][1], m_Vec[1][1], m_Vec[2][1], m_Vec[3][1],
              m_Vec[0][2], m_Vec[1][2], m_Vec[2][2], m_Vec[3][2],
              m_Vec[0][3], m_Vec[1][3], m_Vec[2][3], m_Vec[3][3]);
}

mat4 mat4::inverse() const
{
  // Gauss-Jordan elimination with partial pivoting
  mat4 a(*this); // As a evolves from original mat into identity
  mat4 b;        // b evolves from identity into inverse(a)
  unsigned int i, j, i1;

  // Loop over cols of a from left to right, eliminating above and below diag
  for (j=0; j<4; ++j) {
    // Find largest pivot in column j among rows j..3
    i1 = j;        // Row with largest pivot candidate
    for (i=j+1; i<4; ++i) {
      if (fabs(a[i][j]) > fabs(a[i1][j])) {
        i1 = i;
      }
    }
    std::swap(a[i1], a[j]);
    std::swap(b[i1], b[j]);

    // Scale row j to have a unit diagonal
    assert(0.0 != a[j][j] && "mat4::inverse: singular matrix; can't invert");
    b[j] /= a[j][j];
    a[j] /= a[j][j];

    // Eliminate off-diagonal elems in col j of a, doing identical ops to b
    for (i=0; i<4; ++i)
      if (i!=j) {
        b[i] -= (a[i][j] * b[j]);
        a[i] -= (a[i][j] * a[j]);
      }
  }
  return b;
}

template<>
void mat4::swap<mat4::Row>   (unsigned int i, unsigned int j)
{
  vec4 t;

  t = m_Vec[i];
  m_Vec[i] = m_Vec[j];
  m_Vec[j] = t;
}

template<>
void mat4::swap<mat4::Column>(unsigned int i, unsigned int j)
{
  double t;
  unsigned int k;

  for(k=0; k<4; ++k) {
    t       = m_Vec[k][i];
    m_Vec[k][i] = m_Vec[k][j];
    m_Vec[k][j] = t;
  }
}

//===----------------------------------------------------------------------===//
// binary operators
//===----------------------------------------------------------------------===//
mat4 luba::operator + (const mat4& a, const mat4& b)
{
  return mat4(a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]);
}

mat4 luba::operator - (const mat4& a, const mat4& b)
{
  mat4 result(a);
  result -= b;
  return result;
}

mat4 luba::operator * (const mat4& a, const mat4& b)
{
#define ROWCOL(i, j) a[i][0]*b[0][j] + a[i][1]*b[1][j] +  a[i][2]*b[2][j] + a[i][3]*b[3][j]
  return mat4(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2), ROWCOL(0,3),
              ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2), ROWCOL(1,3),
              ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2), ROWCOL(2,3),
              ROWCOL(3,0), ROWCOL(3,1), ROWCOL(3,2), ROWCOL(3,3));
#undef ROWCOL
}

mat4 luba::operator * (const mat4& a, double d)
{
  mat4 result(a);
  result *= d;
  return result;
}

mat4 luba::operator * (double d, const mat4& a)
{
  mat4 result(a);
  result *= d;
  return result;
}

vec4 luba::operator * (const mat4& a, const vec4& v)
{
#define ROWCOL(i) a[i][0]*v[0] + a[i][1]*v[1] + a[i][2]*v[2] + a[i][3]*v[3]
  return vec4(ROWCOL(0), ROWCOL(1), ROWCOL(2), ROWCOL(3));
#undef ROWCOL
}

vec4 luba::operator * (const vec4& v, const mat4& a)
{
#define ROWCOL(i) v[0]*a[0][i] + v[1]*a[1][i] + v[2]*a[2][i] + v[3]*a[3][i]
  return vec4(ROWCOL(0), ROWCOL(1), ROWCOL(2), ROWCOL(3));
#undef ROWCOL
}

mat4 luba::operator / (const mat4& a, double d)
{
  mat4 result(a);
  result /= d;
  return result;
}

bool luba::operator == (const mat4& a, const mat4& b)
{
  return ((a[0] == b[0]) &&
          (a[1] == b[1]) &&
          (a[2] == b[2]) &&
          (a[3] == b[3]));
}

bool luba::operator != (const mat4& a, const mat4& b)
{
  return !(a == b);
}

std::ostream& std::operator << (std::ostream& s, const mat4& m)
{
  return s << m[0] << '\n' << m[1] << '\n' << m[2] << '\n' << m[3];
}

template<>
void std::swap(mat4& a, mat4& b)
{
  mat4 tmp(a);
  a = b;
  b = tmp;
}

