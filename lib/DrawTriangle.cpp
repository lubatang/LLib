//===- DrawTriangle.cpp ---------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/DrawTriangle.h>
#include <Triangle/Space.h>

#include <cmath>
#include <algorithm>

using namespace luba;

//===----------------------------------------------------------------------===//
// DrawTriangle
//===----------------------------------------------------------------------===//
DrawTriangle::DrawTriangle(const Space& pSpace,
                           const Coord& pA, const Coord& pB, const Coord& pC,
                           const Color& pCA, const Color& pCB, const Color& pCC)
  : m_Space(pSpace) {

}

DrawTriangle::const_iterator DrawTriangle::begin() const
{
  return const_iterator(*this);
}

DrawTriangle::const_iterator DrawTriangle::end() const
{
  return const_iterator(*this);
}

