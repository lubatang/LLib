//===- vec2.cpp -----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <algebra/vec2.h>
#include <cmath>
#include <cassert>
#include <iostream>

using namespace luba;

//===----------------------------------------------------------------------===//
// vec2
//===----------------------------------------------------------------------===//
vec2::vec2() 
{
  m_N[0] = m_N[1] = 0.0;
}

vec2::vec2(double x, double y)
{
  m_N[0] = x;
  m_N[1] = y;
}

vec2::vec2(const vec2& v)
{
  m_N[0] = v.m_N[0];
  m_N[1] = v.m_N[1];
}

vec2& vec2::operator= (const vec2& v)
{
  m_N[0] = v.m_N[0];
  m_N[1] = v.m_N[1];
  return *this;
}

vec2& vec2::set( double x, double y )
{
  m_N[0] = x;
  m_N[1] = y;
  return *this;
}

double vec2::length() const
{
  return ::sqrt(m_N[0]*m_N[0] + m_N[1]*m_N[1]);
}

vec2& vec2::normalize()
{
  double len = length();
  m_N[0] /= len;
  m_N[1] /= len;
  return *this;
}

double vec2::operator [] (unsigned int i) const
{
  assert(i < 2 && "index of vec2 is out of range");
  return m_N[i];
}

double& vec2::operator [] (unsigned int i)
{
  assert(i < 2 && "index of vec2 is out of range");
  return m_N[i];
}

vec2 vec2::operator-() const
{
  return vec2(-m_N[0], -m_N[1]);
}

vec2& vec2::operator += ( const vec2& v )
{
  m_N[0] += v.m_N[0];
  m_N[1] += v.m_N[1];
  return *this;
}

vec2& vec2::operator -= ( const vec2& v )
{
  m_N[0] -= v.m_N[0];
  m_N[1] -= v.m_N[1];
  return *this;
}

vec2& vec2::operator *= ( const double d )
{
  m_N[0] *= d;
  m_N[1] *= d;
  return *this;
}

vec2& vec2::operator /= ( const double d )
{
  m_N[0] /= d;
  m_N[1] /= d;
  return *this;
}

//===----------------------------------------------------------------------===//
// binary operators
//===----------------------------------------------------------------------===//
vec2 std::operator + (const vec2& a, const vec2& b)
{
  vec2 result(a);
  result += b;
  return result;
}

vec2 std::operator - (const vec2& a, const vec2& b)
{
  vec2 result(a);
  result -= b;
  return result;
}

double std::operator * (const vec2& a, const vec2& b)
{
  return (a[0]*b[0] + a[1]*b[1]);
}

vec2 std::operator * (const vec2& a, const double d)
{
  return vec2(d*a[0], d*a[1]);
}

vec2 std::operator * (double d, const vec2& a)
{ return a*d; }

vec2 std::operator / (const vec2& a, double d)
{
  double d_inv = 1./d;
  return vec2(a[0]*d_inv, a[1]*d_inv);
}

bool std::operator == (const vec2& a, const vec2& b)
{
  return (a[0] == b[0]) && (a[1] == b[1]);
}

bool std::operator != (const vec2& a, const vec2& b)
{
  return !(a == b);
}

std::ostream& std::operator << (std::ostream& s, const vec2& v)
{
  return s << "<" << v[0] << ", " << v[1] << ">";
}

void std::swap(vec2& a, vec2& b)
{
  vec2 tmp(a);
  a = b;
  b = tmp;
}

