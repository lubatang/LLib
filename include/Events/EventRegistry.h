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
class KeyEvent;
class MouseEvent;

class EventRegistry
{
public:
  typedef std::list<Stage*> StageList;
  typedef StageList::iterator iterator;
  typedef StageList::const_iterator const_iterator;

public:
  static EventRegistry& self() {
    static EventRegistry instance;
    return instance;
  }

  void record(Stage* pStage);

  void remove(Stage* pStage);

  const_iterator begin() const { return m_StageList.begin(); }
  iterator       begin()       { return m_StageList.begin(); }
  const_iterator end  () const { return m_StageList.end(); }
  iterator       end  ()       { return m_StageList.end(); }

  unsigned int size() const { return m_StageList.size(); }

  bool empty() const { return m_StageList.empty(); }

  void keyEvent(KeyEvent* pEvent);

  void mousePressEvent(MouseEvent* pEvent);

  void mouseReleaseEvent(MouseEvent* pEvent);

  void mouseMoveEvent(MouseEvent* pEvent);

private:
  EventRegistry();
  ~EventRegistry();
  EventRegistry(const EventRegistry& pER);            ///< DO NOT IMPLEMENT
  EventRegistry& operator=(const EventRegistry& pER); ///< DO NOT IMPLEMENT

private:
  StageList m_StageList;

};

} // namespace luba

#endif

