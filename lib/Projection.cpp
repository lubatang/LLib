//===- Projection.cpp -----------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Projection.h>
#include <Triangle/Vectors.h>
#include <iostream>
#include <cmath>
#include <cassert>

using namespace luba;

//===----------------------------------------------------------------------===//
// Projection
//===----------------------------------------------------------------------===//
Projection::Projection()
  : m_Mode(Parallel), m_Distance(0) {
  m_P[2][2] = 0.0;
}

const Projection& Projection::transform(Coord& pCoord) const
{
  pCoord = m_P * pCoord;
  return *this;
}

#include <iostream>
using namespace std;
void Projection::keyEvent(KeyEvent* pEvent)
{
  switch (pEvent->key()) {
    case KeyEvent::Keyp:
    case KeyEvent::KeyP: {
      ++m_Mode;
      m_Mode %= NumOfMode;
      cerr << "projection mode is ";
      if (Parallel == m_Mode) {
        cerr << "parallel" << endl;
        m_P[3][2] = 0.0;
      }
      else {
        cerr << "perspective" << endl;
        m_P[3][2] = (1/m_Distance);
      }

      cerr << "  distance=" << m_Distance << endl;

      cerr << m_P << endl;

      break;
    }
    default:
      break;
  }
}

std::ostream& std::operator << (std::ostream& s, const luba::Projection& pProjection)
{
  return s << pProjection.matrix();
}

