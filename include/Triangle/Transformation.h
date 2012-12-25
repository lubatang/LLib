//===- Transformation.h ---------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_TRANFORMATION_H
#define LUBA_TRANFORMATION_H
#include <iosfwd>
#include <Events/Stage.h>
#include <Events/KeyEvent.h>
#include <Events/MouseEvent.h>
#include <Triangle/Vertex.h>
#include <algebra/mat4.h>

namespace luba {

class Space;

class Transformation : public Stage
{
public:
  Transformation();

  void setSpace(const Space& pSpace) { m_pSpace = &pSpace; }

  void zoom(double pS);
  void move(double pX, double pY);
  void rotate(double pX, double pY);

  const Transformation& transform(Coord& pCoord) const;

  void keyEvent(KeyEvent* pEvent);
  void mouseMoveEvent(MouseEvent* pEvent);
  void mousePressEvent(MouseEvent* pEvent);

  bool active() const { return m_bActivated; }
  unsigned int state() const { return m_State; }

  const mat4& matrix() const { return m_T; }

private:
  enum State {
    MOVE   = 0,
    ROTATE = 1,
    ZOOM   = 2,
    STATES = 3
  };
private:
  bool m_bActivated : 1;
  int m_OrgX;
  int m_OrgY;
  mat4 m_T;
  unsigned int m_State;
  const Space* m_pSpace;
};

} // namespace luba

namespace std {

std::ostream& operator << (std::ostream& s, const luba::Transformation& pTransformation);

} // namespace std

#endif

