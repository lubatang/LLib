//===- Material.h ---------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_MATRIAL_H
#define LUBA_MATRIAL_H
#include <string>

namespace luba {

class Model;
class vec3D;
class Image;

class Material
{
public:
  Material(Model& pModel, unsigned int pIdx);

  ~Material();

  std::string name() const;

  void getAmbient(vec3D& pAmbient);
  vec3D ambient() const;

  void getDiffuse(vec3D& pDiffuse);
  vec3D diffuse() const;

  void getSpecular(vec3D& pSpecular);
  vec3D specular() const;

  void getEmmissive(vec3D& pEmmissive);
  vec3D emmissive() const;

  double shininess() const;

  const Image* image() const { return m_pImage; }
  Image*       image()       { return m_pImage; }

  bool hasImage() const { return (NULL != m_pImage); }

  void setImage(Image& pImage) { m_pImage = &pImage; }

private:
  Model& m_Model;
  unsigned int m_Idx;
  Image* m_pImage;
};

} // namespace of luba

#endif

