//===- FrameBuffer.cpp ----------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/FrameBuffer.h>
#include <Support/FileHandle.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace luba;

//===----------------------------------------------------------------------===//
// Color
//===----------------------------------------------------------------------===//
Color::Color(const Color& pCopy)
{
  r = pCopy.r;
  g = pCopy.g;
  b = pCopy.b;
}

Color& Color::operator=(const Color& pCopy)
{
  r = pCopy.r;
  g = pCopy.g;
  b = pCopy.b;
  return *this;
}

//===----------------------------------------------------------------------===//
// FrameBuffer
//===----------------------------------------------------------------------===//
FrameBuffer::FrameBuffer(unsigned int pWidth, unsigned int pHeight)
  : m_Width(pWidth), m_Height(pHeight) {

  size_t size = m_Width * m_Height;
  m_Colors = (Color*)malloc(sizeof(Color)*size);
  memset(m_Colors, 0u, m_Width*m_Height*sizeof(Color));
}

FrameBuffer::~FrameBuffer()
{
  free(m_Colors);
}

void FrameBuffer::setColor(unsigned int x, unsigned int y, const Color &pColor)
{
  if(isValidCoord(x, y))
    m_Colors[x+y*m_Width] = pColor;
};

void FrameBuffer::clear()
{
  memset(m_Colors, 0u, m_Width*m_Height*sizeof(Color));
}

bool FrameBuffer::saveAsPPM(FileHandle& pFile) const
{
  if (!pFile.isOpened() || !pFile.isGood() || !pFile.isWritable())
    return false;

  FILE* fd = fdopen(pFile.handler(), "w");
  fprintf(fd, "P3 %d %d 255\n", m_Width, m_Height);
  const unsigned char * bits = getUCharArray();
  for(int y=m_Height -1; y>=0; y--) {
    for (unsigned int x=0; x<m_Width; x++) {
      const unsigned char * pixel = &(bits[(x+y*m_Width)*3]);
      //fwrite(pixel, sizeof(unsigned char), 3, fp);
      fprintf(fd, "%u %u %u ", pixel[0], pixel[1], pixel[2]);
    }
  }

  return true;
}

