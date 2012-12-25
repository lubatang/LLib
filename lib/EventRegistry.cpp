//===- EventRegistry.cpp --------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Events/EventRegistry.h>
#include <Events/Stage.h>

using namespace luba;

//===----------------------------------------------------------------------===//
// EventRegistry
//===----------------------------------------------------------------------===//
void EventRegistry::record(Stage& pStage)
{
  m_StageList.push_back(&pStage);
}

