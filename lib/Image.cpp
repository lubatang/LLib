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

void Image::setWrap(Wrap pWrap)
{
  g_Wrap = pWrap;
}

//===----------------------------------------------------------------------===//
// Image
//===----------------------------------------------------------------------===//
Image::Image()
  : m_Data(NULL) {
}

Image::~Image()
{
  if (NULL != m_Data) {
    free(m_Data);
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

  m_Data = (Color*)malloc(sizeof(Color)*m_Width*m_Height);

  for(int i = m_Height-1; i >= 0; --i ) {
    for(unsigned int j = 0; j < m_Width; ++j ) {
      Color* color = new (&m_Data[ i*m_Width + j]) Color();
      for(unsigned int k = 0; k < 3; ++k ) {
        int tmp;
        fscanf(file, "%d", &tmp );
        (*color)[k] = (double)tmp/255.0f;
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
  return m_Data[y*m_Width+ x];
}

Color& Image::getColor(double pU, double pV)
{
  unsigned int x = getX(pU);
  unsigned int y = getY(pV);
  assert((y*m_Width+ x) <= (m_Height*m_Width));
  return m_Data[ y*m_Width+ x];
}
