//===- Coord.h ------------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_COORD_H
#define LUBA_COORD_H

namespace luba {

class Coord
{
public:
  double x;
  double y;
  double z;

public:
  Coord() : x(0.0), y(0.0), z(0.0) {}
  Coord(double pX, double pY, double pZ) : x(pX), y(pY), z(pZ) {}

};

} // namespace luba

#endif

