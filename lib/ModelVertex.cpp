//===- ModelVertex.cpp ----------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/ModelVertex.h>
#include <Triangle/Model.h>
#include <Triangle/Color.h>
#include <cassert>

using namespace luba;

Model* ModelVertex::f_pModel= NULL;

//===----------------------------------------------------------------------===//
// Vertex
//===----------------------------------------------------------------------===//
void ModelVertex::Initialize(Model& pModel)
{
  f_pModel = &pModel;
}

bool ModelVertex::isValid()
{
  return (NULL != f_pModel && NULL != f_pModel->getObject());
}

ModelVertex::ModelVertex()
  :  m_VertexIdx(0), m_ColorIdx(0), m_NormIdx(0), m_TextureIdx(0) {
}

ModelVertex::ModelVertex(size_t pVertex, size_t pColor, size_t pNorm, size_t pText)
  : m_VertexIdx(pVertex),
    m_ColorIdx(pColor),
    m_NormIdx(pNorm),
    m_TextureIdx(pText) {
}
 
void ModelVertex::getCoord(Coord& pCoord) const
{
  assert(isValid() &&
         "ModelVertex::Initialize(Model& pModel) should be called before calling "
         "ModelVertex::getCoord()");

  pCoord[0] = f_pModel->getObject()->vertices[m_VertexIdx*3];
  pCoord[1] = f_pModel->getObject()->vertices[m_VertexIdx*3 + 1];
  pCoord[2] = f_pModel->getObject()->vertices[m_VertexIdx*3 + 2];
  pCoord[3] = 1.0;
}

/// getColor - get the RGB color of the vertex
/// Original data is in the [-1, 1]. Linear interpolation to [0, 255]
void ModelVertex::getColor(Color& pColor) const
{
  assert(isValid() &&
         "ModelVertex::Initialize(Model& pModel) should be called before calling "
         "ModelVertex::getColor()");

  pColor.r = f_pModel->getObject()->colors[m_VertexIdx*3];
  pColor.g = f_pModel->getObject()->colors[m_VertexIdx*3 + 1];
  pColor.b = f_pModel->getObject()->colors[m_VertexIdx*3 + 2];
}

