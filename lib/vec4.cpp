//===- vec4.cpp -----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <algebra/algebra.h>
#include <cstdio>

using namespace LLib::Math;

//===----------------------------------------------------------------------===//
// vec4
//===----------------------------------------------------------------------===//
vec4::vec4(void) 
{n[VX] = n[VY] = n[VZ] = 0.0; n[VW] = 1.0; }

vec4::vec4(const double x, const double y, const double z, const double w)
{ n[VX] = x; n[VY] = y; n[VZ] = z; n[VW] = w; }

vec4::vec4(const double d)
{  n[VX] = n[VY] = n[VZ] = n[VW] = d; }

vec4::vec4(const vec4& v)
{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VZ]; n[VW] = v.n[VW]; }

vec4::vec4(const vec3& v)
{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VZ]; n[VW] = 1.0; }

vec4::vec4(const vec3& v, const double d)
{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VZ];  n[VW] = d; }


vec4& vec4::operator = (const vec4& v)
{
  n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VZ]; n[VW] = v.n[VW];
  return *this;
}

vec4& vec4::operator += ( const vec4& v )
{
  n[VX] += v.n[VX]; n[VY] += v.n[VY]; n[VZ] += v.n[VZ]; n[VW] += v.n[VW];
  return *this;
}

vec4& vec4::operator -= ( const vec4& v )
{
  n[VX] -= v.n[VX]; n[VY] -= v.n[VY]; n[VZ] -= v.n[VZ]; n[VW] -= v.n[VW];
  return *this;
}

vec4& vec4::operator *= ( const double d )
{ n[VX] *= d; n[VY] *= d; n[VZ] *= d; n[VW] *= d; return *this; }

vec4& vec4::operator /= ( const double d )
{
  double d_inv = 1./d; n[VX] *= d_inv; n[VY] *= d_inv; n[VZ] *= d_inv;
  n[VW] *= d_inv; return *this;
}

double& vec4::operator [] ( int i) {
  if (i < VX || i > VW)
    //VEC_ERROR("vec4 [] operator: illegal access; index = " << i << '\n')
    VEC_ERROR("vec4 [] operator: illegal access" );

  return n[i];
}

double vec4::length(void)
{ return sqrt(length2()); }

double vec4::length2(void)
{ return n[VX]*n[VX] + n[VY]*n[VY] + n[VZ]*n[VZ] + n[VW]*n[VW]; }

vec4& vec4::normalize(void) // it is up to caller to avoid divide-by-zero
{ *this /= length(); return *this; }

vec4& vec4::homogenize(void) // it is up to caller to avoid divide-by-zero
{ n[VX] /= n[VW];  n[VY] /= n[VW];  n[VZ] /= n[VW]; n[VW] = 1.0;  return *this; }

vec4& vec4::apply(V_FCT_PTR fct)
{
  n[VX] = (*fct)(n[VX]);
  n[VY] = (*fct)(n[VY]);
  n[VZ] = (*fct)(n[VZ]);
  n[VW] = (*fct)(n[VW]);
  return *this;
}

void  vec4::print(FILE *file, const char* name )  // print vector to a file
{
  fprintf( file, "%s: <%f, %f, %f, %f>\n", name, n[VX], n[VY], n[VZ], n[VW] );
}

void vec4::set( double x, double y, double z, double a)
{
  n[0] = x; n[1] = y; n[2] = z; n[3] = a;
}

