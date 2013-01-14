//===- Model.h ------------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_MODEL_H
#define LUBA_MODEL_H
#include <Triangle/Image.h>
#include <GLM/glm.h>
#include <Support/FileHandle.h>
#include <string>
#include <vector>

namespace luba {

class FrameBuffer;

class Model
{
public:
  typedef GLMmodel Object;
  typedef std::vector<Image*> ImageList;

public:
  static Model& self() {
    static Model instance;
    return instance;
  }

  static void Initialize(int pArgc, char* pArgv[], const std::string& pFilename);

  bool isValid() const;

  Object* getObject();

  const ImageList& images() const { return m_ImageList; }
  ImageList&       images()       { return m_ImageList; }

private:
  void LazyInitializeObject();
  void InitializeTextureBuffer();

private:
  Model();
  ~Model();
  Model(const Model& pCopy);
  Model& operator=(const Model& pCopy);

private:
  static std::string m_File;
  Object* m_pObject;
  ImageList m_ImageList;
};

} // namespace of luba

#endif

