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
  enum Wrap {
    Repeat,
    Clamp
  };

public:
  Image();

  ~Image();

  //read the image and store it at the data
  bool read(const std::string& pFileName);

  unsigned int width()  const { return m_Width;  }
  unsigned int height() const { return m_Height; }
  const std::string& name() const { return m_Name; }

  const Color& getColor(double pU, double pV) const;
  Color&       getColor(double pU, double pV);

  unsigned int getX(double pU) const;
  unsigned int getY(double pV) const;

  static void setWrap(Wrap pWrap);
  static Wrap wrap() { return g_Wrap; }
  static bool isRepeat() { return (Repeat == g_Wrap); }
  static bool isClamp()  { return (Clamp == g_Wrap); }

private:
  typedef Color* ColorList;

private:
  unsigned int m_Width;
  unsigned int m_Height;
  std::string m_Name;

  ColorList m_Data;

  static Wrap g_Wrap;
};

} // namespace of luba

#endif

