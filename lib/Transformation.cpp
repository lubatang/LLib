//===- Transformation.cpp ----------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Transformation.h>
#include <Triangle/Space.h>
#include <iostream>

using namespace luba;

//===----------------------------------------------------------------------===//
// Transformation
//===----------------------------------------------------------------------===//
Transformation::Transformation()
  : Stage("transformation"), m_bActivated(false), m_bRotated(false),
    m_OrgX(0), m_OrgY(0), m_T(),
    m_pSpace(NULL) {
}

const Transformation& Transformation::transform(Coord& pCoord) const
{
  if (NULL != m_pSpace) {
    double sX = m_pSpace->width()/2;
    double sY = m_pSpace->height()/2;
    double sZ = m_pSpace->depth()/2;

    mat4 affine;
    affine[0][3] = -sX;
    affine[1][3] = -sY;
    affine[2][3] = -sZ;

    mat4 reverse;
    reverse[0][3] = sX;
    reverse[1][3] = sY;
    reverse[2][3] = sZ;

    pCoord = (reverse* m_T * affine) * pCoord;
  }
  else
    pCoord = m_T * pCoord;

  return *this;
}

void Transformation::move(double pX, double pY)
{
  m_T[0][3] += pX;
  m_T[1][3] += pY;
}

void Transformation::zoom(double pS)
{
  double scaling = 1.0 + pS / 40.0;
  m_T[0][0] *= scaling;
  m_T[1][1] *= scaling;
  m_T[2][2] *= scaling;
}

void Transformation::rotate(double pR)
{
}

void Transformation::keyEvent(KeyEvent* pEvent)
{
  switch (pEvent->key()) {
    case KeyEvent::Keyt:
    case KeyEvent::KeyT: {
      m_bActivated = true;
      break;
    }
    case KeyEvent::KeySpace: {
      if (m_bActivated)
        m_bRotated = !m_bRotated;
      break;
    }
    case KeyEvent::KeyLeft: {
      if (m_bActivated) {
        if (m_bRotated)
          rotate(-1);
        else
          move(-1, 0);
      }
      break;
    }
    case KeyEvent::KeyRight: {
      if (m_bActivated) {
        if (m_bRotated)
          rotate(1);
        else
          move(1, 0);
      }
      break;
    }
    case KeyEvent::KeyDown: {
      if (m_bActivated) {
        if (m_bRotated)
          zoom(-1);
        else
          move(0, -1);
      }
      break;
    }
    case KeyEvent::KeyUp: {
      if (m_bActivated) {
        if (m_bRotated)
          zoom(1);
        else
          move(0, 1);
      }
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
      double deltaX = pEvent->x() - m_OrgX;
      double deltaY = pEvent->y() - m_OrgY;

      if (m_bRotated) {
        zoom(deltaY);
        rotate(deltaX);
      }
      else {
        move(deltaX, -deltaY);
      }

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

