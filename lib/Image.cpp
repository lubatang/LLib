//===- Image.cpp ----------------------------------------------------------===//
//
// copyright (c), 2012-
// luba tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Image.h>
#include <Support/FileHandle.h>

#include <cassert>

#include <iostream>
using namespace std;
using namespace luba;

bool Image::read(const std::string& pFileName)
{
  if (pFileName.empty())
    return false;

  FILE* file = fopen(pFileName.c_str(), "r");
  if (NULL == file)
    return false;

  //read the Image information
  fscanf(file, "%*s");
  fscanf(file, "%d %d", &m_Width, &m_Height);
  fscanf(file, "%*d");

  m_Data.resize(m_Width*m_Height);

  for(int i = m_Height-1; i >= 0; --i ) {
    for(unsigned int j = 0; j < m_Width; ++j ) {
      for(unsigned int k = 0; k < 3; ++k ) {
        int tmp;
        fscanf(file, "%d", &tmp );
        m_Data[ i*m_Width + j ][k] = (double)tmp/255.0f;
      }
    }
  }

  fclose(file);
  return true;
}

