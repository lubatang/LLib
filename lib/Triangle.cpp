//===- Triangle.cpp -------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Triangle.h>
#include <Triangle/Vertex.h>
#include <Triangle/Coord.h>

#include <algorithm>

using namespace luba;

Triangle::Triangle(const Vertex& pV1, const Vertex& pV2, const Vertex& pV3)
  : m_pV1(&pV1), m_pV2(&pV2), m_pV3(&pV3) {
  // sort by Y
  Coord v[3];
  pV1.getCoord(v[0]);
  pV2.getCoord(v[1]);
  pV3.getCoord(v[2]);

  if (v[0].y < v[1].y) {
    std::swap(v[0], v[1]);
    std::swap(m_pV1, m_pV2);
  }
  if (v[0].y < v[2].y) {
    std::swap(v[0], v[2]);
    std::swap(m_pV1, m_pV3);
  }

  if (v[1].y < v[2].y) {
    std::swap(v[1], v[2]);
    std::swap(m_pV2, m_pV3);
  }
}
