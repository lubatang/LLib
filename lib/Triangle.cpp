//===- Triangle.cpp -------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Triangle.h>
#include <Triangle/Vertex.h>

#include <algorithm>

using namespace luba;

Triangle::Triangle(const Vertex& pV1, const Vertex& pV2, const Vertex& pV3)
  : m_pV1(&pV1), m_pV2(&pV2), m_pV3(&pV3) {
  // sort by Y
  Coord v[3];
  v[0] = pV1.coord();
  v[1] = pV2.coord();
  v[2] = pV3.coord();

  if (v[0][1] < v[1][1]) {
    std::swap(v[0], v[1]);
    std::swap(m_pV1, m_pV2);
  }
  if (v[0][1] < v[2][1]) {
    std::swap(v[0], v[2]);
    std::swap(m_pV1, m_pV3);
  }

  if (v[1][1] < v[2][1]) {
    std::swap(v[1], v[2]);
    std::swap(m_pV2, m_pV3);
  }
}
