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

class Material
{
public:
  Material(Model& pModel, unsigned int pIdx);

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

private:
  Model& m_Model;
  unsigned int m_Idx;
};

} // namespace of luba

#endif

