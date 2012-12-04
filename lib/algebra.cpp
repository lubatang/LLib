#include <math.h>
#include <algebra/algebra.h>
#include <ctype.h>
#include <iostream>

using namespace LLib::Math;

namespace LLib {
namespace Math {

vec2 operator - (const vec2& a)
{ return vec2(-a.n[VX],-a.n[VY]); }

vec2 operator + (const vec2& a, const vec2& b)
{ return vec2(a.n[VX]+ b.n[VX], a.n[VY] + b.n[VY]); }

vec2 operator - (const vec2& a, const vec2& b)
{ return vec2(a.n[VX]-b.n[VX], a.n[VY]-b.n[VY]); }

vec2 operator * (const vec2& a, const double d)
{ return vec2(d*a.n[VX], d*a.n[VY]); }

vec2 operator * (const double d, const vec2& a)
{ return a*d; }

vec2 operator * (const mat3& a, const vec2& v)
{
  vec3 av;

  av.n[VX] = a.v[0].n[VX]*v.n[VX] + a.v[0].n[VY]*v.n[VY] + a.v[0].n[VZ];
  av.n[VY] = a.v[1].n[VX]*v.n[VX] + a.v[1].n[VY]*v.n[VY] + a.v[1].n[VZ];
  av.n[VZ] = a.v[2].n[VX]*v.n[VX] + a.v[2].n[VY]*v.n[VY] + a.v[2].n[VZ];
  return av;
}

vec2 operator * (const vec2& v, mat3& a)
{ return a.transpose() * v; }

vec3 operator * (const mat3& a, const vec3& v)
{
  vec3 av;

  av.n[VX] = 
      a.v[0].n[VX]*v.n[VX] + a.v[0].n[VY]*v.n[VY] + a.v[0].n[VZ]*v.n[VZ];
  av.n[VY] = 
      a.v[1].n[VX]*v.n[VX] + a.v[1].n[VY]*v.n[VY] + a.v[1].n[VZ]*v.n[VZ];
  av.n[VZ] = 
      a.v[2].n[VX]*v.n[VX] + a.v[2].n[VY]*v.n[VY] + a.v[2].n[VZ]*v.n[VZ];
  return av;
}

vec3 operator * (const vec3& v, mat3& a) 
{ return a.transpose() * v; }

double operator * (const vec2& a, const vec2& b)
{ return (a.n[VX]*b.n[VX] + a.n[VY]*b.n[VY]); }

vec2 operator / (const vec2& a, const double d)
{ double d_inv = 1./d; return vec2(a.n[VX]*d_inv, a.n[VY]*d_inv); }

vec3 operator ^ (const vec2& a, const vec2& b)
{ return vec3(0.0, 0.0, a.n[VX] * b.n[VY] - b.n[VX] * a.n[VY]); }

int operator == (const vec2& a, const vec2& b)
{ return (a.n[VX] == b.n[VX]) && (a.n[VY] == b.n[VY]); }

int operator != (const vec2& a, const vec2& b)
{ return !(a == b); }

std::ostream& operator << (std::ostream& s, vec2& v)
{ return s << "| " << v.n[VX] << ' ' << v.n[VY] << " |"; }

std::istream& operator >> (std::istream& s, vec2& v)
{
  vec2  v_tmp;
  char  c = ' ';

  while (isspace(c))
    s >> c;
  // The vectors can be formatted either as x y or | x y |
  if (c == '|') {
    s >> v_tmp[VX] >> v_tmp[VY];
    while (s >> c && isspace(c)) ;
    if (c != '|')
      ;//s.set(_bad);
  }
  else {
    s.putback(c);
    s >> v_tmp[VX] >> v_tmp[VY];
  }
  if (s)
    v = v_tmp;
  return s;
}

/*
vec2 min(const vec2& a, const vec2& b)
{ return vec2(MIN(a.n[VX], b.n[VX]), MIN(a.n[VY], b.n[VY])); }

vec2 max(const vec2& a, const vec2& b)
{ return vec2(MAX(a.n[VX], b.n[VX]), MAX(a.n[VY], b.n[VY])); }
*/

vec2 prod(const vec2& a, const vec2& b)
{ return vec2(a.n[VX] * b.n[VX], a.n[VY] * b.n[VY]); }

vec3 operator - (const vec3& a)
{  return vec3(-a.n[VX],-a.n[VY],-a.n[VZ]); }

vec3 operator + (const vec3& a, const vec3& b)
{ return vec3(a.n[VX]+ b.n[VX], a.n[VY] + b.n[VY], a.n[VZ] + b.n[VZ]); }

vec3 operator - (const vec3& a, const vec3& b)
{ return vec3(a.n[VX]-b.n[VX], a.n[VY]-b.n[VY], a.n[VZ]-b.n[VZ]); }

vec3 operator * (const vec3& a, const double d)
{ return vec3(d*a.n[VX], d*a.n[VY], d*a.n[VZ]); }

vec3 operator * (const double d, const vec3& a)
{ return a*d; }

vec3 operator * (const mat4& a, const vec3& v)
{ return a * vec4(v); }

vec3 operator * (const vec3& v, mat4& a)
{ return a.transpose() * v; }

double operator * (const vec3& a, const vec3& b)
{ return (a.n[VX]*b.n[VX] + a.n[VY]*b.n[VY] + a.n[VZ]*b.n[VZ]); }

vec3 operator / (const vec3& a, const double d)
{
  double d_inv = 1./d; return vec3(a.n[VX]*d_inv, a.n[VY]*d_inv,
  a.n[VZ]*d_inv);
}

vec3 operator ^ (const vec3& a, const vec3& b) {
  return vec3(a.n[VY]*b.n[VZ] - a.n[VZ]*b.n[VY],
              a.n[VZ]*b.n[VX] - a.n[VX]*b.n[VZ],
              a.n[VX]*b.n[VY] - a.n[VY]*b.n[VX]);
}

int operator == (const vec3& a, const vec3& b)
{ return (a.n[VX] == b.n[VX]) && (a.n[VY] == b.n[VY]) && (a.n[VZ] == b.n[VZ]); }

int operator != (const vec3& a, const vec3& b)
{ return !(a == b); }

std::ostream& operator << (std::ostream& s, vec3& v)
{ return s << "| " << v.n[VX] << ' ' << v.n[VY] << ' ' << v.n[VZ] << " |"; }

std::istream& operator >> (std::istream& s, vec3& v) {
  vec3  v_tmp;
  char  c = ' ';

  while (isspace(c))
    s >> c;
  // The vectors can be formatted either as x y z or | x y z |
  if (c == '|') {
    s >> v_tmp[VX] >> v_tmp[VY] >> v_tmp[VZ];
    while (s >> c && isspace(c)) ;
    if (c != '|')
      ;//s.set(_bad);
  }
  else {
    s.putback(c);
    s >> v_tmp[VX] >> v_tmp[VY] >> v_tmp[VZ];
  }
  if (s)
    v = v_tmp;
  return s;
}

vec3 min(const vec3& a, const vec3& b)
{
  return vec3(MIN(a.n[VX], b.n[VX]), MIN(a.n[VY], b.n[VY]), MIN(a.n[VZ], b.n[VZ]));
}

vec3 max(const vec3& a, const vec3& b)
{
  return vec3(MAX(a.n[VX], b.n[VX]), MAX(a.n[VY], b.n[VY]), MAX(a.n[VZ],b.n[VZ]));
}

vec3 prod(const vec3& a, const vec3& b)
{
  return vec3(a.n[VX] * b.n[VX], a.n[VY] * b.n[VY], a.n[VZ] * b.n[VZ]);
}

vec4 operator - (const vec4& a)
{ return vec4(-a.n[VX],-a.n[VY],-a.n[VZ],-a.n[VW]); }

vec4 operator + (const vec4& a, const vec4& b)
{ return vec4(a.n[VX] + b.n[VX], a.n[VY] + b.n[VY], a.n[VZ] + b.n[VZ],
    a.n[VW] + b.n[VW]); }

vec4 operator - (const vec4& a, const vec4& b)
{  return vec4(a.n[VX] - b.n[VX], a.n[VY] - b.n[VY], a.n[VZ] - b.n[VZ],
    a.n[VW] - b.n[VW]); }

vec4 operator * (const vec4& a, const double d)
{ return vec4(d*a.n[VX], d*a.n[VY], d*a.n[VZ], d*a.n[VW] ); }

vec4 operator * (const double d, const vec4& a)
{ return a*d; }

vec4 operator * (const mat4& a, const vec4& v) {
#define ROWCOL(i) a.v[i].n[0]*v.n[VX] + a.v[i].n[1]*v.n[VY] \
  + a.v[i].n[2]*v.n[VZ] + a.v[i].n[3]*v.n[VW]
  return vec4(ROWCOL(0), ROWCOL(1), ROWCOL(2), ROWCOL(3));
#undef ROWCOL
}

vec4 operator * (const vec4& v, mat4& a)
{ return a.transpose() * v; }

double operator * (const vec4& a, const vec4& b)
{ return (a.n[VX]*b.n[VX] + a.n[VY]*b.n[VY] + a.n[VZ]*b.n[VZ] +
    a.n[VW]*b.n[VW]); }

vec4 operator / (const vec4& a, const double d)
{ double d_inv = 1./d; return vec4(a.n[VX]*d_inv, a.n[VY]*d_inv, a.n[VZ]*d_inv,
    a.n[VW]*d_inv); }

  int operator == (const vec4& a, const vec4& b)
{ return (a.n[VX] == b.n[VX]) && (a.n[VY] == b.n[VY]) && (a.n[VZ] == b.n[VZ])
  && (a.n[VW] == b.n[VW]); }

int operator != (const vec4& a, const vec4& b)
{ return !(a == b); }

std::ostream& operator << (std::ostream& s, vec4& v)
{ return s << "| " << v.n[VX] << ' ' << v.n[VY] << ' ' << v.n[VZ] << ' '
  << v.n[VW] << " |"; }

  std::istream& operator >> (std::istream& s, vec4& v) {
    vec4  v_tmp;
    char  c = ' ';

    while (isspace(c))
      s >> c;
    // The vectors can be formatted either as x y z w or | x y z w |
    if (c == '|') {
      s >> v_tmp[VX] >> v_tmp[VY] >> v_tmp[VZ] >> v_tmp[VW];
      while (s >> c && isspace(c)) ;
      if (c != '|')
        ;//s.set(_bad);
    }
    else {
      s.putback(c);
      s >> v_tmp[VX] >> v_tmp[VY] >> v_tmp[VZ] >> v_tmp[VW];
    }
    if (s)
      v = v_tmp;
    return s;
  }

/*
   vec4 min(const vec4& a, const vec4& b)
   { return vec4(MIN(a.n[VX], b.n[VX]), MIN(a.n[VY], b.n[VY]), MIN(a.n[VZ],
   b.n[VZ]), MIN(a.n[VW], b.n[VW])); }

   vec4 max(const vec4& a, const vec4& b)
   { return vec4(MAX(a.n[VX], b.n[VX]), MAX(a.n[VY], b.n[VY]), MAX(a.n[VZ],
   b.n[VZ]), MAX(a.n[VW], b.n[VW])); }
 */
vec4 prod(const vec4& a, const vec4& b)
{
  return vec4(a.n[VX] * b.n[VX], a.n[VY] * b.n[VY], a.n[VZ] * b.n[VZ], a.n[VW] * b.n[VW]);
}

mat3 operator - (const mat3& a)
{ return mat3(-a.v[0], -a.v[1], -a.v[2]); }

mat3 operator + (const mat3& a, const mat3& b)
{ return mat3(a.v[0] + b.v[0], a.v[1] + b.v[1], a.v[2] + b.v[2]); }

mat3 operator - (const mat3& a, const mat3& b)
{ return mat3(a.v[0] - b.v[0], a.v[1] - b.v[1], a.v[2] - b.v[2]); }

mat3 operator * (mat3& a, mat3& b) {
#define ROWCOL(i, j) \
  a.v[i].n[0]*b.v[0][j] + a.v[i].n[1]*b.v[1][j] + a.v[i].n[2]*b.v[2][j]
  return mat3(vec3(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2)),
      vec3(ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2)),
      vec3(ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2)));
#undef ROWCOL
}

mat3 operator * (const mat3& a, const double d)
{ return mat3(a.v[0] * d, a.v[1] * d, a.v[2] * d); }

mat3 operator * (const double d, const mat3& a)
{ return a*d; }

mat3 operator / (const mat3& a, const double d)
{ return mat3(a.v[0] / d, a.v[1] / d, a.v[2] / d); }

int operator == (const mat3& a, const mat3& b)
{ return (a.v[0] == b.v[0]) && (a.v[1] == b.v[1]) && (a.v[2] == b.v[2]); }

int operator != (const mat3& a, const mat3& b)
{ return !(a == b); }

std::ostream& operator << (std::ostream& s, mat3& m)
{ return s << m.v[VX] << '\n' << m.v[VY] << '\n' << m.v[VZ]; }

std::istream& operator >> (std::istream& s, mat3& m) {
  mat3    m_tmp;

  s >> m_tmp[VX] >> m_tmp[VY] >> m_tmp[VZ];
  if (s)
    m = m_tmp;
  return s;
}

void mat3::print( FILE *file, const char* name )
{
  int i, j;

  fprintf( stderr, "%s:\n", name );

  for( i = 0; i < 3; i++ ) {
    fprintf( stderr, "   " );
    for( j = 0; j < 3; j++ ) {
      fprintf( stderr, "%f  ", v[i][j] );
    }
    fprintf( stderr, "\n" );
  }
}

mat4 operator - (const mat4& a)
{ return mat4(-a.v[0], -a.v[1], -a.v[2], -a.v[3]); }

mat4 operator + (const mat4& a, const mat4& b)
{ return mat4(a.v[0] + b.v[0], a.v[1] + b.v[1], a.v[2] + b.v[2],
    a.v[3] + b.v[3]);
}

mat4 operator - (const mat4& a, const mat4& b)
{ return mat4(a.v[0] - b.v[0], a.v[1] - b.v[1], a.v[2] - b.v[2], a.v[3] - b.v[3]); }

mat4 operator * (mat4& a, mat4& b) {
#define ROWCOL(i, j) a.v[i].n[0]*b.v[0][j] + a.v[i].n[1]*b.v[1][j] + \
  a.v[i].n[2]*b.v[2][j] + a.v[i].n[3]*b.v[3][j]
  return mat4(
      vec4(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2), ROWCOL(0,3)),
      vec4(ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2), ROWCOL(1,3)),
      vec4(ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2), ROWCOL(2,3)),
      vec4(ROWCOL(3,0), ROWCOL(3,1), ROWCOL(3,2), ROWCOL(3,3))
      );
}

mat4 operator * (const mat4& a, const double d)
{ return mat4(a.v[0] * d, a.v[1] * d, a.v[2] * d, a.v[3] * d); }

mat4 operator * (const double d, const mat4& a)
{ return a*d; }

mat4 operator / (const mat4& a, const double d)
{ return mat4(a.v[0] / d, a.v[1] / d, a.v[2] / d, a.v[3] / d); }

int operator == (const mat4& a, const mat4& b)
{ return ((a.v[0] == b.v[0]) && (a.v[1] == b.v[1]) && (a.v[2] == b.v[2]) &&
    (a.v[3] == b.v[3])); }

int operator != (const mat4& a, const mat4& b)
{ return !(a == b); }

std::ostream& operator << (std::ostream& s, mat4& m)
{ return s << m.v[VX] << '\n' << m.v[VY] << '\n' << m.v[VZ] << '\n' << m.v[VW]; }

std::istream& operator >> (std::istream& s, mat4& m)
{
  mat4    m_tmp;

  s >> m_tmp[VX] >> m_tmp[VY] >> m_tmp[VZ] >> m_tmp[VW];
  if (s)
    m = m_tmp;
  return s;
}

//===----------------------------------------------------------------------===//
// 2D functions and 3D functions
//===----------------------------------------------------------------------===//

mat3 identity2D(void)
{
  return mat3(vec3(1.0, 0.0, 0.0),
      vec3(0.0, 1.0, 0.0),
      vec3(0.0, 0.0, 1.0));
}

mat3 translation2D(vec2& v)
{
  return mat3(vec3(1.0, 0.0, v[VX]),
      vec3(0.0, 1.0, v[VY]),
      vec3(0.0, 0.0, 1.0));
}

mat3 rotation2D(vec2& Center, const double angleDeg)
{
  double  angleRad = angleDeg * M_PI / 180.0,
          c = cos(angleRad),
          s = sin(angleRad);

  return mat3(vec3(c, -s, Center[VX] * (1.0-c) + Center[VY] * s),
      vec3(s, c, Center[VY] * (1.0-c) - Center[VX] * s),
      vec3(0.0, 0.0, 1.0));
}

mat3 scaling2D(vec2& scaleVector)
{
  return mat3(vec3(scaleVector[VX], 0.0, 0.0),
      vec3(0.0, scaleVector[VY], 0.0),
      vec3(0.0, 0.0, 1.0));
}

mat4 identity3D(void)
{
  return mat4(vec4(1.0, 0.0, 0.0, 0.0),
      vec4(0.0, 1.0, 0.0, 0.0),
      vec4(0.0, 0.0, 1.0, 0.0),
      vec4(0.0, 0.0, 0.0, 1.0));
}

mat4 translation3D(vec3& v)
{
  return mat4(vec4(1.0, 0.0, 0.0, v[VX]),
      vec4(0.0, 1.0, 0.0, v[VY]),
      vec4(0.0, 0.0, 1.0, v[VZ]),
      vec4(0.0, 0.0, 0.0, 1.0));
}

mat4 rotation3D(vec3& Axis, const double angleDeg)
{
  double  angleRad = angleDeg * M_PI / 180.0,
          c = cos(angleRad),
          s = sin(angleRad),
          t = 1.0 - c;

  Axis.normalize();
  return mat4(vec4(t * Axis[VX] * Axis[VX] + c,
        t * Axis[VX] * Axis[VY] - s * Axis[VZ],
        t * Axis[VX] * Axis[VZ] + s * Axis[VY],
        0.0),
      vec4(t * Axis[VX] * Axis[VY] + s * Axis[VZ],
        t * Axis[VY] * Axis[VY] + c,
        t * Axis[VY] * Axis[VZ] - s * Axis[VX],
        0.0),
      vec4(t * Axis[VX] * Axis[VZ] - s * Axis[VY],
        t * Axis[VY] * Axis[VZ] + s * Axis[VX],
        t * Axis[VZ] * Axis[VZ] + c,
        0.0),
      vec4(0.0, 0.0, 0.0, 1.0));
}

mat4 rotation3Drad(vec3& Axis, const double angleRad) {
  double   c = cos(angleRad),
           s = sin(angleRad),
           t = 1.0 - c;

  Axis.normalize();
  return mat4(vec4(t * Axis[VX] * Axis[VX] + c,
        t * Axis[VX] * Axis[VY] - s * Axis[VZ],
        t * Axis[VX] * Axis[VZ] + s * Axis[VY],
        0.0),
      vec4(t * Axis[VX] * Axis[VY] + s * Axis[VZ],
        t * Axis[VY] * Axis[VY] + c,
        t * Axis[VY] * Axis[VZ] - s * Axis[VX],
        0.0),
      vec4(t * Axis[VX] * Axis[VZ] - s * Axis[VY],
        t * Axis[VY] * Axis[VZ] + s * Axis[VX],
        t * Axis[VZ] * Axis[VZ] + c,
        0.0),
      vec4(0.0, 0.0, 0.0, 1.0));
}

mat4 scaling3D(vec3& scaleVector)
{
  return mat4(vec4(scaleVector[VX], 0.0, 0.0, 0.0),
      vec4(0.0, scaleVector[VY], 0.0, 0.0),
      vec4(0.0, 0.0, scaleVector[VZ], 0.0),
      vec4(0.0, 0.0, 0.0, 1.0));
}

mat4 perspective3D(const double d)
{
  return mat4(vec4(1.0, 0.0, 0.0, 0.0),
      vec4(0.0, 1.0, 0.0, 0.0),
      vec4(0.0, 0.0, 1.0, 0.0),
      vec4(0.0, 0.0, 1.0/d, 0.0));
}

} // namespace math
} // namespace LLib

void std::swap(vec2& a, vec2& b)
{
  vec2 tmp(a);
  a = b;
  b = tmp;
}

void std::swap(vec3& a, vec3& b)
{
  vec3 tmp(a);
  a = b;
  b = tmp;
}

void std::swap(vec4& a, vec4& b)
{
  vec4 tmp(a);
  a = b;
  b = tmp;
}

void std::swap(mat3& a, mat3& b)
{
  mat3 tmp(a);
  a = b;
  b = tmp;
}

void swap(mat4& a, mat4& b)
{
  mat4 tmp(a);
  a = b;
  b = tmp;
}

