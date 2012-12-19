//===- Line.cpp -----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Line.h>
#include <Triangle/Vertex.h>
#include <Triangle/Space.h>

#include <cmath>
#include <iostream>

using namespace luba;

//===----------------------------------------------------------------------===//
// Line
//===----------------------------------------------------------------------===//
Line::Line(const Vertex& pA, const Vertex& pB)
  : m_A(pA), m_B(pB) {
}

std::ostream& std::operator << (std::ostream& s, const luba::Line& pLine)
{
  s << "<line from=(" << pLine.front().x() << ", " << pLine.front().y() << ", " << pLine.front().z() << ")";
  s << " to=(" << pLine.rear().x() << ", " << pLine.rear().y() << ", " << pLine.rear().z() << ")>";
}

