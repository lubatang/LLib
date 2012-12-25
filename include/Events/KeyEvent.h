//===- KeyEvent.h ---------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_KEY_EVENT_H
#define LUBA_KEY_EVENT_H
#include <Events/Event.h>

namespace luba {

class KeyEvent : public Event
{
public:
  KeyEvent();
  ~KeyEvent();

  void setKey(int pKey);
  int key() const { return m_Key; }

private:
  int m_Key;
};

} // namespace of luba

#endif

