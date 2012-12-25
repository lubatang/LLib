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
#include <algebra/mat4.h>

namespace luba {

class Translation : public Stage
{
public:
  Translation();

  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();

  const Translation& transform(Coord& pCoord) const;

  void keyEvent(KeyEvent* pEvent);
  void mouseMoveEvent(MouseEvent* pEvent);
  void mousePressEvent(MouseEvent* pEvent);

  bool active() const { return m_bActivated; }

  const mat4& matrix() const { return m_T; }

private:
  bool m_bActivated : 1;
  int m_OrgX;
  int m_OrgY;
  mat4 m_T;
};

} // namespace luba

namespace std {

std::ostream& operator << (std::ostream& s, const luba::Translation& pTranslation);

} // namespace std

#endif

