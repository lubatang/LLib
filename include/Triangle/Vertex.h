//===- Vertex.h -----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_VERTEX_H
#define LUBA_VERTEX_H
#include <Triangle/Model.h>
#include <Triangle/Color.h>

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

class Vertex
{
public:
  Vertex(Model::Object& pObject);

  Vertex(Model::Object& pObject, size_t pVertex, size_t pColor, size_t m_Norm, size_t m_Text);

  void getCoord(Coord& pCoord) const;

  void getColor(Color& pColor) const;

private:
  Model::Object& m_Object;

  size_t m_VertexIdx;
  size_t m_ColorIdx;
  size_t m_NormIdx;
  size_t m_TextureIdx;
};

} // namespace of luba

#endif

