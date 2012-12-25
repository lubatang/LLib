//===- Event.cpp ----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Events/Event.h>

using namespace luba;

//===----------------------------------------------------------------------===//
// Event
//===----------------------------------------------------------------------===//
Event::Event(Event::Type pType)
  : m_Type(pType) {
}

Event::~Event()
{
}

