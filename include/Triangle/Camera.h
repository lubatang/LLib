//===- Camera.h -----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_CAMERA_H
#define LUBA_CAMERA_H
#include <iosfwd>
#include <Triangle/Vectors.h>
#include <Triangle/Vertex.h>

namespace luba {

class Camera
{
public:
  /// Camera - constructor
  /// @param pVRP [in] The view reference point
  /// @param pVPN [in] The view plane normal
  /// @param pVUP [in] The view up vector
  Camera(const vec3& pVRP, const vec3& pVPN, const vec3& pVUP);

  const vec3& vpn() const { return m_VPN; }
  vec3&       vpn()       { return m_VPN; }

  const vec3& position() const { return m_VRP; }
  vec3&       position()       { return m_VRP; }

  const vec3& up() const { return m_VUP; }
  vec3&       up()       { return m_VUP; }

  mat4 rotate() const;
  mat4 translate() const;
  mat4 matrix() const;

private:
  vec3 m_VRP;
  vec3 m_VPN;
  vec3 m_VUP;
};

} // namespace of luba

namespace std {
ostream& operator << (ostream& s, const luba::Camera& pCamera);
}

#endif

