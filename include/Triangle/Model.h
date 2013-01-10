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

namespace luba {

class FrameBuffer;

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

  bool isValid() const;

  Object* getObject();

  const TextureBuffer& getTextures() const { return m_TextureBuffer; }
  TextureBuffer&       getTextures()       { return m_TextureBuffer; }

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
  TextureBuffer m_TextureBuffer;
};

} // namespace of luba

#endif

