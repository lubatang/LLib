//===- Vectors.cpp --------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Vectors.h>

using namespace luba;
using namespace std;

//===----------------------------------------------------------------------===//
// vec2D
//===----------------------------------------------------------------------===//
vec2D::vec2D()
 : vec3(0.0, 0.0, 1.0) {
}

vec2D::vec2D(const vec2D& v)
 : vec3(v[0], v[1], v[2]) {
}

vec2D::vec2D(double x, double y)
 : vec3(x, y, 1.0) {
}

vec2D::vec2D(const vec2& v)
  : vec3(v[0], v[1], 1.0) {
}

vec2D& vec2D::operator=(const vec2D& pCopy)
{
  m_N[0] = pCopy.m_N[0];
  m_N[1] = pCopy.m_N[1];
  m_N[2] = pCopy.m_N[2];
  return *this;
}

vec2D& vec2D::operator=(const vec3& pCopy)
{
  m_N[0] = pCopy[0];
  m_N[1] = pCopy[1];
  m_N[2] = pCopy[2];
  return *this;
}

//===----------------------------------------------------------------------===//
// 2D functions
//===----------------------------------------------------------------------===//
/// translate - move 2D point pOrig with offset pOffset
void translate(vec2D& pOrig, const vec2& pOffset)
{
  mat3 T(1.0, 0.0, pOffset[0],
         0.0, 1.0, pOffset[1],
         0.0, 0.0, 1.0        );

  pOrig = T * pOrig;
}

//===----------------------------------------------------------------------===//
// vec3D
//===----------------------------------------------------------------------===//
vec3D::vec3D()
  : vec4(0.0, 0.0, 0.0, 1.0) {
}

vec3D::vec3D(const vec3D& v)
 : vec4(v[0], v[1], v[2], v[3]) {
}

vec3D::vec3D(double x, double y, double z)
 : vec4(x, y, z, 1.0) {
}

vec3D::vec3D(double x, double y, double z, double w)
 : vec4(x, y, z, w) {
}

vec3D::vec3D(const vec3& v)
  : vec4(v[0], v[1], v[2], 1.0) {

}

vec3D::vec3D(const vec3& v, double w)
  : vec4(v[0], v[1], v[2], w) {
}

vec3D::vec3D(float pV[4])
  : vec4(pV[0], pV[1], pV[2], pV[3]) {
}

vec3D& vec3D::operator=(const vec3D& pCopy)
{
  m_N[0] = pCopy.m_N[0];
  m_N[1] = pCopy.m_N[1];
  m_N[2] = pCopy.m_N[2];
  m_N[3] = pCopy.m_N[3];
  return *this;
}

vec3D& vec3D::operator=(const vec4& pCopy)
{
  m_N[0] = pCopy[0];
  m_N[1] = pCopy[1];
  m_N[2] = pCopy[2];
  m_N[3] = pCopy[3];
  return *this;
}

//===----------------------------------------------------------------------===//
// 3D functions
//===----------------------------------------------------------------------===//
void luba::translate(vec3D& pVector, double pX, double pY, double pZ)
{
  mat4 T(1.0, 0.0, 0.0, pX,
         0.0, 1.0, 0.0, pY,
         0.0, 0.0, 1.0, pZ,
         0.0, 0.0, 0.0, 1.0);

  pVector = T * pVector;
}

/// scaling
void luba::scaling(vec3D& pVector, double pX, double pY, double pZ)
{
  mat4 S( pX, 0.0, 0.0, 0.0,
         0.0,  pY, 0.0, 0.0,
         0.0, 0.0,  pZ, 0.0,
         0.0, 0.0, 0.0, 1.0);

  pVector = S * pVector;
}

vec3D luba::CoefProd(const vec3D& pX, const vec3D& pY)
{
  vec3D result(pX);
  result[0] *= pY[0];
  result[1] *= pY[1];
  result[2] *= pY[2];
  result[3] *= pY[3];
  return result;
}

/**
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

**/
