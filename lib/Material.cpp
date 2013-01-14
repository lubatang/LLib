//===- Material.cpp -------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Material.h>
#include <Triangle/Model.h>
#include <Triangle/Vectors.h>
#include <Triangle/Image.h>

#include <cassert>
#include <iostream>

using namespace luba;
using namespace std;

//===----------------------------------------------------------------------===//
// Material
//===----------------------------------------------------------------------===//
Material::Material(Model& pModel, unsigned int pIdx)
  : m_Model(pModel), m_Idx(pIdx), m_pImage(NULL) {

  int idx = m_Model.getObject()->materials[pIdx].textureID;

  if (-1 != idx) {
    try {
      m_pImage = pModel.images().at(idx);
    }
    catch (...) {
      cerr << "Fatal error: require a texture that is out of range.\n"
           << "require index: " << idx << "\n"
           << "textures:\n";
      unsigned int count = 0;
      Model::ImageList::const_iterator text, tEnd = pModel.images().end();
      for (text = pModel.images().begin(); text != tEnd; ++text) {
        cerr << "  #" << count << "\t" << (*text)->name() << endl;
        ++count;
      }
      exit(1);
    }
  }
}

Material::~Material()
{
}

std::string Material::name() const
{
  return std::string(m_Model.getObject()->materials[m_Idx].name);
}

void Material::getAmbient(vec3D& pAmbient)
{
  pAmbient = m_Model.getObject()->materials[m_Idx].ambient;
}

vec3D Material::ambient() const
{
  return m_Model.getObject()->materials[m_Idx].ambient;
}

void Material::getDiffuse(vec3D& pDiffuse)
{
  pDiffuse = m_Model.getObject()->materials[m_Idx].diffuse;
}

vec3D Material::diffuse() const
{
  return m_Model.getObject()->materials[m_Idx].diffuse;
}

void Material::getSpecular(vec3D& pSpecular)
{
  pSpecular = m_Model.getObject()->materials[m_Idx].specular;
}

vec3D Material::specular() const
{
  return m_Model.getObject()->materials[m_Idx].specular;
}

void Material::getEmmissive(vec3D& pEmmissive)
{
  assert(false && "GLM does not implement emission");
  pEmmissive = m_Model.getObject()->materials[m_Idx].emmissive;
}

vec3D Material::emmissive() const
{
  assert(false && "GLM does not implement emission");
  return m_Model.getObject()->materials[m_Idx].emmissive;
}

double Material::shininess() const
{
  return m_Model.getObject()->materials[m_Idx].shininess;
}

