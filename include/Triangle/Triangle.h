//===- Triangle.h ---------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_TRIANGLE_H
#define LUBA_TRIANGLE_H
#include <algebra/vec3.h>

namespace luba {

class Vertex;

class Triangle
{
public:
  Triangle(const Vertex& pV1, const Vertex& pV2, const Vertex& pV3);

  const Vertex& v1() const { return *m_pV1; }
  const Vertex& v2() const { return *m_pV2; }
  const Vertex& v3() const { return *m_pV3; }

  const vec3& norm() const { return m_FacetNorm; }
  vec3&       norm()       { return m_FacetNorm; }
  Triangle& setNorm(double pX, double pY, double pZ);

private:
  const Vertex* m_pV1;
  const Vertex* m_pV2;
  const Vertex* m_pV3;

  vec3 m_FacetNorm;
};

} // namespace of luba

#endif

