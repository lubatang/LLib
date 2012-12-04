//===- vec2.cpp -----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <algebra/algebra.h>

using namespace LLib::Math;

//===----------------------------------------------------------------------===//
// vec2
//===----------------------------------------------------------------------===//
vec2::vec2(void) 
{
  n[VX] = n[VY] = 0.0;
}

vec2::vec2(const double x, const double y)
{ n[VX] = x; n[VY] = y; }

vec2::vec2(const double d)
{ n[VX] = n[VY] = d; }

vec2::vec2(const vec2& v)
{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; }

vec2::vec2(const vec3& v) // it is up to caller to avoid divide-by-zero
{ n[VX] = v.n[VX]/v.n[VZ]; n[VY] = v.n[VY]/v.n[VZ]; };

vec2::vec2(const vec3& v, int dropAxis)
{
  switch (dropAxis) {
    case VX: n[VX] = v.n[VY]; n[VY] = v.n[VZ]; break;
    case VY: n[VX] = v.n[VX]; n[VY] = v.n[VZ]; break;
    default: n[VX] = v.n[VX]; n[VY] = v.n[VY]; break;
  }
}

vec2& vec2::operator = (const vec2& v)
{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; return *this; }

vec2& vec2::operator += ( const vec2& v )
{ n[VX] += v.n[VX]; n[VY] += v.n[VY]; return *this; }

vec2& vec2::operator -= ( const vec2& v )
{ n[VX] -= v.n[VX]; n[VY] -= v.n[VY]; return *this; }

vec2& vec2::operator *= ( const double d )
{ n[VX] *= d; n[VY] *= d; return *this; }

vec2& vec2::operator /= ( const double d )
{ double d_inv = 1./d; n[VX] *= d_inv; n[VY] *= d_inv; return *this; }

double& vec2::operator [] ( int i)
{
  if (i < VX || i > VY)
    //VEC_ERROR("vec2 [] operator: illegal access; index = " << i << '\n')
    VEC_ERROR("vec2 [] operator: illegal access" );
  return n[i];
}

double vec2::length(void)
{ return sqrt(length2()); }

double vec2::length2(void)
{ return n[VX]*n[VX] + n[VY]*n[VY]; }

vec2& vec2::normalize(void) // it is up to caller to avoid divide-by-zero
{ *this /= length(); return *this; }

vec2& vec2::apply(V_FCT_PTR fct)
{ n[VX] = (*fct)(n[VX]); n[VY] = (*fct)(n[VY]); return *this; }

void vec2::set( double x, double y )
{  n[VX] = x;   n[VY] = y; }

