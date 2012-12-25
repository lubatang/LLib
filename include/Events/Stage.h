//===- Stage.h ------------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_STAGE_H
#define LUBA_STAGE_H
#include <string>

namespace luba {

class KeyEvent;
class MouseEvent;

class Stage
{
public:
  Stage();
  Stage(const std::string& pName);
  virtual ~Stage();

  virtual void keyEvent(KeyEvent* pEvent) = 0;
  virtual void mouseMoveEvent(MouseEvent* pEvent) = 0;
  virtual void mousePressEvent(MouseEvent* pEvent) = 0;

private:
  std::string m_Name;
};

} // namespace luba

#endif

