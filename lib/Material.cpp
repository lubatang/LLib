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

using namespace luba;

#include <iostream>
using namespace std;
//===----------------------------------------------------------------------===//
// Material
//===----------------------------------------------------------------------===//
Material::Material(Model& pModel, unsigned int pIdx)
  : m_Model(pModel), m_Idx(pIdx), m_pImage(NULL) {

  unsigned int idx = m_Model.getObject()->materials[m_Idx].textureID;
  m_pImage = &pModel.getTextures().at(idx);
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

