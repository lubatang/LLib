//===- mat4.cpp -----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <algebra/algebra.h>

using namespace LLib::Math;

//===----------------------------------------------------------------------===//
// mat4
//===----------------------------------------------------------------------===//
mat4::mat4(void) { *this = identity3D();}

mat4::mat4(const vec4& v0, const vec4& v1, const vec4& v2, const vec4& v3)
{ v[0] = v0; v[1] = v1; v[2] = v2; v[3] = v3; }

mat4::mat4(const double d)
{ v[0] = v[1] = v[2] = v[3] = vec4(d); }

mat4::mat4(const mat4& m)
{ v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2]; v[3] = m.v[3]; }

mat4::mat4(const double a00, const double a01, const double a02, const double a03,
    const double a10, const double a11, const double a12, const double a13,
    const double a20, const double a21, const double a22, const double a23,
    const double a30, const double a31, const double a32, const double a33 )
{
  v[0][0] = a00;  v[0][1] = a01;  v[0][2] = a02;  v[0][3] = a03;
  v[1][0] = a10;  v[1][1] = a11;  v[1][2] = a12;  v[1][3] = a13;
  v[2][0] = a20;  v[2][1] = a21;  v[2][2] = a22;  v[2][3] = a23;
  v[3][0] = a30;  v[3][1] = a31;  v[3][2] = a32;  v[3][3] = a33;
}

// ASSIGNMENT OPERATORS

mat4& mat4::operator = ( const mat4& m )
{ v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2]; v[3] = m.v[3];
  return *this; }

mat4& mat4::operator += ( const mat4& m )
{ v[0] += m.v[0]; v[1] += m.v[1]; v[2] += m.v[2]; v[3] += m.v[3];
  return *this; }

mat4& mat4::operator -= ( const mat4& m )
{ v[0] -= m.v[0]; v[1] -= m.v[1]; v[2] -= m.v[2]; v[3] -= m.v[3];
  return *this; }

mat4& mat4::operator *= ( const double d )
{ v[0] *= d; v[1] *= d; v[2] *= d; v[3] *= d; return *this; }

mat4& mat4::operator /= ( const double d )
{ v[0] /= d; v[1] /= d; v[2] /= d; v[3] /= d; return *this; }

vec4& mat4::operator [] ( int i) {
  if (i < VX || i > VW)
    //VEC_ERROR("mat4 [] operator: illegal access; index = " << i << '\n')
    VEC_ERROR("mat4 [] operator: illegal access" );
  return v[i];
}

// SPECIAL FUNCTIONS;

mat4 mat4::transpose(void) {
  return mat4(vec4(v[0][0], v[1][0], v[2][0], v[3][0]),
      vec4(v[0][1], v[1][1], v[2][1], v[3][1]),
      vec4(v[0][2], v[1][2], v[2][2], v[3][2]),
      vec4(v[0][3], v[1][3], v[2][3], v[3][3]));
}

mat4 mat4::inverse(void)   // Gauss-Jordan elimination with partial pivoting
{
  mat4 a(*this),      // As a evolves from original mat into identity
       b(identity3D());   // b evolves from identity into inverse(a)
  int i, j, i1;

  // Loop over cols of a from left to right, eliminating above and below diag
  for (j=0; j<4; j++) {   // Find largest pivot in column j among rows j..3
    i1 = j;        // Row with largest pivot candidate
    for (i=j+1; i<4; i++)
      if (fabs(a.v[i].n[j]) > fabs(a.v[i1].n[j]))
        i1 = i;

    // Swap rows i1 and j in a and b to put pivot on diagonal
    std::swap(a.v[i1], a.v[j]);
    std::swap(b.v[i1], b.v[j]);

    // Scale row j to have a unit diagonal
    if (a.v[j].n[j]==0.)
      VEC_ERROR("mat4::inverse: singular matrix; can't invert\n");
    b.v[j] /= a.v[j].n[j];
    a.v[j] /= a.v[j].n[j];

    // Eliminate off-diagonal elems in col j of a, doing identical ops to b
    for (i=0; i<4; i++)
      if (i!=j) {
        b.v[i] -= a.v[i].n[j]*b.v[j];
        a.v[i] -= a.v[i].n[j]*a.v[j];
      }
  }
  return b;
}

mat4& mat4::apply(V_FCT_PTR fct)
{ v[VX].apply(fct); v[VY].apply(fct); v[VZ].apply(fct); v[VW].apply(fct);
  return *this; }


void mat4::print( FILE *file, const char* name )
{
  int i, j;

  fprintf( stderr, "%s:\n", name );

  for( i = 0; i < 4; i++ ) {
    fprintf( stderr, "   " );
    for( j = 0; j < 4; j++ ) {
      fprintf( stderr, "%f  ", v[i][j] );
    }
    fprintf( stderr, "\n" );
  }
}

void mat4::swap_rows( int i, int j )
{
  vec4 t;

  t = v[i];
  v[i] = v[j];
  v[j] = t;
}

void mat4::swap_cols( int i, int j )
{
  double t;
  int k;

  for(k=0; k<4; k++ ) {
    t       = v[k][i];
    v[k][i] = v[k][j];
    v[k][j] = t;
  }
}


