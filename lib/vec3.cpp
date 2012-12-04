//===- vec3.cpp -----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <algebra/algebra.h>
#include <cstdio>

using namespace LLib::Math;

//===----------------------------------------------------------------------===//
// vec3
//===----------------------------------------------------------------------===//
vec3::vec3(void) 
{
  n[VX] = n[VY] = n[VZ] = 0.0;
}

vec3::vec3(const double x, const double y, const double z)
{ n[VX] = x; n[VY] = y; n[VZ] = z; }

vec3::vec3(const double d)
{ n[VX] = n[VY] = n[VZ] = d; }

vec3::vec3(const vec3& v)
{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VZ]; }

vec3::vec3(const vec2& v)
{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = 1.0; }

vec3::vec3(const vec2& v, double d)
{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = d; }

vec3::vec3(const vec4& v) // it is up to caller to avoid divide-by-zero
{
  n[VX] = v.n[VX] / v.n[VW]; n[VY] = v.n[VY] / v.n[VW];
  n[VZ] = v.n[VZ] / v.n[VW];
}

vec3::vec3(const vec4& v, int dropAxis)
{
  switch (dropAxis) {
    case VX: n[VX] = v.n[VY]; n[VY] = v.n[VZ]; n[VZ] = v.n[VW]; break;
    case VY: n[VX] = v.n[VX]; n[VY] = v.n[VZ]; n[VZ] = v.n[VW]; break;
    case VZ: n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VW]; break;
    default: n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VZ]; break;
  }
}


vec3& vec3::operator = (const vec3& v)
{
  n[VX] = v.n[VX];
  n[VY] = v.n[VY];
  n[VZ] = v.n[VZ];
  return *this;
}

vec3& vec3::operator += ( const vec3& v )
{ n[VX] += v.n[VX]; n[VY] += v.n[VY]; n[VZ] += v.n[VZ]; return *this; }

vec3& vec3::operator -= ( const vec3& v )
{ n[VX] -= v.n[VX]; n[VY] -= v.n[VY]; n[VZ] -= v.n[VZ]; return *this; }

vec3& vec3::operator *= ( const double d )
{ n[VX] *= d; n[VY] *= d; n[VZ] *= d; return *this; }

vec3& vec3::operator /= ( const double d )
{
  double d_inv = 1./d;
  n[VX] *= d_inv; n[VY] *= d_inv; n[VZ] *= d_inv;
  return *this;
}

double& vec3::operator [] ( int i)
{
  if (i < VX || i > VZ)
    VEC_ERROR("vec3 [] operator: illegal access" );

  return n[i];
}


// SPECIAL FUNCTIONS

double vec3::length(void)
{  return sqrt(length2()); }

double vec3::length2(void)
{  return n[VX]*n[VX] + n[VY]*n[VY] + n[VZ]*n[VZ]; }

vec3& vec3::normalize(void) // it is up to caller to avoid divide-by-zero
{ *this /= length(); return *this; }

vec3& vec3::homogenize(void) // it is up to caller to avoid divide-by-zero
{ n[VX] /= n[VZ];  n[VY] /= n[VZ];  n[VZ] = 1.0; return *this; }

vec3& vec3::apply(V_FCT_PTR fct)
{
  n[VX] = (*fct)(n[VX]); n[VY] = (*fct)(n[VY]); n[VZ] = (*fct)(n[VZ]);
  return *this;
}

void  vec3::set( double x, double y, double z )     // set vector
{ n[VX] = x; n[VY] = y; n[VZ] = z;  }

void  vec3::print(FILE *file, const char *name )  // print vector to a file
{
  fprintf( file, "%s: <%f, %f, %f>\n", name, n[VX], n[VY], n[VZ] );
}

