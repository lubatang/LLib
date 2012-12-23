//===- Space.cpp ----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Space.h>

using namespace luba;

//===----------------------------------------------------------------------===//
// Space
//===----------------------------------------------------------------------===//
Space::Space(unsigned int pWidth, unsigned int pHeight, unsigned int pDepth)
  : m_Width(pWidth), m_Height(pHeight), m_Depth(pDepth), m_pCamera(NULL) {
}

void Space::map(Vertex& pVertex) const
{
  scaling(pVertex.coord(), (double)m_Width/2, (double)m_Height/2, (double)m_Depth/2);
  translate(pVertex.coord(), (double)(m_Width/2),
                             (double)(m_Height/2),
                             (double)(m_Depth/2));

  if (NULL != m_pCamera)
    m_pCamera->transform(pVertex.coord());
}

