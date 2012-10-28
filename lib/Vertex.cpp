//===- Vertex.cpp ---------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Vertex.h>

using namespace luba;

//===----------------------------------------------------------------------===//
// Vertex
//===----------------------------------------------------------------------===//
Vertex::Vertex(Model::Object& pObject)
  : m_Object(pObject),
    m_VertexIdx(0), m_ColorIdx(0), m_NormIdx(0), m_TextureIdx(0) {
}

Vertex::Vertex(Model::Object& pObject,
               size_t pVertex, size_t pColor, size_t pNorm, size_t pText)
  : m_Object(pObject),
    m_VertexIdx(pVertex),
    m_ColorIdx(pColor),
    m_NormIdx(pNorm),
    m_TextureIdx(pText) {
}
 
void Vertex::getCoord(Coord& pCoord) const
{
  pCoord.x = m_Object.vertices[m_VertexIdx*3];
  pCoord.y = m_Object.vertices[m_VertexIdx*3 + 1];
  pCoord.z = m_Object.vertices[m_VertexIdx*3 + 2];
}

void Vertex::getColor(Color& pColor) const
{
  pColor.r = m_Object.colors[m_VertexIdx*3]*128 + 255;
  pColor.g = m_Object.colors[m_VertexIdx*3 + 1]*128 + 255;
  pColor.b = m_Object.colors[m_VertexIdx*3 + 2]*128 + 255;
}

