//===- MouseEvent.cpp -----------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Events/MouseEvent.h>

#include <cassert>

using namespace luba;

//===----------------------------------------------------------------------===//
// MouseEvent
//===----------------------------------------------------------------------===//
MouseEvent::MouseEvent()
  : Event(Event::MouseEvent), m_X(0), m_Y(0), m_Button(NoButton) {
}

MouseEvent::~MouseEvent()
{
}

void MouseEvent::setCoord(int pX, int pY)
{
  m_X = pX;
  m_Y = pY;
}

void MouseEvent::setButton(unsigned int pButton)
{
  assert(pButton <= (LeftButton | MidButton | RightButton));
  m_Button = pButton;
}

