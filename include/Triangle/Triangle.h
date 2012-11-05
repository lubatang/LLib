//===- Triangle.h ---------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_TRIANGLE_H
#define LUBA_TRIANGLE_H

namespace luba {

class Vertex;

class Triangle
{
public:
  Triangle(const Vertex& pV1, const Vertex& pV2, const Vertex& pV3);

  const Vertex& v1() const { return *m_pV1; }
  const Vertex& v2() const { return *m_pV2; }
  const Vertex& v3() const { return *m_pV3; }

private:
  const Vertex* m_pV1;
  const Vertex* m_pV2;
  const Vertex* m_pV3;
};

} // namespace of luba

#endif

