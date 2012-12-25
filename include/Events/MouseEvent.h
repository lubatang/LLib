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
  MouseEvent();
  ~MouseEvent();
};

} // namespace of luba

#endif

