/**************************************************************************
  
  algebra3.cpp, algebra3.h -  C++ Vector and Matrix Algebra routines         

  There are three vector classes and two matrix classes: vec2, vec3,
  vec4, mat3, and mat4.

  All the standard arithmetic operations are defined, with '*'
  for dot product of two vectors and multiplication of two matrices,
  and '^' for cross product of two vectors.

  Additional functions include length(), normalize(), homogenize for
  vectors, and print(), set(), apply() for all classes.

  There is a function transpose() for matrices, but note that it 
  does not actually change the matrix, 

  When multiplied with a matrix, a vector is treated as a row vector
  if it precedes the matrix (v*M), and as a column vector if it
  follows the matrix (M*v).

  Matrices are stored in row-major form.

  A vector of one dimension (2d, 3d, or 4d) can be cast to a vector
  of a higher or lower dimension.  If casting to a higher dimension,
  the new component is set by default to 1.0, unless a value is
  specified:
     vec3 a(1.0, 2.0, 3.0 );
     vec4 b( a, 4.0 );       // now b == {1.0, 2.0, 3.0, 4.0};
  When casting to a lower dimension, the vector is homogenized in
  the lower dimension.  E.g., if a 4d {X,Y,Z,W} is cast to 3d, the
  resulting vector is {X/W, Y/W, Z/W}.  It is up to the user to 
  insure the fourth component is not zero before casting.

  There are also the following function for building matrices:
     identity2D(), translation2D(), rotation2D(),
     scaling2D(),  identity3D(),    translation3D(),
     rotation3D(), rotation3Drad(),  scaling3D(),
     perspective3D()

  NOTE: When compiling for Windows, include this file first, to avoid
        certain name conflicts
 
  ---------------------------------------------------------------------
  
  Author: Jean-Francois DOUEg          
  Revised: Paul Rademacher                                      
  Version 3.2 - Feb 1998
                
**************************************************************************/
#ifndef _ALGEBRA3_H_
#define _ALGEBRA3_H_
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iosfwd>

namespace LLib
{
  namespace Math
  {


    // this line defines a new type: pointer to a function which returns a
    // double and takes as argument a double
    typedef double (*V_FCT_PTR)(double);

    // min-max macros
    #ifndef MIN
    #define MIN(A,B) ((A) < (B) ? (A) : (B))
    #define MAX(A,B) ((A) > (B) ? (A) : (B))
    #endif

    //#include <stream.h>
    // error handling macro
    //#define VEC_ERROR(E) { cerr << E; exit(1); }
    /*#define << 
    #define >>*/

    #ifdef VEC_ERROR_FATAL
    #ifndef VEC_ERROR
      #define VEC_ERROR(E) { printf( "VERROR %s\n", E ); exit(1); }
    #endif
    #else
    #ifndef VEC_ERROR
      #define VEC_ERROR(E) { printf( "VERROR %s\n", E ); }
    #endif
    #endif

    #define EPSILON 1e-14

    class vec2;
    class vec3;
    class vec4;
    class mat3;
    class mat4;

    /*#ifndef X
    enum {X,Y,Z,W};
    #endif
    */

    /*#ifndef R
    enum {R,G,B,ALPHA};
    #endif
    */

    #ifndef M_PI
    #define M_PI 3.14159265358979323846
    #endif


    enum {VX, VY, VZ, VW};        // axes
    enum {PA, PB, PC, PD};        // planes
    enum {RED, GREEN, BLUE, ALPHA};      // colors
    enum {KA, KD, KS, ES};        // phong coefficients

   /****************************************************************
    *  2D Vector
    ****************************************************************/

    class vec2
    {
    protected:
      double n[2];

    public:
      vec2(void);
      vec2(const double x, const double y);
      vec2(const double d);
      vec2(const vec2& v);      // copy constructor
      vec2(const vec3& v);      // cast v3 to v2
      vec2(const vec3& v, int dropAxis);  // cast v3 to v2

      // Assignment operators

      vec2& operator  = ( const vec2& v );  // assignment of a vec2
      vec2& operator += ( const vec2& v );  // incrementation by a vec2
      vec2& operator -= ( const vec2& v );  // decrementation by a vec2
      vec2& operator *= ( const double d );  // multiplication by a constant
      vec2& operator /= ( const double d );  // division by a constant
      double& operator [] ( int i);    // indexing

    // special functions

    double length(void);      // length of a vec2
    double length2(void);      // squared length of a vec2
    vec2& normalize(void);      // normalize a vec2
    vec2& apply(V_FCT_PTR fct);    // apply a func. to each component
    void  set( double x, double y );  // set vector

    // friends

    friend vec2 operator - (const vec2& v);          // -v1
    friend vec2 operator + (const vec2& a, const vec2& b);      // v1 + v2
    friend vec2 operator - (const vec2& a, const vec2& b);      // v1 - v2
    friend vec2 operator * (const vec2& a, const double d);      // v1 * 3.0
    friend vec2 operator * (const double d, const vec2& a);      // 3.0 * v1
    friend vec2 operator * (const mat3& a, const vec2& v);      // M . v
    friend vec2 operator * (const vec2& v, mat3& a);      // v . M
    friend double operator * (const vec2& a, const vec2& b);    // dot product
    friend vec2 operator / (const vec2& a, const double d);      // v1 / 3.0
    friend vec3 operator ^ (const vec2& a, const vec2& b);      // cross product
    friend int operator == (const vec2& a, const vec2& b);      // v1 == v2 ?
    friend int operator != (const vec2& a, const vec2& b);      // v1 != v2 ?
    friend std::ostream& operator << (std::ostream& s, vec2& v);      // output to stream
    friend std::istream& operator >> (std::istream& s, vec2& v);      // input from strm.
    friend void swap(vec2& a, vec2& b);          // swap v1 & v2
    //friend vec2 min(const vec2& a, const vec2& b);        // min(v1, v2)
    //friend vec2 max(const vec2& a, const vec2& b);        // max(v1, v2)
    friend vec2 prod(const vec2& a, const vec2& b);        // term by term *

    // necessary friend declarations

    friend class vec3;
    };

   /***************************************************************
    *          3D Vector
    ****************************************************************/
    class vec3
    {
    public:
      double n[3];


    public:
    // Constructors

    vec3(void);
    vec3(const double x, const double y, const double z);
    vec3(const double d);
    vec3(const vec3& v);          // copy constructor
    vec3(const vec2& v);          // cast v2 to v3
    vec3(const vec2& v, double d);        // cast v2 to v3
    vec3(const vec4& v);          // cast v4 to v3
    vec3(const vec4& v, int dropAxis);      // cast v4 to v3

    // Assignment operators

    vec3& operator  = ( const vec3& v );      // assignment of a vec3
    vec3& operator += ( const vec3& v );      // incrementation by a vec3
    vec3& operator -= ( const vec3& v );      // decrementation by a vec3
    vec3& operator *= ( const double d );      // multiplication by a constant
    vec3& operator /= ( const double d );      // division by a constant
    double& operator [] ( int i);        // indexing

    // special functions

    double length(void);          // length of a vec3
    double length2(void);          // squared length of a vec3
    vec3& normalize(void);          // normalize a vec3
    vec3& homogenize(void);          // homogenize (div by Z)
    vec3& apply(V_FCT_PTR fct);        // apply a func. to each component
    void  set( double x, double y, double z );     // set vector
    void  print( FILE *file, const char *name );      // print vector to a file

    // friends

    friend vec3 operator - (const vec3& v);          // -v1
    friend vec3 operator + (const vec3& a, const vec3& b);      // v1 + v2
    friend vec3 operator - (const vec3& a, const vec3& b);      // v1 - v2
    friend vec3 operator * (const vec3& a, const double d);      // v1 * 3.0
    friend vec3 operator * (const double d, const vec3& a);      // 3.0 * v1
    friend vec3 operator * (const mat4& a, const vec3& v);      // M . v
    friend vec3 operator * (const vec3& v, mat4& a);      // v . M
    friend double operator * (const vec3& a, const vec3& b);    // dot product
    friend vec3 operator / (const vec3& a, const double d);      // v1 / 3.0
    friend vec3 operator ^ (const vec3& a, const vec3& b);      // cross product
    friend int operator == (const vec3& a, const vec3& b);      // v1 == v2 ?
    friend int operator != (const vec3& a, const vec3& b);      // v1 != v2 ?
    friend std::ostream& operator << (std::ostream& s, vec3& v);      // output to stream
    friend std::istream& operator >> (std::istream& s, vec3& v);      // input from strm.
    friend void swap(vec3& a, vec3& b);              // swap v1 & v2
    //friend vec3 min(const vec3& a, const vec3& b);        // min(v1, v2)
    //friend vec3 max(const vec3& a, const vec3& b);        // max(v1, v2)
    friend vec3 prod(const vec3& a, const vec3& b);       // term by term *

    // necessary friend declarations

    friend class vec2;
    friend class vec4;
    friend class mat3;
    friend vec2 operator * (const mat3& a, const vec2& v);      // linear transform
    friend vec3 operator * (const mat3& a, const vec3& v);      // linear transform
    friend mat3 operator * (mat3& a, mat3& b);        // matrix 3 product

    };

    /****************************************************************
    *                *
    *          4D Vector        *
    *                *
    ****************************************************************/

    class vec4
    {
    protected:
        double n[4];
    public:

    // Constructors

    vec4(void);
    vec4(const double x, const double y, const double z, const double w);
    vec4(const double d);
    vec4(const vec4& v);          // copy constructor
    vec4(const vec3& v);          // cast vec3 to vec4
    vec4(const vec3& v, const double d);      // cast vec3 to vec4

    // Assignment operators

    vec4& operator  = ( const vec4& v );      // assignment of a vec4
    vec4& operator += ( const vec4& v );      // incrementation by a vec4
    vec4& operator -= ( const vec4& v );      // decrementation by a vec4
    vec4& operator *= ( const double d );      // multiplication by a constant
    vec4& operator /= ( const double d );      // division by a constant
    double& operator [] ( int i);        // indexing

    // special functions

    double length(void);          // length of a vec4
    double length2(void);          // squared length of a vec4
    vec4& normalize(void);          // normalize a vec4
    vec4& apply(V_FCT_PTR fct);        // apply a func. to each component
    vec4& homogenize(void);
    void  print(FILE *file, const char *name );      // print vector to a file
    void  set( double x, double y, double z, double a );            

    // friends

    friend vec4 operator - (const vec4& v);          // -v1
    friend vec4 operator + (const vec4& a, const vec4& b);      // v1 + v2
    friend vec4 operator - (const vec4& a, const vec4& b);      // v1 - v2
    friend vec4 operator * (const vec4& a, const double d);      // v1 * 3.0
    friend vec4 operator * (const double d, const vec4& a);      // 3.0 * v1
    friend vec4 operator * (const mat4& a, const vec4& v);      // M . v
    friend vec4 operator * (const vec4& v, mat4& a);      // v . M
    friend double operator * (const vec4& a, const vec4& b);    // dot product
    friend vec4 operator / (const vec4& a, const double d);      // v1 / 3.0
    friend int operator == (const vec4& a, const vec4& b);      // v1 == v2 ?
    friend int operator != (const vec4& a, const vec4& b);      // v1 != v2 ?
    friend std::ostream& operator << (std::ostream& s, vec4& v);      // output to stream
    friend std::istream& operator >> (std::istream& s, vec4& v);      // input from strm.
    friend void swap(vec4& a, vec4& b);          // swap v1 & v2
    //friend vec4 min(const vec4& a, const vec4& b);        // min(v1, v2)
    //friend vec4 max(const vec4& a, const vec4& b);        // max(v1, v2)
    friend vec4 prod(const vec4& a, const vec4& b);        // term by term *

    // necessary friend declarations

    friend class vec3;
    friend class mat4;
    friend vec3 operator * (const mat4& a, const vec3& v);      // linear transform
    friend mat4 operator * (mat4& a, mat4& b);        // matrix 4 product
    };

    /****************************************************************
    *                *
    *         3x3 Matrix        *
    *                *
    ****************************************************************/

    class mat3
    {
    protected:
    public:
    vec3 v[3];



    // Constructors

    mat3(void);
    mat3(const vec3& v0, const vec3& v1, const vec3& v2);
    mat3(const double d);
    mat3(const mat3& m);

    // Assignment operators

    mat3& operator  = ( const mat3& m );      // assignment of a mat3
    mat3& operator += ( const mat3& m );      // incrementation by a mat3
    mat3& operator -= ( const mat3& m );      // decrementation by a mat3
    mat3& operator *= ( const double d );      // multiplication by a constant
    mat3& operator /= ( const double d );      // division by a constant
    vec3& operator [] ( int i);        // indexing

    // special functions

    mat3 transpose(void);          // transpose
    mat3 inverse(void);          // inverse
    mat3& apply(V_FCT_PTR fct);        // apply a func. to each element
    void print( FILE *file, const char *name );       // print matrix to a file
    void set(const vec3& v0, const vec3& v1, const vec3& v2);


    // friends

    friend mat3 operator - (const mat3& a);          // -m1
    friend mat3 operator + (const mat3& a, const mat3& b);      // m1 + m2
    friend mat3 operator - (const mat3& a, const mat3& b);      // m1 - m2
    friend mat3 operator * (mat3& a, mat3& b);        // m1 * m2
    friend mat3 operator * (const mat3& a, const double d);      // m1 * 3.0
    friend mat3 operator * (const double d, const mat3& a);      // 3.0 * m1
    friend mat3 operator / (const mat3& a, const double d);      // m1 / 3.0
    friend int operator == (const mat3& a, const mat3& b);      // m1 == m2 ?
    friend int operator != (const mat3& a, const mat3& b);      // m1 != m2 ?
    friend std::ostream& operator << (std::ostream& s, mat3& m);      // output to stream
    friend std::istream& operator >> (std::istream& s, mat3& m);      // input from strm.
    friend void swap(mat3& a, mat3& b);          // swap m1 & m2

    // necessary friend declarations

    friend vec3 operator * (const mat3& a, const vec3& v);      // linear transform
    friend vec2 operator * (const mat3& a, const vec2& v);      // linear transform
    };

   /****************************************************************
    *         4x4 Matrix
    ****************************************************************/
    class mat4
    {
    public:
      vec4 v[4];

    public:
      mat4(void);
      mat4(const vec4& v0, const vec4& v1, const vec4& v2, const vec4& v3);
      mat4(const double d);
      mat4(const mat4& m);
      mat4(const double a00, const double a01, const double a02, const double a03,
           const double a10, const double a11, const double a12, const double a13,
           const double a20, const double a21, const double a22, const double a23,
           const double a30, const double a31, const double a32, const double a33 );


    // Assignment operators

    mat4& operator  = ( const mat4& m );      // assignment of a mat4
    mat4& operator += ( const mat4& m );      // incrementation by a mat4
    mat4& operator -= ( const mat4& m );      // decrementation by a mat4
    mat4& operator *= ( const double d );      // multiplication by a constant
    mat4& operator /= ( const double d );      // division by a constant
    vec4& operator [] ( int i);        // indexing

    // special functions

    mat4 transpose(void);          // transpose
    mat4 inverse(void);            // inverse
    mat4& apply(V_FCT_PTR fct);        // apply a func. to each element
    void print(FILE *file, const char *name );       // print matrix to a file
    void swap_rows( int i, int j );             // swap rows i and j
    void swap_cols( int i, int j );             // swap cols i and j

    // friends

    friend mat4 operator - (const mat4& a);          // -m1
    friend mat4 operator + (const mat4& a, const mat4& b);      // m1 + m2
    friend mat4 operator - (const mat4& a, const mat4& b);      // m1 - m2
    friend mat4 operator * (mat4& a, mat4& b);        // m1 * m2
    friend mat4 operator * (const mat4& a, const double d);      // m1 * 4.0
    friend mat4 operator * (const double d, const mat4& a);      // 4.0 * m1
    friend mat4 operator / (const mat4& a, const double d);      // m1 / 3.0
    friend int operator == (const mat4& a, const mat4& b);      // m1 == m2 ?
    friend int operator != (const mat4& a, const mat4& b);      // m1 != m2 ?
    friend std::ostream& operator << (std::ostream& s, mat4& m);      // output to stream
    friend std::istream& operator >> (std::istream& s, mat4& m);      // input from strm.
    friend void swap(mat4& a, mat4& b);          // swap m1 & m2

    // necessary friend declarations

    friend vec4 operator * (const mat4& a, const vec4& v);      // linear transform
    //friend vec4 operator * (const vec4& v, const mat4& a);      // linear transform
    friend vec3 operator * (const mat4& a, const vec3& v);      // linear transform
    friend vec3 operator * (const vec3& v, const mat4& a);      // linear transform
    };

   /****************************************************************
    *         2D functions and 3D functions
    ****************************************************************/
    mat3 identity2D(void);
    mat3 translation2D(vec2& v);
    mat3 rotation2D(vec2& Center, const double angleDeg);
    mat3 scaling2D(vec2& scaleVector);
    mat4 identity3D(void);
    mat4 translation3D(vec3& v);
    mat4 rotation3D(vec3& Axis, const double angleDeg);
    mat4 rotation3Drad(vec3& Axis, const double angleRad);
    mat4 scaling3D(vec3& scaleVector);
    mat4 perspective3D(const double d);


    vec3 operator * (const vec3& v, mat3& a);
    vec2 operator * (const vec2& v, mat3& a);
    vec3 operator * (const vec3& v, mat4& a);
    vec4 operator * (const vec4& v, mat4& a);
  };
};

#endif
