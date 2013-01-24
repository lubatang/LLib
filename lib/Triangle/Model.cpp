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

#include <iostream>
#include <cstdlib>

using namespace luba;
using namespace std;

std::string Model::m_File;
std::string Model::m_BumpMapPath;
std::string Model::m_SkyCubePath;

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

void Model::Initialize(int pArgc, char* pArgv[],
                       const std::string& pFile,
                       const std::string& pBumpMapPath,
                       const std::string& pSkyCubePath)
{
  m_File = pFile;
  m_BumpMapPath = pBumpMapPath;
  m_SkyCubePath = pSkyCubePath;
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
      InitializeBumpMap();
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

void Model::InitializeBumpMap()
{
  if (m_BumpMapPath.empty())
    return;

  if (!m_BumpMap.read(m_BumpMapPath)) {
    cerr << "Error: cannot read bump map `" << m_BumpMapPath << "'." << endl;
    exit(1);
  }
}

void Model::InitializeSkyCube()
{
  if (m_SkyCubePath.empty())
    return;

  if (!m_SkyCube.read(m_SkyCubePath)) {
    cerr << "Error: cannot read sky cube`" << m_SkyCubePath << "'." << endl;
    exit(1);
  }
}

