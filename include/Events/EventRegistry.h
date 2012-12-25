//===- EventRegistry.h ----------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_EVENT_REGISTRY_H
#define LUBA_EVENT_REGISTRY_H
#include <list>

namespace luba {

class Stage;

class EventRegistry
{
public:
  static EventRegistry& self() {
    static EventRegistry instance;
    return instance;
  }

private:
  EventRegistry();
  ~EventRegistry();
  EventRegistry(const EventRegistry& pER);
  EventRegistry& operator=(const EventRegistry& pER);

private:
  typedef std::list<Stage*> StageList;

private:
  StageList m_StageList;

};

} // namespace luba

#endif

