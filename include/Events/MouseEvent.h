//===- MouseEvent.h -------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_MOUSE_EVENT_H
#define LUBA_MOUSE_EVENT_H
#include <Events/Event.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

namespace luba {

class MouseEvent : public Event
{
public:
  enum Button {
    NoButton    = 0x0,
    LeftButton  = 0x1,
    MidButton   = 0x2,
    RightButton = 0x4
  };

public:
  MouseEvent();
  ~MouseEvent();

  int x() const { return m_X; }
  int y() const { return m_Y; }

  void setCoord(int pX, int pY);

  unsigned int button() const { return m_Button; }

  void setButton(unsigned int pButton);

  void reset() {
    m_X = m_Y = 0;
    m_Button = NoButton;
  }

private:
  int m_X;
  int m_Y;
  unsigned int m_Button;

};

} // namespace of luba

#endif

