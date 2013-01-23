//===- Model.h ------------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_MODEL_H
#define LUBA_MODEL_H
#include <Triangle/Image.h>
#include <Triangle/BumpMap.h>
#include <Support/FileHandle.h>

#include <GLM/glm.h>

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

  static void Initialize(int pArgc, char* pArgv[],
                         const std::string& pFilename,
                         const std::string& pBumpMapPath);

  bool isValid() const;

  Object* getObject();

  const ImageList& images() const { return m_ImageList; }
  ImageList&       images()       { return m_ImageList; }

  const BumpMap& bumpMap() const { return m_BumpMap; }
  BumpMap&       bumpMap()       { return m_BumpMap; }

private:
  void LazyInitializeObject();
  void InitializeTextureBuffer();
  void InitializeBumpMap();

private:
  Model();
  ~Model();
  Model(const Model& pCopy);
  Model& operator=(const Model& pCopy);

private:
  static std::string m_File;
  static std::string m_BumpMapPath;
  Object* m_pObject;
  ImageList m_ImageList;
  BumpMap m_BumpMap;
};

} // namespace of luba

#endif

