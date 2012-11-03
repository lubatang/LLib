//===- Line.cpp -----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Line.h>
#include <Triangle/Vertex.h>
#include <Triangle/Coord.h>
#include <Triangle/Space.h>

#include <cmath>

using namespace luba;

//===----------------------------------------------------------------------===//
// Line
//===----------------------------------------------------------------------===//
Line::Line(const Vertex& pA, const Vertex& pB)
  : m_A(pA), m_B(pB) {
}

