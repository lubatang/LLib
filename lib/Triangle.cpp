//===- Triangle.cpp -------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Triangle.h>
#include <Triangle/Vertex.h>

using namespace luba;

Triangle::Triangle(const Vertex& pV1, const Vertex& pV2, const Vertex& pV3)
  : m_V1(pV1), m_V2(pV2), m_V3(pV3) {
}
