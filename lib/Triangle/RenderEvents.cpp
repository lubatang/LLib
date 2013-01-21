//===- RenderEvents.cpp ---------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/RenderEvents.h>
#include <iostream>

using namespace luba;
using namespace std;

//===----------------------------------------------------------------------===//
// RenderEvents
//===----------------------------------------------------------------------===//
RenderEvents::RenderEvents()
  : m_State(None) {
}

void RenderEvents::keyEvent(KeyEvent* pEvent)
{
  switch (pEvent->key()) {
    case KeyEvent::KeyM:
    case KeyEvent::Keym: {
      ++m_State;
      m_State %= NumOfState;
      switch (m_State) {
        case None:
          cerr << "Not to render" << endl;
          break;
        case Nearest:
          cerr << "Nearest sampling" << endl;
          break;
        case Linear:
          cerr << "Linear sampling" << endl;
          break;
      }
      break;
    }
    default: {
      break;
    }
  }
}

Image::Filtering RenderEvents::filter() const
{
  if (Linear == m_State)
    return Image::Linear;
  return Image::Nearest;
}

