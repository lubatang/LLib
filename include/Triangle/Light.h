//===- Light.h ------------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_LIGHT_H
#define LUBA_LIGHT_H
#include <Events/Stage.h>
#include <Events/Event.h>
#include <Triangle/Vectors.h>

namespace luba {

class Light : public Stage
{
public:
  Light();

  Light(double pX, double pY, double pZ);

  void setPosition(double pX, double pY, double pZ);

  void getPosition(vec3& pPos);

  const vec3D& position() const { return m_Position; }
  vec3D&       position()       { return m_Position; }

  bool isActive() const { return m_bActive; }
  void setDirection(vec3& pDir);

  const vec3D& direction() const { return m_Direction; }
  vec3D        direction()       { return m_Direction; }

  void spot(double pX, double pY);
  void move(double pX, double pY);
  void roll(double pX, double pY);

  void keyEvent         (KeyEvent* pEvent);
  void mouseMoveEvent   (MouseEvent* pEvent);
  void mousePressEvent  (MouseEvent* pEvent);

  const vec3D& ambient() const  { return m_Ambient; }
  void setAmbient(const vec3D& pAmbient) { m_Ambient = pAmbient; }

  const vec3D& diffuse() const  { return m_Diffuse; }
  void setDiffuse(const vec3D& pDiffuse) { m_Diffuse = pDiffuse; }

  const vec3D& specular() const { return m_Specular; }
  void setSpecular(const vec3D& pSpecular) { m_Specular = pSpecular; }

  double getKC() const { return m_Kc; }
  double getKL() const { return m_Kl; }
  double getKQ() const { return m_Kq; }

  double setConstAttenuation    (double pKc) { m_Kc = pKc; }
  double setLinearAttenuation   (double pKl) { m_Kl = pKl; }
  double setQuadraticAttenuation(double pKq) { m_Kq = pKq; }

  double getSpotExpo() const { return m_SpotExpo; }
  void setSpotExpo(double pValue) { m_SpotExpo = pValue; }

private:
  enum State {
    MOVE   = 0,
    ROTATE = 1,
    SPOT   = 2,
    STATES = 3
  };


private:
  vec3D m_Position;
  vec3D m_Ambient;
  vec3D m_Diffuse;
  vec3D m_Specular;

  vec3D m_Direction;

  double m_Kc;
  double m_Kl;
  double m_Kq;

  double m_SpotExpo;

  bool m_bActive;

  int m_OrgX;
  int m_OrgY;

  unsigned int m_State;
};

} // namespace of luba

#endif

