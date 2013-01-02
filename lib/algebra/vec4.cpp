//===- vec4.cpp -----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <algebra/vec4.h>
#include <algebra/vec3.h>
#include <cassert>
#include <cmath>
#include <iostream>

using namespace luba;

//===----------------------------------------------------------------------===//
// vec4
//===----------------------------------------------------------------------===//
vec4::vec4() 
{
  m_N[0] = m_N[1] = m_N[2] = m_N[3] = 0.0;
}

vec4::vec4(const vec4& v)
{
  m_N[0] = v.m_N[0];
  m_N[1] = v.m_N[1];
  m_N[2] = v.m_N[2];
  m_N[3] = v.m_N[3];
}

vec4::vec4(double x, double y, double z, double w)
{
  m_N[0] = x;
  m_N[1] = y;
  m_N[2] = z;
  m_N[3] = w;
}

vec4::vec4(const vec3& v, double d)
{
  m_N[0] = v[0];
  m_N[1] = v[1];
  m_N[2] = v[2];
  m_N[3] = d;
}

vec4::operator vec3() const
{
  vec3 result;
  result[0] = m_N[0];
  result[1] = m_N[1];
  result[2] = m_N[2];
  return result;
}

vec4 vec4::operator-() const
{
  return vec4(-m_N[0], -m_N[1], -m_N[2], -m_N[3]);
}

vec4& vec4::operator = (const vec4& v)
{
  m_N[0] = v.m_N[0];
  m_N[1] = v.m_N[1];
  m_N[2] = v.m_N[2];
  m_N[3] = v.m_N[3];
  return *this;
}

vec4& vec4::operator += (const vec4& v)
{
  m_N[0] += v.m_N[0];
  m_N[1] += v.m_N[1];
  m_N[2] += v.m_N[2];
  m_N[3] += v.m_N[3];
  return *this;
}

vec4& vec4::operator -= (const vec4& v)
{
  m_N[0] -= v.m_N[0];
  m_N[1] -= v.m_N[1];
  m_N[2] -= v.m_N[2];
  m_N[3] -= v.m_N[3];
  return *this;
}

vec4& vec4::operator *= (double d)
{
  m_N[0] *= d;
  m_N[1] *= d;
  m_N[2] *= d;
  m_N[3] *= d;
  return *this;
}

vec4& vec4::operator /= ( double d )
{
  assert(d != 0.0 && "divided by zero");
  m_N[0] /= d;
  m_N[1] /= d;
  m_N[2] /= d;
  m_N[3] /= d;
  return *this;
}

double vec4::operator [] (unsigned int idx) const
{
  assert(idx < 4 && "index is out of range");
  return m_N[idx];
}

double& vec4::operator [] (unsigned int idx)
{
  assert(idx < 4 && "index is out of range");
  return m_N[idx];
}

double vec4::length() const
{
  return sqrt(m_N[0]*m_N[0] + m_N[1]*m_N[1] + m_N[2]*m_N[2] + m_N[3]*m_N[3]);
}

vec4& vec4::normalize()
{
  double len = length();
  assert(len != 0.0 && "divided by zero");
  m_N[0] /= len;
  m_N[1] /= len;
  m_N[2] /= len;
  m_N[3] /= len;
  return *this;
}

void vec4::set(double x, double y, double z, double w)
{
  m_N[0] = x;
  m_N[1] = y;
  m_N[2] = z;
  m_N[3] = w;
}

vec4 luba::operator-(const vec4& a, const vec4& b)
{
  vec4 result(a);
  return (result -= b);
}

vec4 luba::operator + (const vec4& a, const vec4& b)
{
  vec4 result(a);
  result += b;
  return result;
}

vec4 luba::operator * (const vec4& a, double d)
{
  vec4 result(a);
  result *= d;
  return result;
}

vec4 luba::operator * (double d, const vec4& a)
{
  vec4 result(a);
  result *= d;
  return result;
}

double luba::operator * (const vec4& a, const vec4& b)
{
  return (a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3]);
}

vec4 luba::operator / (const vec4& a, double d)
{
  vec4 result(a);
  result /= d;
  return result;
}

bool luba::operator == (const vec4& a, const vec4& b)
{
  return ((a[0] == b[0]) &&
          (a[1] == b[1]) &&
          (a[2] == b[2]) &&
          (a[3] == b[3]));
}

bool luba::operator != (const vec4& a, const vec4& b)
{
  return !(a == b);
}

//===----------------------------------------------------------------------===//
// namespace std
//===----------------------------------------------------------------------===//
std::ostream& std::operator << (std::ostream& s, const vec4& v)
{
  return s << "<" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ">";
}

template<>
void std::swap(vec4& a, vec4& b)
{
  vec4 tmp(a);
  a = b;
  b = tmp;
}

