//===- ColorIterator.cpp ---------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/ColorIterator.h>

using namespace luba;

//===----------------------------------------------------------------------===//
// ColorIterator
//===----------------------------------------------------------------------===//
ColorIterator::ColorIterator(const Color& pCA, const Color& pCB, float pDistance)
  : m_Color(pCA){
  m_Delta.r = (pCB.r - pCA.r)/pDistance;
  m_Delta.g = (pCB.g - pCA.g)/pDistance;
  m_Delta.b = (pCB.b - pCA.b)/pDistance;
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

