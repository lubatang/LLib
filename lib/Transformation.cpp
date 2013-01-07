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

using namespace std;
using namespace luba;

//===----------------------------------------------------------------------===//
// Transformation
//===----------------------------------------------------------------------===//
Transformation::Transformation()
  : Stage("transformation"), m_bActivated(false),
    m_OrgX(0), m_OrgY(0), m_T(), m_S(), m_R(),
    m_State(MOVE),
    m_pSpace(NULL) {
}

void Transformation::move(double pX, double pY)
{
  m_T[0][3] += pX;
  m_T[1][3] += pY;
}

void Transformation::zoom(double pS)
{
  double scale = 1.0 + pS / 40.0;
  m_S[0][0] *= scale;
  m_S[1][1] *= scale;
  m_S[2][2] *= scale;
}

void Transformation::roll(double pX, double pY)
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
  m_R = (rotationX * rotationY) * m_R;
}

void Transformation::keyEvent(KeyEvent* pEvent)
{
  switch (pEvent->key()) {
    case KeyEvent::Keyt:
    case KeyEvent::KeyT: {
      m_bActivated = true;
      m_State = MOVE;
      cerr << "Controlling Model. (Press SPACE to change mouse modes)" << endl;
      break;
    }
    case KeyEvent::KeySpace: {
      if (m_bActivated) {
        ++m_State;
        m_State %= STATES;
        switch (m_State) {
          case MOVE: {
            cerr << "Moving model's position" << endl;
            break;
          }
          case ROTATE: {
            cerr << "Rotating model" << endl;
            break;
          }
          case ZOOM: {
            cerr << "Scaling model" << endl;
            break;
          }
        }
      }
      break;
    }
    case KeyEvent::KeyLeft: {
      if (m_bActivated) {
        switch (m_State) {
          case MOVE:   move(-1, 0);   break;
          case ROTATE: roll(-1, 0); break;
          default: break;
        }
      }
      break;
    }
    case KeyEvent::KeyRight: {
      if (m_bActivated) {
        switch (m_State) {
          case MOVE:   move(1, 0);   break;
          case ROTATE: roll(1, 0); break;
          default: break;
        }
      }
      break;
    }
    case KeyEvent::KeyDown: {
      if (m_bActivated) {
        switch (m_State) {
          case MOVE:   move(0, -1);   break;
          case ROTATE: roll(0, -1); break;
          case ZOOM:   zoom(-1); break;
        }
      }
      break;
    }
    case KeyEvent::KeyUp: {
      if (m_bActivated) {
        switch (m_State) {
          case MOVE:   move(0, 1);   break;
          case ROTATE: roll(0, 1); break;
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
          roll(deltaX, deltaY);
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
  return s << (pTransformation.trans() * pTransformation.scale() * pTransformation.rotate());
}

