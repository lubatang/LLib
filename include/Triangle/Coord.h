//===- Coord.h ------------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_COORD_H
#define LUBA_COORD_H
#include <algorithm>

namespace luba {

class Coord
{
public:
  float x;
  float y;
  float z;

public:
  Coord() : x(0.0), y(0.0), z(0.0) {}
  Coord(float pX, float pY, float pZ) : x(pX), y(pY), z(pZ) {}

};

} // namespace luba

namespace std {

template<>
inline void swap(luba::Coord& pA, luba::Coord& pB) {
  std::swap(pA.x, pB.x);
  std::swap(pA.y, pB.y);
  std::swap(pA.z, pB.z);
}

} // namespace std

#endif

