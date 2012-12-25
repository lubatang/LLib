//===- Translation.h ------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_TRANSLATION_H
#define LUBA_TRANSLATION_H
#include <iosfwd>
#include <Events/Stage.h>
#include <Events/KeyEvent.h>
#include <Events/MouseEvent.h>
#include <Triangle/Vertex.h>

namespace luba {

class Translation : public Stage
{
public:
  Translation();

  const Translation& transform(Coord& pCoord) const;

  void keyEvent(KeyEvent* pEvent);
  void mouseMoveEvent(MouseEvent* pEvent);
  void mousePressEvent(MouseEvent* pEvent);
};

} // namespace luba

namespace std {

std::ostream& operator << (std::ostream& s, const luba::Translation& pTranslation);

} // namespace std

#endif

