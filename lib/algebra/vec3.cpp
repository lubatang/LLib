//===- vec3.cpp -----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <algebra/vec3.h>
#include <algebra/vec2.h>
#include <cmath>
#include <cassert>
#include <iostream>

using namespace luba;

//===----------------------------------------------------------------------===//
// vec3
//===----------------------------------------------------------------------===//
vec3::vec3() 
{
  m_N[0] = m_N[1] = m_N[2] = 0.0;
}

vec3::vec3(const vec3& v)
{
  m_N[0] = v.m_N[0];
  m_N[1] = v.m_N[1];
  m_N[2] = v.m_N[2];
}

vec3::vec3(double x, double y, double z)
{
  m_N[0] = x;
  m_N[1] = y;
  m_N[2] = z;
}

vec3::vec3(const vec2& v, double d)
{
  m_N[0] = v[0];
  m_N[1] = v[1];
  m_N[2] = d;
}

vec3 vec3::operator - () const
{
  return vec3(-m_N[0], -m_N[1], -m_N[2]);
}

vec3& vec3::operator = (const vec3& v)
{
  m_N[0] = v.m_N[0];
  m_N[1] = v.m_N[1];
  m_N[2] = v.m_N[2];
  return *this;
}

vec3& vec3::operator += (const vec3& v)
{
  m_N[0] += v.m_N[0];
  m_N[1] += v.m_N[1];
  m_N[2] += v.m_N[2];
  return *this;
}

vec3& vec3::operator -= (const vec3& v)
{
  m_N[0] -= v.m_N[0];
  m_N[1] -= v.m_N[1];
  m_N[2] -= v.m_N[2];
  return *this;
}

vec3& vec3::operator *= (double d)
{
  m_N[0] *= d;
  m_N[1] *= d;
  m_N[2] *= d;
  return *this;
}

vec3& vec3::operator /= ( double d )
{
  assert( d != 0.0 && "divided by zero");
  m_N[0] /= d;
  m_N[1] /= d;
  m_N[2] /= d;
  return *this;
}

double vec3::operator[] (unsigned int i) const
{
  assert(i < 3 && "index is out of range");
  return m_N[i];
}

double& vec3::operator[] (unsigned int i)
{
  assert(i < 3 && "index is out of range");
  return m_N[i];
}

double vec3::length() const
{
  return sqrt(m_N[0]*m_N[0] + m_N[1]*m_N[1] + m_N[2]*m_N[2]);
}

vec3& vec3::normalize()
{
  double d = length();
  assert( d != 0.0 && "divided by zero");
  m_N[0] /= d;
  m_N[1] /= d;
  m_N[2] /= d;
  return *this;
}

void vec3::set(double x, double y, double z)
{
  m_N[0] = x;
  m_N[1] = y;
  m_N[2] = z;
}

//===----------------------------------------------------------------------===//
// std namespace
//===----------------------------------------------------------------------===//
vec3 std::operator + (const vec3& a, const vec3& b)
{
  return vec3(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
}

vec3 std::operator - (const vec3& a, const vec3& b)
{
  return vec3(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
}

double std::operator * (const vec3& a, const vec3& b)
{
  return (a[0]*b[0] + a[1]*b[1] + a[2]*b[2]);
}

vec3 std::operator * (const vec3& a, double d)
{
  return vec3(d*a[0], d*a[1], d*a[2]);
}

vec3 std::operator * (double d, const vec3& a)
{
  return vec3(d*a[0], d*a[1], d*a[2]);
}

vec3 std::operator ^ (const vec3& a, const vec3& b)
{
  return vec3(a[1]*b[2] - a[2]*b[1],
              a[2]*b[0] - a[0]*b[2],
              a[0]*b[1] - a[1]*b[0]);
}

vec3 std::operator / (const vec3& a, double d)
{
  assert( d != 0.0 && "divided by zero");
  vec3 result(a);
  result /= d;
  return result;
}

void std::swap(vec3& a, vec3& b)
{
  vec3 tmp(a);
  a = b;
  b = tmp;
}

bool std::operator == (const vec3& a, const vec3& b)
{
  return ((a[0] == b[0]) &&
          (a[1] == b[1]) &&
          (a[2] == b[2]));
}

bool std::operator != (const vec3& a, const vec3& b)
{
  return !(a == b);
}

std::ostream& std::operator << (std::ostream& s, const vec3& v)
{
  return s << "<" << v[0] << ", " << v[1] << ", " << v[2] << ">";
}

