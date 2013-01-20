//===- Stage.cpp ----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Events/Stage.h>
#include <Events/EventRegistry.h>

using namespace luba;

//===----------------------------------------------------------------------===//
// Stage
//===----------------------------------------------------------------------===//
Stage::Stage()
{
  EventRegistry::self().record(this);
}

Stage::Stage(const std::string& pName)
  : m_Name(pName) {
  EventRegistry::self().record(this);
}

Stage::~Stage()
{
  EventRegistry::self().remove(this);
}

