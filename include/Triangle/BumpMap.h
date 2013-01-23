//===- BumpMap.h ----------------------------------------------------------===//
//
// copyright (c), 2012-
// luba tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_BUMP_MAP_H
#define LUBA_BUMP_MAP_H

#include <Triangle/Texture.h>
#include <algebra/vec3.h>
#include <vector>
#include <string>

namespace luba {

class BumpMap
{
public:
  typedef vec3 Norm;
public:
  BumpMap();
  ~BumpMap();

  //read the image and store it at the data
  bool read(const std::string& pFileName);

  bool isOpened() const { return (NULL != m_NormList); }

  unsigned int width()  const { return m_Width;  }
  unsigned int height() const { return m_Height; }
  const std::string& name() const { return m_Name; }

  const Norm& getNorm(double pU, double pV) const;
  Norm&       getNorm(double pU, double pV);

  unsigned int getX(double pU) const;
  unsigned int getY(double pV) const;

private:
  typedef Norm* NormList;

private:
  unsigned int m_Width;
  unsigned int m_Height;
  std::string m_Name;
  NormList m_NormList;
};

} // namespace of luba

#endif

