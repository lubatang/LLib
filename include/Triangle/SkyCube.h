//===- SkyCube.h ----------------------------------------------------------===//
//
// copyright (c), 2012-
// luba tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_SKY_CUBE_H
#define LUBA_SKY_CUBE_H

#include <vector>
#include <string>

namespace luba {

class SkyCube
{
public:
  SkyCube();
  ~SkyCube();

  //read the image and store it at the data
  bool read(const std::string& pFileName);

  bool isOpened() const;

private:
  std::string m_Name;

};

} // namespace of luba

#endif

