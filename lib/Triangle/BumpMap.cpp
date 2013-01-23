//===- BumpMap.cpp --------------------------------------------------------===//
//
// copyright (c), 2012-
// luba tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/BumpMap.h>

#include <cstdlib>
#include <cassert>
#include <cmath>

using namespace luba;

#include <iostream>
using namespace std;

//===----------------------------------------------------------------------===//
// BumpMap
//===----------------------------------------------------------------------===//
BumpMap::BumpMap()
  : m_NormList(NULL) {
}

BumpMap::~BumpMap()
{
  if (NULL != m_NormList) {
    free(m_NormList);
    m_NormList = NULL;
  }
}

bool BumpMap::read(const std::string& pFileName)
{
  if (pFileName.empty())
    return false;

  FILE* file = fopen(pFileName.c_str(), "r");
  if (NULL == file)
    return false;

  m_Name = pFileName;

  //read the BumpMap information
  fscanf(file, "%*s");
  fscanf(file, "%d %d", &m_Width, &m_Height);
  fscanf(file, "%*d");

  m_NormList = (Norm*)malloc(sizeof(Norm)*m_Width*m_Height);
  for(int i = m_Height-1; i >= 0; --i ) {
    for(unsigned int j = 0; j < m_Width; ++j ) {
      Norm* norm = new (m_NormList + m_Width*i + j) Norm();
      for(unsigned int k = 0; k < 3; ++k ) {
        int tmp;
        fscanf(file, "%d", &tmp );
        (*norm)[k] = (double)tmp/255.0f;
      }
    }
  }

  fclose(file);

  /// Calculate normals
  /// @{
  if (m_Width > 2 && m_Height > 2) { // border is 0 and (max -1)
    Norm* average = (Norm*)malloc(sizeof(Norm)*m_Width*m_Height);
    unsigned w, wEnd = m_Width - 1;
    unsigned h, hEnd = m_Height - 1;
    for (h = 1; h < hEnd; ++h) {
      for (w = 1; w < wEnd; ++w) {
        average[h*m_Width + w] = m_NormList[m_Width*h + w] +
                                 m_NormList[m_Width*(h + 1) + w] +
                                 m_NormList[m_Width*h + w + 1] +
                                 m_NormList[m_Width*(h + 1) + w + 1];
        average[h*m_Width + w] /= 4;
      }
    }

    for (h = 1; h < hEnd; ++h) {
      for (w = 1; w < wEnd; ++w) {
        m_NormList[m_Width*h + w] = average[h*m_Width + w];
      }
    }

    free(average);
  }
  /// @}

  return true;
}

unsigned int BumpMap::getX(double pU) const
{
  // clamp
  if (pU > 1.0) pU = 1.0;
  if (pU < 0.0) pU = 0.0;

  assert(pU >= 0.0 && pU <= 1.0 && "pU is out of range");
  return (unsigned int)(pU*(double)(m_Width - 1));
}

unsigned int BumpMap::getY(double pV) const
{
  // clamp
  if (pV > 1.0) pV = 1.0;
  if (pV < 0.0) pV = 0.0;

  assert(pV >= 0.0 && pV <= 1.0 && "pV is out of range");
  return (unsigned int)(pV*(double)(m_Height - 1));
}

const BumpMap::Norm& BumpMap::getNorm(double pU, double pV) const
{
  unsigned int x = getX(pU);
  unsigned int y = getY(pV);
  assert((y*m_Width+ x) <= (m_Height*m_Width));
  return m_NormList[y*m_Width + x];
}

BumpMap::Norm& BumpMap::getNorm(double pU, double pV)
{
  unsigned int x = getX(pU);
  unsigned int y = getY(pV);
  assert((y*m_Width+ x) <= (m_Height*m_Width));
  return m_NormList[y*m_Width + x];
}

