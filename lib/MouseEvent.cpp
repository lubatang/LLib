//===- MouseEvent.cpp -----------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Events/MouseEvent.h>

using namespace luba;

//===----------------------------------------------------------------------===//
// MouseEvent
//===----------------------------------------------------------------------===//
MouseEvent::MouseEvent()
  : Event(Event::MouseEvent) {
}

MouseEvent::~MouseEvent()
{
}

