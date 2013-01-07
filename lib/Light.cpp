//===- Light.cpp ----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Light.h>
#include <Triangle/Vectors.h>
#include <Events/KeyEvent.h>
#include <Events/MouseEvent.h>

#include <cmath>
#include <iostream>

using namespace std;
using namespace luba;

//===----------------------------------------------------------------------===//
// Light
//===----------------------------------------------------------------------===//
Light::Light()
  : Stage("light"), m_bActive(false), m_OrgX(0), m_OrgY(0),
    m_Position(1000, 1000, 1000, 0),
    m_Ambient(0.1, 0.1, 0.1, 1.0),
    m_Diffuse(1.0, 1.0, 1.0, 1.0),
    m_Specular(0.2, 0.2, 0.2, 1.0),
    m_Direction(-1, -1, -1, 1.0),
    m_Kc(1.0),
    m_Kl(0),
    m_Kq(0),
    m_SpotExpo(1),
    m_State(MOVE) {
}

void Light::setPosition(double pX, double pY, double pZ)
{
  m_Position[0] = pX;
  m_Position[1] = pY;
  m_Position[2] = pZ;
}

void Light::getPosition(vec3& pPos)
{
  pPos.set(m_Position[0], m_Position[1], m_Position[2]);
}

void Light::move(double pX, double pY)
{
  m_Position[0] += pX;
  m_Position[1] += pY;
}

void Light::spot(double pX, double pY)
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
  m_Direction = (rotationX * rotationY) * m_Direction;
}

void Light::roll(double pX, double pY)
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
  m_Position = (rotationX * rotationY) * m_Position;
}

void Light::keyEvent(KeyEvent* pEvent)  
{
  switch (pEvent->key()) {
    case KeyEvent::Keyl:
    case KeyEvent::KeyL: {
      m_bActive = true;
      m_State = MOVE;
      cerr << "Controlling Light. (Press SPACE to change mouse modes)" << endl;
      break;
    }
    case KeyEvent::KeySpace: {
      if (m_bActive) {
        ++m_State;
        m_State %= STATES;
        switch (m_State) {
          case MOVE: {
            cerr << "Moving light position" << endl;
            break;
          }
          case ROTATE: {
            cerr << "Rotating light position" << endl;
            break;
          }
          case SPOT: {
            cerr << "Adjust light direction (for spot light)" << endl;
            break;
          }
        }
      }
      break;
    }
    case KeyEvent::KeyLeft: {
      if (m_bActive) {
        switch (m_State) {
          case MOVE:   move(-1, 0); break;
          case ROTATE: roll(-1, 0); break;
          case SPOT:   spot(-1, 0); break;
          default: break;
        }
      }
      break;
    }
    case KeyEvent::KeyRight: {
      if (m_bActive) {
        switch (m_State) {
          case MOVE:   move(1, 0); break;
          case ROTATE: roll(1, 0); break;
          case SPOT:   spot(1, 0); break;
          default: break;
        }
      }
      break;
    }
    case KeyEvent::KeyDown: {
      if (m_bActive) {
        switch (m_State) {
          case MOVE:   move(0, -1); break;
          case ROTATE: roll(0, -1); break;
          case SPOT:   spot(0, -1); break;
        }
      }
      break;
    }
    case KeyEvent::KeyUp: {
      if (m_bActive) {
        switch (m_State) {
          case MOVE:   move(0, 1);   break;
          case ROTATE: roll(0, 1); break;
          case SPOT:   spot(0, 1); break;
        }
      }
      break;
    }
    default: {
      m_bActive = false;
      break;
    }
  }
}

void Light::mouseMoveEvent(MouseEvent* pEvent)
{
  if (m_bActive) {
    double deltaX = pEvent->x() - m_OrgX;
    double deltaY = pEvent->y() - m_OrgY;

    if (MouseEvent::NoButton != pEvent->button()) {
      switch (m_State) {
        case MOVE: {
          move(deltaX, deltaY);
          break;
        }
        case ROTATE: {
          roll(deltaX, deltaY);
          break;
        }
        case SPOT: {
          spot(deltaX, deltaY);
          break;
        }
      }
    }

    m_OrgX = pEvent->x();
    m_OrgY = pEvent->y();
  }
}

void Light::mousePressEvent(MouseEvent* pEvent)
{
  if (m_bActive) {
    m_OrgX = pEvent->x();
    m_OrgY = pEvent->y();
  }
}

