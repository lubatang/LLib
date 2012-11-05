//===- ColorIterator.cpp ---------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/ColorIterator.h>

#include <Triangle/Line.h>
#include <Triangle/Vertex.h>

using namespace luba;

//===----------------------------------------------------------------------===//
// ColorIterator
//===----------------------------------------------------------------------===//
ColorIterator::ColorIterator(const Line& pLine, float pDistance)
{
  Color to;
  pLine.front().getColor(m_Color);
  pLine.rear().getColor(to);
  m_Delta.r = (to.r - m_Color.r)/pDistance;
  m_Delta.g = (to.g - m_Color.g)/pDistance;
  m_Delta.b = (to.b - m_Color.b)/pDistance;
}

ColorIterator::ColorIterator()
{
}

ColorIterator::ColorIterator(const ColorIterator& pCopy)
{
  m_Color = pCopy.m_Color;
  m_Delta = pCopy.m_Delta;
}

ColorIterator& ColorIterator::operator=(const ColorIterator& pCopy)
{
  m_Color = pCopy.m_Color;
  m_Delta = pCopy.m_Delta;
  return *this;
}

ColorIterator& ColorIterator::next()
{
  m_Color += m_Delta;
}

