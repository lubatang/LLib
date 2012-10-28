//===- Model.cpp ----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Model.h>
#include <Triangle/Triangle.h>
#include <Triangle/Vertex.h>
#include <Triangle/FrameBuffer.h>

using namespace luba;

std::string Model::m_File;

//===----------------------------------------------------------------------===//
// Model
//===----------------------------------------------------------------------===//
Model::Model()
  : m_pObject(NULL) {

}

Model::~Model()
{
  glmDelete(m_pObject);
}

void Model::Initialize(int pArgc, char* pArgv[], const std::string& pFile)
{
  m_File = pFile;
  glutInit(&pArgc, pArgv);
}

void Model::LazyInitializeObject()
{
  if (NULL == m_pObject) {
    if (!m_File.empty())
      m_pObject = glmReadOBJ(m_File.c_str());
  }
}

Model::Object* Model::getObject()
{
  LazyInitializeObject();
  return m_pObject;
}

bool Model::draw(FrameBuffer& pFB) const
{
  if (NULL == m_pObject)
    return false;

  for(int i=0; i<(int)m_pObject->numtriangles; ++i) {
    for (size_t j=0; j<3; ++j) {
      int v1 = m_pObject->triangles[i].vindices[j];
      int n1 = m_pObject->triangles[i].nindices[j];
      int fn = m_pObject->triangles[i].findex;
      int t1 = m_pObject->triangles[i].tindices[j];
      Vertex vertex(*m_pObject, v1, n1, fn, t1);

      Coord coord;
      vertex.getCoord(coord);
      int x = (pFB.getWidth() + (int)(pFB.getWidth() * coord.x)) >> 1;
      int y = (pFB.getHeight() + (int)(pFB.getHeight() * coord.y)) >> 1;

      int z = 128 * coord.z + 128;
      Color color(z, z, z);
//      vertex.getColor(color);

      pFB.setColor(x, y, color);
    }
  }

  return true;
}

