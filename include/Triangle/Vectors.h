//===- Vectors.h ----------------------------------------------------------===//
//
// copyright (c), 2012-
// luba tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_VECTOR_ALGEBRA_H
#define LUBA_VECTOR_ALGEBRA_H
#include <algebra/vec2.h>
#include <algebra/vec3.h>
#include <algebra/vec4.h>
#include <algebra/mat3.h>
#include <algebra/mat4.h>

namespace luba {

class vec2D : public vec3
{
public:
  vec2D();
  vec2D(const vec2D& v);
  explicit vec2D(double x, double y);
  explicit vec2D(const vec2& v);

  vec2D& operator=(const vec3& pCopy);
  vec2D& operator=(const vec2D& pCopy);
};

class vec3D : public vec4
{
public:
  vec3D();
  vec3D(const vec3D& v);

  explicit vec3D(double x, double y, double z);
  explicit vec3D(const vec3& v);

  vec3D& operator=(const vec4& pCopy);
  vec3D& operator=(const vec3D& pCopy);
};

//===----------------------------------------------------------------------===//
// 2D functions
//===----------------------------------------------------------------------===//
void translate(vec2D& pOrig, const vec2& pOffset);

//===----------------------------------------------------------------------===//
// 3D functions
//===----------------------------------------------------------------------===//
void translate(vec3D& pVector, double pX, double pY, double pZ);

void scaling(vec3D& pVector, double pX, double pY, double pZ);

} // namespace of luba

#endif

