//===- Translation.cpp ----------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Translation.h>
#include <iostream>

using namespace luba;

//===----------------------------------------------------------------------===//
// Translation
//===----------------------------------------------------------------------===//
Translation::Translation()
  : Stage("translation") {
}

const Translation& Translation::transform(Coord& pCoord) const
{
  return *this;
}

using namespace std;
void Translation::keyEvent(KeyEvent* pEvent)
{
  switch (pEvent->key()) {
    case KeyEvent::Keyt:
    case KeyEvent::KeyT: {
      cerr << "T" << endl;
      break;
    }
    case KeyEvent::KeyLeft: {
      break;
    }
    case KeyEvent::KeyRight: {
      break;
    }
    case KeyEvent::KeyDown: {
      break;
    }
    case KeyEvent::KeyUp: {
      break;
    }
  }
}

void Translation::mouseMoveEvent(MouseEvent* pEvent)
{
}

void Translation::mousePressEvent(MouseEvent* pEvent)
{
}

std::ostream& std::operator << (std::ostream& s, const luba::Translation& pTranslation)
{
}

