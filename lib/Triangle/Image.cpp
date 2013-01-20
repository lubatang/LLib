//===- Image.cpp ----------------------------------------------------------===//
//
// copyright (c), 2012-
// luba tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Image.h>
#include <Support/FileHandle.h>

#include <cstdlib>
#include <cassert>

using namespace luba;

#include <iostream>
using namespace std;

Image::Wrap Image::g_Wrap = Image::Repeat;

//===----------------------------------------------------------------------===//
// Helper Functions
//===----------------------------------------------------------------------===//
void Image::setWrap(Wrap pWrap)
{
  g_Wrap = pWrap;
}

//===----------------------------------------------------------------------===//
// Image
//===----------------------------------------------------------------------===//
Image::~Image()
{
  MipMap::iterator map, mEnd = m_MipMap.end();
  for (map = m_MipMap.begin(); map != mEnd; ++map) {
    delete *map;
  }
}

bool Image::read(const std::string& pFileName)
{
  if (pFileName.empty())
    return false;

  FILE* file = fopen(pFileName.c_str(), "r");
  if (NULL == file)
    return false;

  m_Name = pFileName;

  //read the Image information
  fscanf(file, "%*s");
  fscanf(file, "%d %d", &m_Width, &m_Height);
  fscanf(file, "%*d");
  Texture* origin = new Texture();
  m_MipMap.push_back(origin);
  origin->resize(m_Width, m_Height);

  for(int i = m_Height-1; i >= 0; --i ) {
    for(unsigned int j = 0; j < m_Width; ++j ) {
      Color& color = origin->at(j, i);
      for(unsigned int k = 0; k < 3; ++k ) {
        int tmp;
        fscanf(file, "%d", &tmp );
        color[k] = (double)tmp/255.0f;
      }
    }
  }

  fclose(file);
  return true;
}

unsigned int Image::getX(double pU) const
{
  switch(g_Wrap) {
    case Repeat: {
      while(pU > 1.0) pU -= 1.0;
      while(pU < 0.0) pU += 1.0;
      break;
    }
    case Clamp: {
      if (pU > 1.0) pU = 1.0;
      if (pU < 0.0) pU = 0.0;
      break;
    }
  }

  assert(pU >= 0.0 && pU <= 1.0 && "pU is out of range");
  return (unsigned int)(pU*(double)(m_Width - 1));
}

unsigned int Image::getY(double pV) const
{
  switch(g_Wrap) {
    case Repeat: {
      while(pV > 1.0) pV -= 1.0;
      while(pV < 0.0) pV += 1.0;
      break;
    }
    case Clamp: {
      if (pV > 1.0) pV = 1.0;
      if (pV < 0.0) pV = 0.0;
      break;
    }
  }

  assert(pV >= 0.0 && pV <= 1.0 && "pV is out of range");
  return (unsigned int)(pV*(double)(m_Height - 1));
}

const Color& Image::getColor(double pU, double pV) const
{
  unsigned int x = getX(pU);
  unsigned int y = getY(pV);
  assert((y*m_Width+ x) <= (m_Height*m_Width));
  return m_MipMap[0]->at(x, y);
}

Color& Image::getColor(double pU, double pV)
{
  unsigned int x = getX(pU);
  unsigned int y = getY(pV);
  assert((y*m_Width+ x) <= (m_Height*m_Width));
  return m_MipMap[0]->at(x, y);
}
