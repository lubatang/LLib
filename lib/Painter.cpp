//===- Painter.cpp --------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Painter.h>
#include <Triangle/Coord.h>
#include <Triangle/Space.h>
#include <Triangle/Model.h>
#include <Triangle/Line.h>
#include <Triangle/DrawLine.h>
#include <Triangle/Triangle.h>
#include <Triangle/DrawTriangle.h>
#include <Triangle/Vertex.h>
#include <Triangle/FrameBuffer.h>
#include <Triangle/Color.h>
#include <Triangle/ColorIterator.h>

#include <cmath>
#include <algorithm>

using namespace luba;

//===----------------------------------------------------------------------===//
// Painter
//===----------------------------------------------------------------------===//
Painter::Painter(FrameBuffer& pFB)
  : m_FB(pFB) {
}

inline bool
Painter::draw(const Space& pSpace, Coord& pCoord, Color& pColor) const
{
  unsigned int x, y, z;
  pSpace.map(pCoord, x, y, z);

  float a, b, c;
  pSpace.map(pCoord, a, b, c);
  m_FB.setColor(x, y, z, pColor);
  return true;
}

bool Painter::draw(const Space& pSpace, Vertex& pVertex) const
{
  Coord coord;
  pVertex.getCoord(coord);

  Color color;
  pVertex.getColor(color);

  return draw(pSpace, coord, color);
}

bool Painter::draw(const Space& pSpace, Line& pLine) const
{
  Coord v1, v2;
  pLine.front().getCoord(v1);
  pLine.rear().getCoord(v2);
  DrawLine drawer(pSpace, v1, v2);

  unsigned int distance = drawer.distance();
  if (0 == distance)
    return true;

  Color c1, c2;
  pLine.front().getColor(c1);
  pLine.rear().getColor(c2);

  ColorIterator color = ColorIterator(c1, c2, distance);
  DrawLine::const_iterator pixel, pEnd = drawer.end();
  for (pixel = drawer.begin(); pixel != pEnd; pixel.next(), color.next()) {
    m_FB.setColor(pixel.x(), pixel.y(), pixel.z(), *color);
  }

  return true;
}

bool Painter::draw(const Space& pSpace, Triangle& pTriangle) const
{
  Coord v1, v2, v3;
  pTriangle.v1().getCoord(v1);
  pTriangle.v2().getCoord(v2);
  pTriangle.v3().getCoord(v3);

  Color c1, c2, c3;
  pTriangle.v1().getColor(c1);
  pTriangle.v2().getColor(c2);
  pTriangle.v3().getColor(c3);

  Coord S, E, A, B, C;
  pSpace.map(v3, S.x, S.y, S.z);
  pSpace.map(v3, E.x, E.y, E.z);

  pSpace.map(v1, A.x, A.y, A.z);
  pSpace.map(v2, B.x, B.y, B.z);
  pSpace.map(v3, C.x, C.y, C.z);

  if ((unsigned int)A.y == (unsigned int)B.y && (unsigned int)B.y == (unsigned int)C.y)
    return true;

  float dx1, dx2, dx3, dz1, dz2, dz3;
  Color dc1, dc2, dc3;
  dx1 = (v1.x - v3.x)/(v1.y - v3.y); // C -> A
  dz1 = (v1.z - v3.z)/(v1.y - v3.y); // C -> A
  dc1.r = (c1.r - c3.r)/(A.y - C.y);
  dc1.g = (c1.g - c3.g)/(A.y - C.y);
  dc1.b = (c1.b - c3.b)/(A.y - C.y);

  dx2 = (v2.x - v3.x)/(v2.y - v3.y); // C -> B
  dz2 = (v2.z - v3.z)/(v2.y - v3.y); // C -> B
  dc2.r = (c2.r - c3.r)/(B.y - C.y);
  dc2.g = (c2.g - c3.g)/(B.y - C.y);
  dc2.b = (c2.b - c3.b)/(B.y - C.y);

  dx3 = (v1.x - v2.x)/(v1.y - v2.y); // B -> A
  dz3 = (v1.z - v2.z)/(v1.y - v2.y); // B -> A
  dc3.r = (c1.r - c2.r)/(A.y - B.y);
  dc3.g = (c1.g - c2.g)/(A.y - B.y);
  dc3.b = (c1.b - c2.b)/(A.y - B.y);

  Color SC, EC;
  SC = c3;
  EC = c3;
  if (dx2 > dx1) { // B is in the right
    while (S.y <= B.y) { // C -> B
      Color delta;
      delta.r = (EC.r - SC.r)/(E.x - S.x);
      delta.g = (EC.g - SC.g)/(E.x - S.x);
      delta.b = (EC.b - SC.b)/(E.x - S.x);
      float dz = (E.z - S.z)/(E.x - S.x);
      Color color = SC;
      unsigned int e = E.x, y = S.y, z = S.z;
      for (unsigned int x = S.x; x <= e; ++x) {
        m_FB.setColor(x, y, z, color);
        color.r += delta.r;
        color.g += delta.g;
        color.b += delta.b;
        z += dz;
      }
      ++S.y;
      ++E.y;
      S.x += dx1;
      S.z += dz1;
      E.x += dx2;
      E.z += dz2;
      SC.r += dc1.r; SC.g += dc1.g; SC.b += dc1.b;
      EC.r += dc2.r; EC.g += dc2.g; EC.b += dc2.b;
    }
    E = B;
    EC = c2;
    while (S.y <= A.y) {
      Color delta;
      delta.r = (EC.r - SC.r)/(E.x - S.x);
      delta.g = (EC.g - SC.g)/(E.x - S.x);
      delta.b = (EC.b - SC.b)/(E.x - S.x);
      float dz = (E.z - S.z)/(E.x - S.x);
      Color color = SC;
      unsigned int e = E.x, y = S.y, z = S.z;
      for (unsigned int x = S.x; x <= e; ++x) {
        m_FB.setColor(x, y, z, color);
        color.r += delta.r;
        color.g += delta.g;
        color.b += delta.b;
        z += dz;
      }
      ++S.y;
      ++E.y;
      S.x += dx1;
      S.z += dz1;
      E.x += dx3;
      E.z += dz3;
      SC.r += dc1.r; SC.g += dc1.g; SC.b += dc1.b;
      EC.r += dc3.r; EC.g += dc3.g; EC.b += dc3.b;
    }
  }
  else { // B is in the left
    while (S.y <= B.y) {
      Color delta;
      delta.r = (EC.r - SC.r)/(E.x - S.x);
      delta.g = (EC.g - SC.g)/(E.x - S.x);
      delta.b = (EC.b - SC.b)/(E.x - S.x);
      float dz = (E.z - S.z)/(E.x - S.x);
      Color color = SC;
      unsigned int e = E.x, y = S.y, z = S.z;
      for (unsigned int x = S.x; x <= e; ++x) {
        m_FB.setColor(x, y, z, color);
        color.r += delta.r;
        color.g += delta.g;
        color.b += delta.b;
        z += dz;
      }
      ++S.y;
      ++E.y;
      S.x += dx2;
      S.z += dz2;
      E.x += dx1;
      E.z += dz1;
      SC.r += dc2.r; SC.g += dc2.g; SC.b += dc2.b;
      EC.r += dc1.r; EC.g += dc1.g; EC.b += dc1.b;
    }
    S = B;
    SC = c2;
    while (S.y <= A.y) {
      Color delta;
      delta.r = (EC.r - SC.r)/(E.x - S.x);
      delta.g = (EC.g - SC.g)/(E.x - S.x);
      delta.b = (EC.b - SC.b)/(E.x - S.x);
      float dz = (E.z - S.z)/(E.x - S.x);
      Color color = SC;
      unsigned int e = E.x, y = S.y, z = S.z;
      for (unsigned int x = S.x; x <= e; ++x) {
        m_FB.setColor(x, y, z, color);
        color.r += delta.r;
        color.g += delta.g;
        color.b += delta.b;
        z += dz;
      }
      ++S.y;
      ++E.y;
      S.x += dx3;
      S.z += dz3;
      E.x += dx1;
      E.z += dz1;
      SC.r += dc3.r; SC.g += dc3.g; SC.b += dc3.b;
      EC.r += dc1.r; EC.g += dc1.g; EC.b += dc1.b;
    }
  }
  return true;
}

bool Painter::draw(const Space& pSpace, Model& pModel, bool pSolid) const
{
  if (!Model::self().isValid())
    return false;

  for(int i=0; i<(int)Model::self().getObject()->numtriangles; ++i) {
    int fn = Model::self().getObject()->triangles[i].findex;

    int v  = Model::self().getObject()->triangles[i].vindices[0];
    int n  = Model::self().getObject()->triangles[i].nindices[0];
    int t  = Model::self().getObject()->triangles[i].tindices[0];
    Vertex v1(v, n, fn, t);

    v  = Model::self().getObject()->triangles[i].vindices[1];
    n  = Model::self().getObject()->triangles[i].nindices[1];
    t  = Model::self().getObject()->triangles[i].tindices[1];
    Vertex v2(v, n, fn, t);

    v  = Model::self().getObject()->triangles[i].vindices[2];
    n  = Model::self().getObject()->triangles[i].nindices[2];
    t  = Model::self().getObject()->triangles[i].tindices[2];
    Vertex v3(v, n, fn, t);

    if (pSolid) {
      Triangle tri(v1, v2, v3);
      draw(pSpace, tri);
    }
    else {
      Line l1(v1, v2);
      Line l2(v1, v3);
      Line l3(v2, v3);
      draw(pSpace, l1);
      draw(pSpace, l2);
      draw(pSpace, l3);
    }
  }

  return true;
}

