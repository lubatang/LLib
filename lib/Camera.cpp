//===- Camera.cpp ---------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Camera.h>
#include <ostream>

using namespace luba;

//===----------------------------------------------------------------------===//
// Camera
//===----------------------------------------------------------------------===//
Camera::Camera(const vec3& pPos, const vec3& pTarget, const vec3& pUp)
  : m_Pos(pPos), m_Target(pTarget), m_Up(pUp), m_VPN(pPos - pTarget)
{
}

mat4 Camera::rotate() const
{
  vec3 n(m_VPN);
  n.normalize();

  vec3 u = CrossProduct(m_Up, m_VPN).normalize();
  vec3 v = CrossProduct(n, u);

  return mat4(u.x(), u.y(), u.z(), 0.0,
              v.x(), v.y(), v.z(), 0.0,
              n.x(), n.y(), n.z(), 0.0,
                0.0,   0.0,   0.0, 1.0);
}

mat4 Camera::translate() const
{
  return mat4(1.0, 0.0, 0.0, -m_Pos.x(),
              0.0, 1.0, 0.0, -m_Pos.y(),
              0.0, 0.0, 1.0, -m_Pos.z(),
              0.0, 0.0, 0.0, 1.0);
}

const Camera& Camera::transform(Coord& pCoord) const
{
  vec3 n(m_VPN);
  n.normalize();

  vec3 u = CrossProduct(m_Up, m_VPN).normalize();
  vec3 v = CrossProduct(n, u);

  mat4 R(u.x(), u.y(), u.z(), -m_Pos.x(),
         v.x(), v.y(), v.z(), -m_Pos.y(),
         n.x(), n.y(), n.z(), -m_Pos.z(),
         0.0,     0.0,   0.0,        1.0);

  pCoord = R * pCoord;
  return *this;
}

//===----------------------------------------------------------------------===//
// namespace std
//===----------------------------------------------------------------------===//
std::ostream& std::operator << (std::ostream& s, const luba::Camera& pCamera)
{
  return s;
}
