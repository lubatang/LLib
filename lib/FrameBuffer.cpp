//===- FrameBuffer.cpp ----------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/FrameBuffer.h>
#include <Triangle/Color.h>
#include <Support/FileHandle.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace luba;

//===----------------------------------------------------------------------===//
// FrameBuffer
//===----------------------------------------------------------------------===//
FrameBuffer::FrameBuffer(unsigned int pWidth, unsigned int pHeight)
  : m_Width(pWidth), m_Height(pHeight) {

  size_t size = m_Width * m_Height;
  m_Pixels = (Pixel*)malloc(sizeof(Pixel)*size);
  memset(m_Pixels, 0u, size*sizeof(Pixel));

  m_ZBuffer = (unsigned int*)malloc(sizeof(unsigned int)*size);
  memset(m_ZBuffer, 0u, size*sizeof(unsigned int));
}

FrameBuffer::~FrameBuffer()
{
  free(m_Pixels);
}

void FrameBuffer::setColor(unsigned int pX, unsigned int pY, unsigned int pZ,
                           const Color &pColor)
{
  if(isValidCoord(pX, pY)) {
    size_t index = pX + pY*m_Width;
    if (pZ >= m_ZBuffer[index]) {
      Pixel round;
      round.r = pColor.r() * 127.5 + 127.5;
      round.g = pColor.g() * 127.5 + 127.5;
      round.b = pColor.b() * 127.5 + 127.5;
      m_Pixels[index] = round;
      m_ZBuffer[index] = pZ;
    }
  }
};

void FrameBuffer::clear()
{
  memset(m_Pixels, 0u, m_Width*m_Height*sizeof(Pixel));
  memset(m_ZBuffer, 0u, m_Width*m_Height*sizeof(unsigned int));
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

