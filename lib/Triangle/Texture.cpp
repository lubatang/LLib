//===- Texture.cpp --------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Texture.h>
#include <Triangle/Color.h>

#include <cstdlib>
#include <cassert>

//using namespace luba;

//===----------------------------------------------------------------------===//
// Texture
//===----------------------------------------------------------------------===//
// For the damn low quality GLM, I must explicitly indicate my own texture
// class.
luba::Texture::Texture()
  : m_Data(NULL), m_Width(0), m_Height(0) {
}

luba::Texture::~Texture()
{
  reset();
}

void luba::Texture::reset()
{
  if (NULL != m_Data) {
    free(m_Data);
    m_Data = NULL;
    m_Width = m_Height = 0;
  }
}

template<> luba::Texture&
luba::Texture::shrink<luba::Texture::Nearest>(const luba::Texture& pOther)
{
  resize(pOther.width()/2, pOther.height()/2);
  for (unsigned int j = 0; j < m_Height; ++j) {
    for (unsigned int i = 0; i < m_Width; ++i) {
      Color *color = new (&m_Data[j*m_Width + i]) Color(pOther.at(i*2, j*2));
    }
  }
  return *this;
}

template<> luba::Texture&
luba::Texture::shrink<luba::Texture::Boxfilter>(const luba::Texture& pOther)
{
  reset();
  m_Width = pOther.width() / 2;
  m_Height = pOther.height() / 2;
  m_Data = (Color*) malloc(sizeof(Color)*m_Width*m_Height);
  for (unsigned int j = 0; j < m_Height; ++j) {
    for (unsigned int i = 0; i < m_Width; ++i) {
      Color *color = new (&m_Data[j*m_Width + i]) Color(
                                          pOther.at(i*2, j*2) + 
                                          pOther.at(i*2 + 1, j*2) + 
                                          pOther.at(i*2, j*2 + 1) + 
                                          pOther.at(i*2 + 1, j*2 + 1));
      *color /= 4;
    }
  }
  return *this;
}

luba::Texture::iterator luba::Texture::begin()
{
  return m_Data;
}

luba::Texture::iterator luba::Texture::end()
{
  return m_Data + (m_Width*m_Height);
}

luba::Texture::const_iterator luba::Texture::begin() const
{
  return m_Data;
}

luba::Texture::const_iterator luba::Texture::end() const
{
  return m_Data + (m_Width*m_Height);
}

luba::Color& luba::Texture::at(unsigned int pX, unsigned int pY)
{
  assert(NULL != m_Data);
  // For a single texture, we should clamp the coordinate.
  if (pX >= m_Width) pX = m_Width - 1;
  if (pY >= m_Height) pY = m_Height - 1;
  return m_Data[pY*m_Width + pX];
}

const luba::Color& luba::Texture::at(unsigned int pX, unsigned int pY) const
{
  assert(NULL != m_Data);
  // For a single texture, we should clamp the coordinate.
  if (pX >= m_Width) pX = m_Width - 1;
  if (pY >= m_Height) pY = m_Height - 1;
  return m_Data[pY*m_Width + pX];
}

luba::Texture& luba::Texture::resize(unsigned int pWidth, unsigned int pHeight)
{
  reset();
  m_Width = pWidth;
  m_Height = pHeight;
  m_Data = (Color*) malloc(sizeof(Color)*m_Width*m_Height);
  return *this;
}

