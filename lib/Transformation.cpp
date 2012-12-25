//===- Transformation.cpp ----------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Transformation.h>
#include <iostream>

using namespace luba;

//===----------------------------------------------------------------------===//
// Transformation
//===----------------------------------------------------------------------===//
Transformation::Transformation()
  : Stage("transformation"), m_bActivated(false), m_bRotated(false),
    m_OrgX(0), m_OrgY(0), m_T() {
}

const Transformation& Transformation::transform(Coord& pCoord) const
{
  pCoord = m_T * pCoord;
  return *this;
}

void Transformation::moveRight()
{
  m_T[0][3] += 1;
}

void Transformation::moveLeft()
{
  m_T[0][3] -= 1;
}

void Transformation::moveUp()
{
  m_T[1][3] += 1;
}

void Transformation::moveDown()
{
  m_T[1][3] -= 1;
}

void Transformation::keyEvent(KeyEvent* pEvent)
{
  switch (pEvent->key()) {
    case KeyEvent::Keyt:
    case KeyEvent::KeyT: {
      m_bActivated = true;
      break;
    }
    case KeyEvent::KeyLeft: {
      if (m_bActivated)
        moveLeft();
      break;
    }
    case KeyEvent::KeyRight: {
      if (m_bActivated)
        moveRight();
      break;
    }
    case KeyEvent::KeyDown: {
      if (m_bActivated)
        moveDown();
      break;
    }
    case KeyEvent::KeyUp: {
      if (m_bActivated)
        moveUp();
      break;
    }
    default: {
      m_bActivated = false;
      break;
    }
  }
}

void Transformation::mouseMoveEvent(MouseEvent* pEvent)
{
  if (m_bActivated) {
    if (MouseEvent::NoButton != pEvent->button()) { // mouse pressed
      double deltaX = m_OrgX - pEvent->x();
      double deltaY = m_OrgY - pEvent->y();

      m_T[0][3] -= deltaX;
      m_T[1][3] += deltaY;

      m_OrgX = pEvent->x();
      m_OrgY = pEvent->y();
    }
  }
}

void Transformation::mousePressEvent(MouseEvent* pEvent)
{
  if (m_bActivated) {
    m_OrgX = pEvent->x();
    m_OrgY = pEvent->y();
  }
}

std::ostream& std::operator << (std::ostream& s, const luba::Transformation& pTransformation)
{
  return s << pTransformation.matrix();
}

