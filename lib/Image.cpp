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

//===----------------------------------------------------------------------===//
// Image
//===----------------------------------------------------------------------===//
Image::Image()
  : m_Data(NULL) {
}

Image::~Image()
{
  if (NULL != m_Data) {
    for (unsigned int i = 0; i < m_Width*m_Height; ++i) {
      m_Data[i].~Color();
    }
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
      Color* color = m_Data + i*m_Width + j;
      new (color) Color();
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

const Color& Image::getColor(double pU, double pV) const
{
  assert(pU <= 1.0 && pV <= 1.0 && "Either pU or pV is out of range");
  unsigned int x = pU*(double)(m_Width - 1);
  unsigned int y = pV*(double)(m_Height - 1);
  return *(m_Data + x*m_Width + y);
}

Color& Image::getColor(double pU, double pV)
{
  assert(pU <= 1.0 && pV <= 1.0 && "Either pU or pV is out of range");
  unsigned int x = pU*(double)(m_Width - 1);
  unsigned int y = pV*(double)(m_Height - 1);
  return *(m_Data + x*m_Width + y);
}
