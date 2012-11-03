//===- FrameBuffer.h ------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_FRAME_BUFFER_H
#define LUBA_FRAME_BUFFER_H
#include <stdint.h>

namespace luba {

class Color;
class FileHandle;

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

  void setColor(unsigned int pX, unsigned int pY, const Color &pColor);

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

