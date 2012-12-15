//===- Model.cpp ----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Model.h>
#include <Triangle/Triangle.h>
#include <Triangle/FrameBuffer.h>
#include <Triangle/Line.h>

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

bool Model::isValid() const
{
  return (NULL != m_pObject);
}

void Model::LazyInitializeObject()
{
  if (NULL == m_pObject) {
    if (!m_File.empty()) {
      m_pObject = glmReadOBJ(m_File.c_str());
    }
  }
}

Model::Object* Model::getObject()
{
  LazyInitializeObject();
  return m_pObject;
}

