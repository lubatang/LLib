//===- KeyEvent.cpp -------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Events/KeyEvent.h>

using namespace luba;

//===----------------------------------------------------------------------===//
// KeyEvent
//===----------------------------------------------------------------------===//
KeyEvent::KeyEvent()
  : Event(Event::KeyEvent), m_Key(-1) {
}

KeyEvent::~KeyEvent()
{
  m_Key = -1;
}

void KeyEvent::setKey(int pKey)
{
  m_Key = pKey;
}

