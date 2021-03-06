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
#include <Triangle/Image.h>
#include <Triangle/RenderEvents.h>
#include <Triangle/BumpMap.h>
#include <Support/ManagedStatic.h>

#include <cmath>
#include <cassert>
#include <algorithm>


#include <iostream>
using namespace std;
using namespace luba;

static ManagedStatic<Transformation> g_Trans;
static ManagedStatic<Projection> g_Proj;
static ManagedStatic<RenderEvents> g_Render;

//===----------------------------------------------------------------------===//
// Painter
//===----------------------------------------------------------------------===//
Painter::Painter(FrameBuffer& pFB, const Camera& pCamera, const Light& pLight)
  : m_FB(pFB), m_Camera(pCamera), m_Light(pLight) {
}

/**
 *  Draw a vertex
 */
bool Painter::draw(const Vertex& pVertex, const Material& pMaterial) const
{
  if (pVertex.x() > m_FB.getWidth() || pVertex.y() > m_FB.getHeight())
    return true;

  if (pVertex.x() < 0 || pVertex.y() < 0)
    return true;

  /// Texture mapping
  /// @{
  Color color;
  if (pMaterial.hasImage()) {
    switch (g_Render->filter()) {
      case Image::Nearest:
        color = pMaterial.image()->getColor<Image::Nearest>(
                             pVertex.texture().x(),
                             pVertex.texture().y());
        break;
      case Image::Linear:
        color = pMaterial.image()->getColor<Image::Linear>(
                             pVertex.texture().x(),
                             pVertex.texture().y());
        break;
    }
  }
  /// @}

  /// Bump mapping
  /// @{
  BumpMap::Norm norm;
  if (Model::self().bumpMap().isOpened()) {
    norm = Model::self().bumpMap().getNorm(pVertex.texture().x(),
                                           pVertex.texture().y());
//    norm.normalize();
  }
  /// @}

  /// Lighting
  /// @{
  if (m_Light.isTurnOn()) {
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
  
    vec3 N(pVertex.norm() + norm);
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
    color += (ambient + diffuse + specular);
  }
  /// }@

  if (color.r() > 1.0) color.r() = 1.0;
  if (color.r() < -1.0) color.r() = -1.0;
  if (color.g() > 1.0) color.g() = 1.0;
  if (color.g() < -1.0) color.g() = -1.0;
  if (color.b() > 1.0) color.b() = 1.0;
  if (color.b() < -1.0) color.b() = -1.0;

  m_FB.setColor(pVertex.x(), pVertex.y(), pVertex.z(), color);
  return true;
}

/**
 *  draw a line
 */
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

/**
 *  draw a horizontal line
 */
bool Painter::drawHorizon(const Vertex& pLeft, const Vertex& pRight, const Material& pMaterial) const
{
  assert(pLeft.y() == pRight.y());
  Line horizon(pLeft, pRight);
  return draw(horizon, pMaterial);
}

/**
 *  Draw a triangle
 */
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

#ifdef LUBA_DEBUG
static unsigned int counter = 0;

#endif

static inline void start_model()
{
#ifdef LUBA_DEBUG
  if (0 == counter) {
    cerr << "<model>" << endl;
  }
#endif
}

static inline void end_model()
{
#ifdef LUBA_DEBUG
  if (0 == counter) {
    cerr << "</model>" << endl;
    ++counter;
  }
#endif
}

static inline void print_vertex(const Vertex& pVertex, const std::string& pName)
{
#ifdef LUBA_DEBUG
  if (0 == counter) {
    cerr << "  <vertex name=" << pName << "\">" << endl;
    cerr << "     coord:   " << pVertex.coord() << endl;
    cerr << "     texture: " << pVertex.texture() << endl;
    cerr << "  </vertex>" << endl;
  }
#endif
}

static inline void print_triangle(int i, const Vertex& pV1, const Vertex& pV2, const Vertex& pV3)
{
#ifdef LUBA_DEBUG
  if (0 == counter) {
    cerr << "  <triangle id=" << i << ">" << endl;
      print_vertex(pV1, "v1");
      print_vertex(pV2, "v2");
      print_vertex(pV3, "v3");
    cerr << "  </triangle>" << endl;
  }
#endif
}

/**
 *  Draw a model 
 */
bool Painter::draw(const Space& pSpace, Model& pModel) const
{
  if (!Model::self().isValid())
    return false;

  m_FB.clear();
  g_Trans->setSpace(pSpace);
  g_Proj->setDistance(1200);

  start_model();
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

      /// calculate facet normal
      /// @{
      vec3D facet_norm;
      int fn = Model::self().getObject()->triangles[group->triangles[i]].findex;
      facet_norm[0] = Model::self().getObject()->facetnorms[fn*3];
      facet_norm[1] = Model::self().getObject()->facetnorms[fn*3 + 1];
      facet_norm[2] = Model::self().getObject()->facetnorms[fn*3 + 2];
      facet_norm[3] = 0;

      facet_norm = g_Trans->rotate() * facet_norm;
      /// @}

      /// back face culling
      /// @{
      double value = facet_norm * m_Camera.vpn();

      // heuristic algorithm
      double threshold = (Projection::Parallel == g_Proj->mode())?0.0: 0.2;
      if (value > threshold) {
        // back face culling
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

      double p1w = p1.w();
      double p2w = p2.w();
      double p3w = p3.w();

      p1.coord() /= p1.w();
      p2.coord() /= p2.w();
      p3.coord() /= p3.w();

      p1.z() = v1.z();
      p2.z() = v2.z();
      p3.z() = v3.z();

      v1.coord() = pSpace.translate() * p1.coord();
      v2.coord() = pSpace.translate() * p2.coord();
      v3.coord() = pSpace.translate() * p3.coord();

      v1.w() = p1w;
      v2.w() = p2w;
      v3.w() = p3w;

      /// @}

      /// normal
      /// @{
      v1.norm() = (m_Camera.rotate() * g_Trans->rotate()) * v1.norm();
      v2.norm() = (m_Camera.rotate() * g_Trans->rotate()) * v2.norm();
      v3.norm() = (m_Camera.rotate() * g_Trans->rotate()) * v3.norm();
      /// @}

      Triangle tri(v1, v2, v3);
      print_triangle(i, tri.v1(), tri.v2(), tri.v3());

      CalculateLOD(tri, material);

      Line l1(tri.v3(), tri.v2());
      Line l2(tri.v3(), tri.v1());
      Line l3(tri.v2(), tri.v1());

      draw(l1, material);
      draw(l2, material);
      draw(l3, material);

      if (RenderEvents::None != g_Render->state()) {
        draw(tri, material);
      }
    }
    group = group->next;
  }
  end_model();
  return true;
}

void Painter::CalculateLOD(const Triangle& pTriangle, Material& pMaterial) const
{
  if (!pMaterial.hasImage())
    return;

  const Vertex& v1 = pTriangle.v1();
  const Vertex& v2 = pTriangle.v2();
  const Vertex& v3 = pTriangle.v3();
  double maxX = v1.x();
  if (maxX < v2.x()) maxX = v2.x();
  if (maxX < v3.x()) maxX = v3.x();

  double minX = v1.x();
  if (minX > v2.x()) minX = v2.x();
  if (minX > v3.x()) minX = v3.x();

  double maxY = v1.y();
  if (maxY < v2.y()) maxY = v2.y();
  if (maxY < v3.y()) maxY = v3.y();

  double minY = v1.y();
  if (minY > v2.y()) minY = v2.y();
  if (minY > v3.y()) minY = v3.y();

  double dX = ::fabs(maxX - minX);
  double dY = ::fabs(maxY - minY);

  double polygon = dX*dY;
  pMaterial.image()->setPolygonSize(polygon);

  double maxU = v1.u();
  if (maxU < v2.u()) maxU = v2.u();
  if (maxU < v3.u()) maxU = v3.u();

  double minU = v1.u();
  if (minU > v2.u()) minU = v2.u();
  if (minU > v3.u()) minU = v3.u();

  double maxV = v1.v();
  if (maxV < v2.v()) maxV = v2.v();
  if (maxV < v3.v()) maxV = v3.v();

  double minV = v1.v();
  if (minV > v2.v()) minV = v2.v();
  if (minV > v3.v()) minV = v3.v();

  double dU = ::fabs(maxU - minU);
  double dV = ::fabs(maxV - minV);
  double texture = dU*dV;
  pMaterial.image()->setTextureSize(texture);
}

