//===- Vertex.h -----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_VERTEX_H
#define LUBA_VERTEX_H
#include <cstddef>

namespace luba {

class Model;
class Color;

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

class Vertex
{
public:
  static void Initialize(Model& pModel);

  static bool isValid();

public:
  Vertex();

  Vertex(size_t pVertex, size_t pColor, size_t m_Norm, size_t m_Text);

  void getCoord(Coord& pCoord) const;

  void getColor(Color& pColor) const;

private:
  static Model* f_pModel;

  size_t m_VertexIdx;
  size_t m_ColorIdx;
  size_t m_NormIdx;
  size_t m_TextureIdx;
};

} // namespace of luba

#endif
