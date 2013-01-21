//===- Image.h ------------------------------------------------------------===//
//
// copyright (c), 2012-
// luba tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_IMAGE_H
#define LUBA_IMAGE_H

#include <Triangle/Color.h>
#include <Triangle/Texture.h>
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

  enum Filtering {
    Nearest,
    Linear
  };

public:
  ~Image();

  //read the image and store it at the data
  bool read(const std::string& pFileName, bool pUseMipMap = true);

  unsigned int width()  const { return m_Width;  }
  unsigned int height() const { return m_Height; }
  const std::string& name() const { return m_Name; }

  template<Filtering F> Color getColor(double pU, double pV) const;

  unsigned int getX(double pU) const;
  unsigned int getY(double pV) const;

  static void setWrap(Wrap pWrap);
  static Wrap wrap() { return g_Wrap; }
  static bool isRepeat() { return (Repeat == g_Wrap); }
  static bool isClamp()  { return (Clamp == g_Wrap); }

  void setPolygonSize(double pSize) { m_PolySize = pSize; }
  void setTextureSize(double pSize) { m_TextureSize = pSize; }

private:
  typedef std::vector<Texture*> MipMap;

  unsigned int lod() const;

private:
  unsigned int m_Width;
  unsigned int m_Height;
  std::string m_Name;
  MipMap m_MipMap;
  double m_PolySize;
  double m_TextureSize;
  static Wrap g_Wrap;
};

template<> Color Image::getColor<Image::Nearest>(double pU, double pV) const;
template<> Color Image::getColor<Image::Linear>(double pU, double pV) const;

} // namespace of luba

#endif

