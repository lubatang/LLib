//===- ModelToVertex.h ----------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_MODEL_VERTEX_H
#define LUBA_MODEL_VERTEX_H
#include <cstddef>

#include <Triangle/Vertex.h>

namespace luba {

class Model;
class Color;

class ModelToVertex
{
public:
  ModelToVertex(Model& pModel);

  void setConverter(size_t pVertex, size_t pColor, size_t m_Norm, size_t m_Text);

  void getVertex(Vertex& pVertex) const;

  void getCoord(Coord& pCoord) const;

  void getColor(Color& pColor) const;

private:
  Model& m_Model;

  size_t m_VertexIdx;
  size_t m_ColorIdx;
  size_t m_NormIdx;
  size_t m_TextureIdx;
};

} // namespace of luba

#endif

