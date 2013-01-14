//===- Model.cpp ----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Model.h>
#include <Triangle/Triangle.h>
#include <Triangle/FrameBuffer.h>
#include <Triangle/Line.h>
#include <Triangle/Image.h>

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
  ImageList::iterator image, iEnd = m_ImageList.end();
  for (image = m_ImageList.begin(); image != iEnd; ++image) {
    delete *image;
  }
}

void Model::Initialize(int pArgc, char* pArgv[], const std::string& pFile)
{
  m_File = pFile;
  glutInit(&pArgc, pArgv);
}

bool Model::isValid() const
{
  return (NULL != m_pObject);
}

void Model::LazyInitializeObject()
{
  if (NULL == m_pObject) {
    if (!m_File.empty()) {
      m_pObject = glmReadOBJ(m_File.c_str());
      InitializeTextureBuffer();
    }
  }
}

Model::Object* Model::getObject()
{
  LazyInitializeObject();
  return m_pObject;
}

void Model::InitializeTextureBuffer()
{
  m_pObject->materials[0].textureID = -1;
  if (m_pObject->nummaterials == 1)
    return;

  for (unsigned int i = 1; i < m_pObject->nummaterials; ++i) {
    std::string path(m_pObject->materials[i].textureImageName);
    if (path.empty()) {
      m_pObject->materials[i].textureID = -1;
      continue;
    }

    Image* image = new Image();
    if (!image->read(path)) {
      delete image;
      m_pObject->materials[i].textureID = -1;
    }
    else {
      m_pObject->materials[i].textureID = m_ImageList.size();
      m_ImageList.push_back(image);
    }
  }
}

