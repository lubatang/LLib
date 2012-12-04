//===- mat3.cpp -----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <algebra/algebra.h>

using namespace LLib::Math;

//===----------------------------------------------------------------------===//
// mat3
//===----------------------------------------------------------------------===//
mat3::mat3(void)
{
  *this = identity2D();
}

mat3::mat3(const vec3& v0, const vec3& v1, const vec3& v2)
{ this->set( v0, v1, v2 ); };

mat3::mat3(const double d)
{ v[0] = v[1] = v[2] = vec3(d); }

mat3::mat3(const mat3& m)
{ v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2]; }

mat3& mat3::operator = ( const mat3& m )
{ v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2]; return *this; }

mat3& mat3::operator += ( const mat3& m )
{ v[0] += m.v[0]; v[1] += m.v[1]; v[2] += m.v[2]; return *this; }

mat3& mat3::operator -= ( const mat3& m )
{ v[0] -= m.v[0]; v[1] -= m.v[1]; v[2] -= m.v[2]; return *this; }

mat3& mat3::operator *= ( const double d )
{ v[0] *= d; v[1] *= d; v[2] *= d; return *this; }

mat3& mat3::operator /= ( const double d )
{ v[0] /= d; v[1] /= d; v[2] /= d; return *this; }

vec3& mat3::operator [] ( int i) {
  if (i < VX || i > VZ)
    //VEC_ERROR("mat3 [] operator: illegal access; index = " << i << '\n')
    VEC_ERROR("mat3 [] operator: illegal access" );
  return v[i];
}

void mat3::set( const vec3& v0, const vec3& v1, const vec3& v2 ) {
  v[0] = v0; v[1] = v1; v[2] = v2; 
}

// SPECIAL FUNCTIONS

mat3 mat3::transpose(void) {
  return mat3(vec3(v[0][0], v[1][0], v[2][0]),
      vec3(v[0][1], v[1][1], v[2][1]),
      vec3(v[0][2], v[1][2], v[2][2]));
}

mat3 mat3::inverse(void)      // Gauss-Jordan elimination with partial pivoting
{
  mat3 a(*this),      // As a evolves from original mat into identity
       b(identity2D());   // b evolves from identity into inverse(a)
  int   i, j, i1;

  // Loop over cols of a from left to right, eliminating above and below diag
  for (j=0; j<3; j++) {   // Find largest pivot in column j among rows j..2
    i1 = j;        // Row with largest pivot candidate
    for (i=j+1; i<3; i++)
      if (fabs(a.v[i].n[j]) > fabs(a.v[i1].n[j]))
        i1 = i;

    // Swap rows i1 and j in a and b to put pivot on diagonal
    std::swap(a.v[i1], a.v[j]);
    std::swap(b.v[i1], b.v[j]);

    // Scale row j to have a unit diagonal
    if (a.v[j].n[j]==0.)
      VEC_ERROR("mat3::inverse: singular matrix; can't invert\n");
    b.v[j] /= a.v[j].n[j];
    a.v[j] /= a.v[j].n[j];

    // Eliminate off-diagonal elems in col j of a, doing identical ops to b
    for (i=0; i<3; i++)
      if (i!=j) {
        b.v[i] -= a.v[i].n[j]*b.v[j];
        a.v[i] -= a.v[i].n[j]*a.v[j];
      }
  }
  return b;
}

mat3& mat3::apply(V_FCT_PTR fct) {
  v[VX].apply(fct);
  v[VY].apply(fct);
  v[VZ].apply(fct);
  return *this;
}

