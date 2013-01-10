//===- Painter.cpp --------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Painter.h>
#include <Triangle/Space.h>
#include <Triangle/Light.h>
#include <Triangle/Model.h>
#include <Triangle/Material.h>
#include <Triangle/Line.h>
#include <Triangle/DrawLine.h>
#include <Triangle/Triangle.h>
#include <Triangle/DrawTriangle.h>
#include <Triangle/ModelToVertex.h>
#include <Triangle/FrameBuffer.h>
#include <Triangle/Color.h>
#include <Triangle/Transformation.h>
#include <Triangle/Projection.h>
#include <Triangle/ManagedStatic.h>
#include <Triangle/Image.h>

#include <cmath>
#include <cassert>
#include <algorithm>


#include <iostream>
using namespace std;
using namespace luba;

static ManagedStatic<Transformation> g_Trans;
static ManagedStatic<Projection> g_Proj;

//===----------------------------------------------------------------------===//
// Painter
//===----------------------------------------------------------------------===//
Painter::Painter(FrameBuffer& pFB, const Camera& pCamera, const Light& pLight)
  : m_FB(pFB), m_Camera(pCamera), m_Light(pLight) {
}

bool Painter::draw(const Vertex& pVertex, const Material& pMaterial) const
{
  /// Lighting formula
  ///  L = ambient + att * spot * [ ambient + diffuse + specular ]
  double distance = vec3D(m_Light.position() - pVertex.coord()).length();
  double att = 1 / (m_Light.getKC() +
                    m_Light.getKL() * distance +
                    m_Light.getKQ() * distance * distance);

  vec3D L(m_Light.position() - pVertex.coord());
  L.normalize();

  vec3D D(m_Light.direction());
  D.normalize();
  double spot = pow((-L * D), m_Light.getSpotExpo());

  vec3D ambient(CoefProd(pMaterial.ambient(), m_Light.ambient()));
  ambient *= (1.0 + (att * spot));

  vec3 N(pVertex.norm());
  N.normalize();

  double diffuse_coef = L * N;
  if (diffuse_coef < 0)
    diffuse_coef = 0.0;

  vec3D diffuse(CoefProd(m_Light.diffuse(), pMaterial.diffuse()));
  diffuse *= (diffuse_coef * att * spot);

  vec3D V(vec3D(m_Camera.position()) - pVertex.coord()); 
  V.normalize();

  vec3D H(L + V);
  H.normalize();

  double poweree = H * N;
  if (poweree < 0.0)
    poweree = 0.0;
  double specular_coef = pow(poweree, pMaterial.shininess());
  vec3D specular(CoefProd(m_Light.specular(), pMaterial.specular()));
  specular *= (specular_coef * att * spot);

  Color color(ambient + diffuse + specular);

  if (color.r() > 1.0)
    color.r() = 1.0;

  if (color.g() > 1.0)
    color.g() = 1.0;

  if (color.b() > 1.0)
    color.b() = 1.0;

  m_FB.setColor(pVertex.x(), pVertex.y(), pVertex.z(), color);
  return true;
}

bool Painter::draw(const Line& pLine, const Material& pMaterial) const
{
  DrawLine drawer(pLine.front(), pLine.rear());

  if (0 == drawer.distance())
    return true;
  DrawLine::const_iterator pixel, pEnd = drawer.end();
  for (pixel = drawer.begin(); pixel != pEnd; pixel.next()) {
    draw(*pixel, pMaterial);
  }

  return true;
}

bool Painter::drawHorizon(const Vertex& pLeft, const Vertex& pRight, const Material& pMaterial) const
{
  assert(pLeft.y() == pRight.y());
  DrawLine drawer(pLeft, pRight);
  DrawLine::const_iterator pixel, pEnd = drawer.end();
  for (pixel = drawer.begin(); pixel != pEnd; pixel.next()) {
    draw(*pixel, pMaterial);
  }
  return true;
}

bool Painter::draw(const Triangle& pTriangle, const Material& pMaterial) const
{
  const Vertex& v1 = pTriangle.v1();
  const Vertex& v2 = pTriangle.v2();
  const Vertex& v3 = pTriangle.v3();

   
  if (int(v1.y()) == int(v3.y())) {
    // a horizontal line
    return true;
  }

  if (fabs(v1.x() - v2.x()) < 1 && fabs(v2.x() - v3.x()) < 1) {
    // a vertical line
    return true;
  }

  float dx1 = (v1.x() - v3.x())/(v1.y() - v3.y());
  float dx2 = (v2.x() - v3.x())/(v2.y() - v3.y());

  DrawLine long_edge(v3, v1);
  DrawLine down_edge(v3, v2);
  DrawLine up_edge(v2, v1);

  int scan_y = (int)v3.y();
  if (dx2 > dx1) { ///< v2 is in the right
    DrawLine::const_iterator left  = long_edge.begin();
    DrawLine::const_iterator right = down_edge.begin();

    if (down_edge.begin()->y() == down_edge.end()->y()) {
      ++scan_y;
      right = up_edge.begin();
    }
    else {
      while (scan_y != down_edge.end()->y()) {
        while (scan_y != left.y())
          left.next();
        while (scan_y != right.y())
          right.next();
        drawHorizon(*left, *right, pMaterial);
        ++scan_y;
      }
      right = up_edge.begin();
    }

    while (scan_y != long_edge.end()->y()) {
      while (scan_y != left.y())
        left.next();
      while (scan_y != right.y())
        right.next();
      drawHorizon(*left, *right, pMaterial);
      ++scan_y;
    }
    return true;
  }
  else { ///< v2 is in the left
    DrawLine::const_iterator left  = down_edge.begin();
    DrawLine::const_iterator right = long_edge.begin();

    while (scan_y != down_edge.end()->y()) {
      while (scan_y != left.y())
        left.next();
      while (scan_y != right.y())
        right.next();
      drawHorizon(*left, *right, pMaterial);
      ++scan_y;
    }

    if (up_edge.begin().y() != up_edge.end().y()) {
      left = up_edge.begin();

      while (scan_y != long_edge.end()->y()) {
        while (scan_y != left.y())
          left.next();
        while (scan_y != right.y())
          right.next();
        drawHorizon(*left, *right, pMaterial);
        ++scan_y;
      }
    }
    else {
      drawHorizon(*up_edge.begin(), *up_edge.end(), pMaterial);
    }
    return true;
  }
  return true;
}

bool Painter::draw(const Space& pSpace, Model& pModel, bool pSolid) const
{
  if (!Model::self().isValid())
    return false;

  m_FB.clear();
  g_Trans->setSpace(pSpace);
  g_Proj->setDistance(1200);

  GLMgroup* group = Model::self().getObject()->groups;
  while (NULL != group) {
    Material material(Model::self(), group->material);

    for (int i=0; i<(int)group->numtriangles; ++i) {
      Vertex v1, v2, v3;
      ModelToVertex converter(Model::self());

      /// get verteices of triangle
      /// @{
      int v  = Model::self().getObject()->triangles[group->triangles[i]].vindices[0];
      int n  = Model::self().getObject()->triangles[group->triangles[i]].nindices[0];
      int t  = Model::self().getObject()->triangles[group->triangles[i]].tindices[0];
      converter.setConverter(v, n, t);
      converter.getVertex(v1);

      v  = Model::self().getObject()->triangles[group->triangles[i]].vindices[1];
      n  = Model::self().getObject()->triangles[group->triangles[i]].nindices[1];
      t  = Model::self().getObject()->triangles[group->triangles[i]].tindices[1];
      converter.setConverter(v, n, t);
      converter.getVertex(v2);

      v  = Model::self().getObject()->triangles[group->triangles[i]].vindices[2];
      n  = Model::self().getObject()->triangles[group->triangles[i]].nindices[2];
      t  = Model::self().getObject()->triangles[group->triangles[i]].tindices[2];
      converter.setConverter(v, n, t);
      converter.getVertex(v3);
      /// @}

      /// backface culling
      /// @{
      vec3D facet_norm;
      int fn = Model::self().getObject()->triangles[group->triangles[i]].findex;
      facet_norm[0] = Model::self().getObject()->facetnorms[fn*3];
      facet_norm[1] = Model::self().getObject()->facetnorms[fn*3 + 1];
      facet_norm[2] = Model::self().getObject()->facetnorms[fn*3 + 2];

      facet_norm = g_Trans->rotate() * facet_norm;
      double value = facet_norm * m_Camera.vpn();

      if (value < 0) { // back face culling
        // because my eyes direction is (0, 0, 1), the dot product > 0 is 
        // back face.
        continue;
      }
      /// @}

      /// calculate coordination
      /// @{
      mat4 matrix(m_Camera.matrix() *
                  g_Trans->rotate() * g_Trans->scale() * g_Trans->trans() *
                  pSpace.scale());
      v1.coord() = matrix * v1.coord();
      v2.coord() = matrix * v2.coord();
      v3.coord() = matrix * v3.coord();

      Vertex p1(v1), p2(v2), p3(v3);
      p1.coord() = g_Proj->matrix() * p1.coord();
      p2.coord() = g_Proj->matrix() * p2.coord();
      p3.coord() = g_Proj->matrix() * p3.coord();

      p1.coord() /= p1.w();
      p2.coord() /= p2.w();
      p3.coord() /= p3.w();

      p1.z() = v1.z();
      p2.z() = v2.z();
      p3.z() = v3.z();

      v1.coord() = pSpace.translate() * p1.coord();
      v2.coord() = pSpace.translate() * p2.coord();
      v3.coord() = pSpace.translate() * p3.coord();

      /// @}

      /// normal
      /// @{
      v1.norm() = (m_Camera.rotate() * g_Trans->rotate()) * v1.norm();
      v2.norm() = (m_Camera.rotate() * g_Trans->rotate()) * v2.norm();
      v3.norm() = (m_Camera.rotate() * g_Trans->rotate()) * v3.norm();
      /// @}

      Triangle tri(v1, v2, v3);
      Line l1(tri.v3(), tri.v2());
      Line l2(tri.v3(), tri.v1());
      Line l3(tri.v2(), tri.v1());

      draw(l1, material);
      draw(l2, material);
      draw(l3, material);

      if (pSolid) {
        draw(tri, material);
      }
    }
    group = group->next;
  }

  return true;
}

