//===- Painter.cpp --------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Painter.h>
#include <Triangle/Space.h>
#include <Triangle/Model.h>
#include <Triangle/Line.h>
#include <Triangle/DrawLine.h>
#include <Triangle/Triangle.h>
#include <Triangle/DrawTriangle.h>
#include <Triangle/ModelToVertex.h>
#include <Triangle/FrameBuffer.h>
#include <Triangle/Color.h>
#include <Triangle/ColorIterator.h>
#include <Triangle/Transformation.h>
#include <Triangle/Projection.h>
#include <Triangle/ManagedStatic.h>

#include <cmath>
#include <cassert>
#include <algorithm>

using namespace luba;

static ManagedStatic<Transformation> g_Trans;
static ManagedStatic<Projection> g_Proj;

//===----------------------------------------------------------------------===//
// Painter
//===----------------------------------------------------------------------===//
Painter::Painter(FrameBuffer& pFB)
  : m_FB(pFB) {
}

bool Painter::draw(const Vertex& pVertex) const
{
  m_FB.setColor(pVertex.x(), pVertex.y(), pVertex.z(), pVertex.color());
  return true;
}

bool Painter::draw(const Line& pLine) const
{
  DrawLine drawer(pLine.front(), pLine.rear());

  if (0 == drawer.distance())
    return true;
  DrawLine::const_iterator pixel, pEnd = drawer.end();
  for (pixel = drawer.begin(); pixel != pEnd; pixel.next()) {
    draw(*pixel);
  }

  return true;
}

bool Painter::drawHorizon(const Vertex& pLeft, const Vertex& pRight) const
{
  assert(pLeft.y() == pRight.y());
  DrawLine drawer(pLeft, pRight);
  DrawLine::const_iterator pixel, pEnd = drawer.end();
  for (pixel = drawer.begin(); pixel != pEnd; pixel.next()) {
    draw(*pixel);
  }
  return true;
}

bool Painter::draw(const Triangle& pTriangle) const
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
        drawHorizon(*left, *right);
        ++scan_y;
      }
      right = up_edge.begin();
    }

    while (scan_y != long_edge.end()->y()) {
      while (scan_y != left.y())
        left.next();
      while (scan_y != right.y())
        right.next();
      drawHorizon(*left, *right);
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
      drawHorizon(*left, *right);
      ++scan_y;
    }

    if (up_edge.begin().y() != up_edge.end().y()) {
      left = up_edge.begin();

      while (scan_y != long_edge.end()->y()) {
        while (scan_y != left.y())
          left.next();
        while (scan_y != right.y())
          right.next();
        drawHorizon(*left, *right);
        ++scan_y;
      }
    }
    else {
      drawHorizon(*up_edge.begin(), *up_edge.end());
    }
    return true;
  }
  return true;
}

bool Painter::draw(const Space& pSpace, const Camera& pCamera, Model& pModel, bool pSolid) const
{
  if (!Model::self().isValid())
    return false;

  m_FB.clear();
  g_Trans->setSpace(pSpace);
  g_Proj->setDistance(pSpace.depth());

  for(int i=0; i<(int)Model::self().getObject()->numtriangles; ++i) {
    Vertex v1, v2, v3;
    ModelToVertex converter(Model::self());

    int fn = Model::self().getObject()->triangles[i].findex;

    int v  = Model::self().getObject()->triangles[i].vindices[0];
    int n  = Model::self().getObject()->triangles[i].nindices[0];
    int t  = Model::self().getObject()->triangles[i].tindices[0];
    converter.setConverter(v, n, fn, t);
    converter.getVertex(v1);

    v  = Model::self().getObject()->triangles[i].vindices[1];
    n  = Model::self().getObject()->triangles[i].nindices[1];
    t  = Model::self().getObject()->triangles[i].tindices[1];
    converter.setConverter(v, n, fn, t);
    converter.getVertex(v2);

    v  = Model::self().getObject()->triangles[i].vindices[2];
    n  = Model::self().getObject()->triangles[i].nindices[2];
    t  = Model::self().getObject()->triangles[i].tindices[2];
    converter.setConverter(v, n, fn, t);
    converter.getVertex(v3);

    vec3D facet_norm;
    facet_norm[0] = Model::self().getObject()->facetnorms[fn*3];
    facet_norm[1] = Model::self().getObject()->facetnorms[fn*3 + 1];
    facet_norm[2] = Model::self().getObject()->facetnorms[fn*3 + 2];
    facet_norm[3] = 1.0;

    mat4 matrix(pSpace.scale());
    matrix = g_Trans->matrix() * matrix;
    facet_norm = matrix * facet_norm;

    matrix = pCamera.matrix() * matrix;

    double value = facet_norm * pCamera.vpn();
    if (value > 0) { // back face culling
      // because my eyes direction is (0, 0, 1), the dot product > 0 is 
      // back face.
      continue;
    }

    v1.coord() = matrix * v1.coord();
    v2.coord() = matrix * v2.coord();
    v3.coord() = matrix * v3.coord();

    Vertex p1(v1), p2(v2), p3(v3);
    mat4 P = g_Proj->matrix();
    p1.coord() = P * v1.coord();
    p2.coord() = P * v2.coord();
    p3.coord() = P * v3.coord();

    p1.coord() /= p1.coord().w();
    p2.coord() /= p2.coord().w();
    p3.coord() /= p3.coord().w();

    p1.coord() = pSpace.translate() * p1.coord();
    p2.coord() = pSpace.translate() * p2.coord();
    p3.coord() = pSpace.translate() * p3.coord();

    Triangle tri(p1, p2, p3);
    Line l1(tri.v3(), tri.v2());
    Line l2(tri.v3(), tri.v1());
    Line l3(tri.v2(), tri.v1());

    draw(l1);
    draw(l2);
    draw(l3);

    if (pSolid) {
      draw(tri);
    }
  }

  return true;
}

