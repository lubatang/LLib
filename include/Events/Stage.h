//===- Stage.h ------------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_STAGE_H
#define LUBA_STAGE_H
#include <string>

namespace luba {

class Stage
{
public:
  Stage();
  Stage(const std::string& pName);
  virtual ~Stage();

private:
  std::string m_Name;
};

} // namespace luba

#endif

