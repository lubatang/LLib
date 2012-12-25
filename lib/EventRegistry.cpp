//===- EventRegistry.cpp --------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Events/EventRegistry.h>
#include <Events/KeyEvent.h>
#include <Events/Stage.h>

using namespace luba;

//===----------------------------------------------------------------------===//
// EventRegistry
//===----------------------------------------------------------------------===//
EventRegistry::EventRegistry()
{
}

EventRegistry::~EventRegistry()
{
}

void EventRegistry::record(Stage* pStage)
{
  m_StageList.push_back(pStage);
}

void EventRegistry::remove(Stage* pStage)
{
  m_StageList.remove(pStage);
}

void EventRegistry::keyEvent(KeyEvent* pEvent)
{
  iterator stage, sEnd = end();
  for (stage = begin(); stage != sEnd; ++stage) {
    (*stage)->keyEvent(pEvent);
  }
}

void EventRegistry::mousePressEvent(MouseEvent* pEvent)
{
  iterator stage, sEnd = end();
  for (stage = begin(); stage != sEnd; ++stage) {
    (*stage)->mousePressEvent(pEvent);
  }
}

void EventRegistry::mouseReleaseEvent(MouseEvent* pEvent)
{
  iterator stage, sEnd = end();
  for (stage = begin(); stage != sEnd; ++stage) {
    (*stage)->mouseReleaseEvent(pEvent);
  }
}

void EventRegistry::mouseMoveEvent(MouseEvent* pEvent)
{
  iterator stage, sEnd = end();
  for (stage = begin(); stage != sEnd; ++stage) {
    (*stage)->mouseMoveEvent(pEvent);
  }
}

