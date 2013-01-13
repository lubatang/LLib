//===- Camera.cpp ---------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Camera.h>
#include <ostream>

using namespace luba;

#include <iostream>
using namespace std;
//===----------------------------------------------------------------------===//
// Camera
//===----------------------------------------------------------------------===//
Camera::Camera(const vec3& pVRP, const vec3& pVPN, const vec3& pVUP)
  : m_VRP(pVRP), m_VPN(pVPN), m_VUP(pVUP)
{
}

mat4 Camera::rotate() const
{
  vec3 n(m_VPN);
  n.normalize();

  vec3 u = CrossProduct(m_VUP, m_VPN).normalize();
  vec3 v = CrossProduct(n, u);

  return mat4(u.x(), u.y(), u.z(), 0.0,
              v.x(), v.y(), v.z(), 0.0,
              n.x(), n.y(), n.z(), 0.0,
                0.0,   0.0,   0.0, 1.0);
}

mat4 Camera::translate() const
{
  return mat4(1.0, 0.0, 0.0, -m_VRP.x(),
              0.0, 1.0, 0.0, -m_VRP.y(),
              0.0, 0.0, 1.0, -m_VRP.z(),
              0.0, 0.0, 0.0, 1.0);
}

mat4 Camera::matrix() const
{
  return (rotate() * translate());
}

//===----------------------------------------------------------------------===//
// namespace std
//===----------------------------------------------------------------------===//
std::ostream& std::operator << (std::ostream& s, const luba::Camera& pCamera)
{
  return s << pCamera.matrix();
}

