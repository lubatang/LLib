//===- Model.h ------------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_MODEL_H
#define LUBA_MODEL_H
#include <GLM/glm.h>
#include <Support/FileHandle.h>
#include <string>

namespace luba {

class Model
{
public:
  typedef GLMmodel Object;

public:
  static Model& self() {
    static Model instance;
    return instance;
  }

  static void Initialize(int pArgc, char* pArgv[], const std::string& pFilename);

  Object*       getObject();

private:
  void LazyInitializeObject();

private:
  Model();
  ~Model();
  Model(const Model& pCopy);
  Model& operator=(const Model& pCopy);

private:
  static std::string m_File;
  Object* m_pObject;
};

} // namespace of luba

#endif

