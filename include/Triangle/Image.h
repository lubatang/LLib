//===- Image.h ------------------------------------------------------------===//
//
// copyright (c), 2012-
// luba tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_IMAGE_H
#define LUBA_IMAGE_H

#include <Triangle/Color.h>
#include <vector>
#include <string>

namespace luba {

class Image
{
public:
  //read the image and store it at the data
  bool read(const std::string& pFileName);

  unsigned int width()  const { return m_Width;  }
  unsigned int height() const { return m_Height; }

private:
  typedef std::vector<Color> ColorList;

private:
  unsigned int m_Width;
  unsigned int m_Height;

  ColorList m_Data;
};

} // namespace of luba

#endif

