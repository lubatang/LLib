//===- RenderEvents.h -----------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_RENDER_EVENTS_H
#define LUBA_RENDER_EVENTS_H
#include <iosfwd>
#include <Events/Stage.h>
#include <Events/KeyEvent.h>
#include <Triangle/Image.h>

namespace luba {

class RenderEvents : public Stage
{
public:
  enum State {
    None,
    Nearest,
    Linear,
    NumOfState = 3
  };

public:
  RenderEvents();

  void keyEvent(KeyEvent* pEvent);

  Image::Filtering filter() const;
  unsigned int state() const { return m_State; }

private:
  unsigned int m_State;
};

} // namespace luba

#endif

