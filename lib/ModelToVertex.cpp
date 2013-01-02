//===- ModelToVertex.cpp --------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/ModelToVertex.h>
#include <Triangle/Model.h>
#include <Triangle/Color.h>

using namespace luba;

//===----------------------------------------------------------------------===//
// Vertex
//===----------------------------------------------------------------------===//
ModelToVertex::ModelToVertex(Model& pModel)
  : m_Model(pModel),
    m_VertexIdx(0), m_ColorIdx(0), m_NormIdx(0), m_TextureIdx(0) {
}

void ModelToVertex::setConverter(size_t pVertex,
                                 size_t pColor,
                                 size_t pNorm,
                                 size_t pText)
{
  m_VertexIdx = pVertex;
  m_ColorIdx = pColor;
  m_NormIdx = pNorm;
  m_TextureIdx = pText;
}
 
void ModelToVertex::getVertex(Vertex& pVertex) const
{
  getCoord(pVertex.coord());
  getColor(pVertex.color());
  //getNorm(pVertex.norm());
}

void ModelToVertex::getCoord(Coord& pCoord) const
{
  pCoord[0] = m_Model.getObject()->vertices[m_VertexIdx*3];
  pCoord[1] = m_Model.getObject()->vertices[m_VertexIdx*3 + 1];
  pCoord[2] = m_Model.getObject()->vertices[m_VertexIdx*3 + 2];
  pCoord[3] = 1.0;
}

/// getColor - get the RGB color of the vertex
/// Original data is in the [-1, 1]. Linear interpolation to [0, 255]
void ModelToVertex::getColor(Color& pColor) const
{
  pColor.r = m_Model.getObject()->colors[m_VertexIdx*3];
  pColor.g = m_Model.getObject()->colors[m_VertexIdx*3 + 1];
  pColor.b = m_Model.getObject()->colors[m_VertexIdx*3 + 2];
}

void ModelToVertex::getNorm(vec3& pNorm) const
{
  pNorm[0] = m_Model.getObject()->normals[m_NormIdx*3];
  pNorm[1] = m_Model.getObject()->normals[m_NormIdx*3 + 1];
  pNorm[2] = m_Model.getObject()->normals[m_NormIdx*3 + 2];
}

