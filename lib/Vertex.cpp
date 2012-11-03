//===- Vertex.cpp ---------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Vertex.h>
#include <Triangle/Coord.h>
#include <Triangle/Model.h>
#include <Triangle/Color.h>
#include <cassert>

using namespace luba;

Model* Vertex::f_pModel= NULL;

//===----------------------------------------------------------------------===//
// Vertex
//===----------------------------------------------------------------------===//
void Vertex::Initialize(Model& pModel)
{
  f_pModel = &pModel;
}

bool Vertex::isValid()
{
  return (NULL != f_pModel && NULL != f_pModel->getObject());
}

Vertex::Vertex()
  :  m_VertexIdx(0), m_ColorIdx(0), m_NormIdx(0), m_TextureIdx(0) {
}

Vertex::Vertex(size_t pVertex, size_t pColor, size_t pNorm, size_t pText)
  : m_VertexIdx(pVertex),
    m_ColorIdx(pColor),
    m_NormIdx(pNorm),
    m_TextureIdx(pText) {
}
 
void Vertex::getCoord(Coord& pCoord) const
{
  assert(isValid() &&
         "Vertex::Initialize(Model& pModel) should be called before calling "
         "Vertex::getCoord()");

  pCoord.x = f_pModel->getObject()->vertices[m_VertexIdx*3];
  pCoord.y = f_pModel->getObject()->vertices[m_VertexIdx*3 + 1];
  pCoord.z = f_pModel->getObject()->vertices[m_VertexIdx*3 + 2];
}

/// getColor - get the RGB color of the vertex
/// Original data is in the [-1, 1]. Linear interpolation to [0, 255]
void Vertex::getColor(Color& pColor) const
{
  assert(isValid() &&
         "Vertex::Initialize(Model& pModel) should be called before calling "
         "Vertex::getColor()");

  pColor.r = f_pModel->getObject()->colors[m_VertexIdx*3]*128 + 127;
  pColor.g = f_pModel->getObject()->colors[m_VertexIdx*3 + 1]*128 + 127;
  pColor.b = f_pModel->getObject()->colors[m_VertexIdx*3 + 2]*128 + 127;
}

