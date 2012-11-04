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
};

} // namespace of luba

#endif

