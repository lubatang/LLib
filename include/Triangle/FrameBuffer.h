//===- FrameBuffer.h ------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_FRAME_BUFFER_H
#define LUBA_FRAME_BUFFER_H
#include <stdint.h>

namespace luba {

class FileHandle;

/** \class Color
 *  \brief Color represents the color of a pixel.
 */
class Color
{
public:
  uint8_t r;
  uint8_t g;
  uint8_t b;

public:
  Color() :r(0u), g(0u), b(0u)  {}
  Color(uint8_t pR, uint8_t pG, uint8_t pB) : r(pR), g(pG), b(pB) {}
  Color(const Color& pCopy);
  Color& operator=(const Color& pCopy);

};

/** \class FrameBuffer
 *  \brief FrameBuffer represents the image frame buffer of the graphics.
 */
class FrameBuffer
{
public:
  FrameBuffer(unsigned int width, unsigned int height);

  ~FrameBuffer();

  unsigned int getWidth () const { return m_Width;  } 
  unsigned int getHeight() const { return m_Height; } 

  void clear();

  void setColor(unsigned int x, unsigned int y, const Color &pColor);

  const uint8_t* getUCharArray() const { return (const uint8_t*)m_Colors; }

  bool saveAsPPM(FileHandle& pFile) const;

private:
  bool isValidCoord(unsigned int x, unsigned int y)
  {  return (x < m_Width && y < m_Height);}

private:
  Color* m_Colors;

  unsigned int m_Width;
  unsigned int m_Height;
};

} // namespace of luba

#endif

