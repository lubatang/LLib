//===- Projection.h -------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_PROJECTION_H
#define LUBA_PROJECTION_H
#include <iosfwd>
#include <Events/Stage.h>
#include <Events/KeyEvent.h>
#include <Events/MouseEvent.h>
#include <Triangle/Vertex.h>
#include <algebra/mat4.h>

namespace luba {

class Space;

class Projection : public Stage
{
public:
  enum Mode {
    Parallel    = 0,
    Perspective = 1,
    NumOfMode   = 2
  };

public:
  Projection();

  void keyEvent(KeyEvent* pEvent);

  unsigned int mode() const { return m_Mode; }

  void setMode(Mode pMode) { m_Mode = pMode; }

  double distance() const { return m_Distance; }

  void setDistance(double pDistance) { m_Distance = pDistance; }

  const Projection& transform(Coord& pCoord) const;

  const mat4& matrix() const { return m_P; }

private:
  unsigned int m_Mode;
  double m_Distance;

  mat4 m_P;
};

} // namespace luba

namespace std {

std::ostream& operator << (std::ostream& s, const luba::Projection& pProjection);

} // namespace std

#endif

