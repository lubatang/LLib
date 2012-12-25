//===- Event.h ------------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_EVENT_H
#define LUBA_EVENT_H
#include <string>

namespace luba {

class Event
{
public:
  enum Type {
    KeyEvent
  };

public:
  explicit Event(Type pType);

  virtual ~Event() = 0;

  Type type() const { return m_Type; }

private:
  Type m_Type;
  
};

} // namespace luba

#endif

