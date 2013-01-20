//===- Texture.h ----------------------------------------------------------===//
//
// copyright (c), 2012-
// luba tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_TEXTURE_H
#define LUBA_TEXTURE_H

namespace luba {

class Color;

class Texture
{
public:
  typedef Color* iterator;
  typedef const Color* const_iterator;

  enum Mapping {
    Nearest,
    Boxfilter
  };

public:
  Texture();
  virtual ~Texture();

  template<Mapping M>
  Texture& shrink(const Texture& pOther);

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  const Color& at(unsigned int pX, unsigned int pY) const;
  Color& at(unsigned int pX, unsigned int pY);

  unsigned int width() const { return m_Width; }
  unsigned int height() const { return m_Height; }

  Texture& resize(unsigned int pWidth, unsigned int pHeight);

protected:
  void reset();

protected:
  typedef Color* ColorList;

protected:
  unsigned int m_Width;
  unsigned int m_Height;
  ColorList m_Data;
};

template<> Texture&
Texture::shrink<Texture::Nearest>(const Texture& pOther);

template<> Texture&
Texture::shrink<Texture::Boxfilter>(const Texture& pOther);

} // namespace of luba

#endif

