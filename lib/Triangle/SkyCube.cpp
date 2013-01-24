//===- SkyCube.cpp --------------------------------------------------------===//
//
// copyright (c), 2012-
// luba tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/SkyCube.h>

using namespace luba;

//===----------------------------------------------------------------------===//
// SkyCube
//===----------------------------------------------------------------------===//
SkyCube::SkyCube()
{
}

SkyCube::~SkyCube()
{
}

bool SkyCube::read(const std::string& pFileName)
{
  if (pFileName.empty())
    return false;

  FILE* file = fopen(pFileName.c_str(), "r");
  if (NULL == file)
    return false;

  m_Name = pFileName;

  //read the SkyCube information
  unsigned int width, height;
  fscanf(file, "%*s");
  fscanf(file, "%d %d", &width, &height);
  fscanf(file, "%*d");

  fclose(file);
  return true;
}

bool SkyCube::isOpened() const
{
  return true;
}

