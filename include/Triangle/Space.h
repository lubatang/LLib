//===- Space.h ------------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef SPACE_H
#define SPACE_H
#include <Triangle/Vertex.h>

namespace luba {

class Space
{
public:
  Space(unsigned int pWidth, unsigned int pHeight, unsigned int pDepth);

  void map(Vertex& pVertex) const;

  void setOrigin(unsigned int pX, unsigned int pY, unsigned int pZ);

  unsigned int width()  const { return m_Width; }
  unsigned int height() const { return m_Height; }
  unsigned int depth()  const { return m_Depth; }

  void setHeight(unsigned int pHeight) { m_Height = pHeight; }
  void setWidth(unsigned int pWidth)   { m_Width = pWidth; }
  void setDepth(unsigned int pDepth)   { m_Depth = pDepth; }

private:
  unsigned int m_Width;
  unsigned int m_Height;
  unsigned int m_Depth;

  unsigned int m_X;
  unsigned int m_Y;
  unsigned int m_Z;
};

} // namespace luba
#endif

