//===- Transformation.cpp ----------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Transformation.h>
#include <Triangle/Space.h>
#include <Triangle/Vectors.h>
#include <iostream>
#include <cmath>
#include <cassert>

using namespace luba;

//===----------------------------------------------------------------------===//
// Transformation
//===----------------------------------------------------------------------===//
Transformation::Transformation()
  : Stage("transformation"), m_bActivated(false),
    m_OrgX(0), m_OrgY(0), m_T(),
    m_State(MOVE),
    m_pSpace(NULL) {
}

const Transformation& Transformation::transform(Coord& pCoord) const
{
  assert(NULL != m_pSpace);
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
  double scale = 1.0 + pS / 40.0;
  mat4 scaling;
  scaling[0][0] = scale;
  scaling[1][1] = scale;
  scaling[2][2] = scale;
  m_T = scaling * m_T;
}

void Transformation::rotate(double pX, double pY)
{
  double radianX = (pX * luba::PI) / 180.0;
  mat4 rotationY;
  rotationY[0][0] = cos(radianX);
  rotationY[0][2] = sin(radianX);
  rotationY[2][0] = -sin(radianX);
  rotationY[2][2] = cos(radianX);

  double radianY = (pY * luba::PI) / 180.0;
  mat4 rotationX;
  rotationX[1][1] = cos(radianY);
  rotationX[1][2] = -sin(radianY);
  rotationX[2][1] = sin(radianY);
  rotationX[2][2] = cos(radianY);
  m_T = (rotationX * rotationY) * m_T;
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
      if (m_bActivated) {
        ++m_State;
        m_State %= STATES;
      }
      break;
    }
    case KeyEvent::KeyLeft: {
      if (m_bActivated) {
        switch (m_State) {
          case MOVE:   move(-1, 0);   break;
          case ROTATE: rotate(-1, 0); break;
          default: break;
        }
      }
      break;
    }
    case KeyEvent::KeyRight: {
      if (m_bActivated) {
        switch (m_State) {
          case MOVE:   move(1, 0);   break;
          case ROTATE: rotate(1, 0); break;
          default: break;
        }
      }
      break;
    }
    case KeyEvent::KeyDown: {
      if (m_bActivated) {
        switch (m_State) {
          case MOVE:   move(0, -1);   break;
          case ROTATE: rotate(0, -1); break;
          case ZOOM:   zoom(-1); break;
        }
      }
      break;
    }
    case KeyEvent::KeyUp: {
      if (m_bActivated) {
        switch (m_State) {
          case MOVE:   move(0, 1);   break;
          case ROTATE: rotate(0, 1); break;
          case ZOOM:   zoom(1); break;
        }
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
    double deltaX = pEvent->x() - m_OrgX;
    double deltaY = pEvent->y() - m_OrgY;

    if (MouseEvent::NoButton != pEvent->button()) {
      switch (m_State) {
        case MOVE: {
          move(deltaX, -deltaY);
          break;
        }
        case ROTATE: {
          rotate(deltaX, deltaY);
          break;
        }
        case ZOOM: {
          zoom(-deltaY);
          break;
        }
      }
    }
    m_OrgX = pEvent->x();
    m_OrgY = pEvent->y();
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

