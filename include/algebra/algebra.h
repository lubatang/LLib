//===- algebra.h ----------------------------------------------------------===//
//
// copyright (c), 2012-
// luba tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_ALGEBRA_H
#define LUBA_ALGEBRA_H
#include <algebra/vec2.h>
#include <algebra/vec3.h>
#include <algebra/vec4.h>
#include <algebra/mat3.h>
#include <algebra/mat4.h>

namespace luba {

typedef vec3 vec2D;
typedef vec4 vec3D;

/// translate - move 2D point pOrig with offset pOffset
void translate(vec2D& pOrig, const vec2& pOffset);

} // namespace of luba

#endif

