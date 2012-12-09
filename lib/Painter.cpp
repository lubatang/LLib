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
#include <Triangle/ModelVertex.h>
#include <Triangle/FrameBuffer.h>
#include <Triangle/Color.h>
#include <Triangle/ColorIterator.h>

#include <cmath>
#include <algorithm>

using namespace luba;
using namespace std;

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

  double a, b, c;
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

  // maping to space
  Coord S, E, A, B, C;
  pSpace.map(v1, A[0], A[1], A[2]);
  pSpace.map(v2, B[0], B[1], B[2]);
  pSpace.map(v3, C[0], C[1], C[2]);

  if ((A[1] - B[1]) < 1 && (B[1] - C[1]) < 1)
    return true;

  if (fabs(A[0] - B[0]) < 1 && fabs(B[0] - C[0]) < 1)
    return true;

  float dx1, dx2, dx3, dz1, dz2, dz3;
  Color dc1, dc2, dc3;
  dx1 = (v1[0] - v3[0])/(v1[1] - v3[1]); // C -> A
  dz1 = (v1[2] - v3[2])/(v1[1] - v3[1]); // C -> A
  if ((A[1] -C[1]) > 0) {
    dc1.r = (c1.r - c3.r)/(A[1] - C[1]);
    dc1.g = (c1.g - c3.g)/(A[1] - C[1]);
    dc1.b = (c1.b - c3.b)/(A[1] - C[1]);
  }
  else
    dc1.r = dc1.g = dc1.b = 0;

  dx2 = (v2[0] - v3[0])/(v2[1] - v3[1]); // C -> B
  dz2 = (v2[2] - v3[2])/(v2[1] - v3[1]); // C -> B
  if ((B[1] - C[1]) > 0) {
    dc2.r = (c2.r - c3.r)/(B[1] - C[1]);
    dc2.g = (c2.g - c3.g)/(B[1] - C[1]);
    dc2.b = (c2.b - c3.b)/(B[1] - C[1]);
  }
  else
    dc2.r = dc2.g = dc2.b = 0;

  dx3 = (v1[0] - v2[0])/(v1[1] - v2[1]); // B -> A
  dz3 = (v1[2] - v2[2])/(v1[1] - v2[1]); // B -> A
  if ((A[1] - B[1]) > 0) {
    dc3.r = (c1.r - c2.r)/(A[1] - B[1]);
    dc3.g = (c1.g - c2.g)/(A[1] - B[1]);
    dc3.b = (c1.b - c2.b)/(A[1] - B[1]);
  }
  else
    dc3.r = dc3.g = dc3.b = 0;

  Color SC, EC;
  SC = c3;
  EC = c3;
  S = E = C;
  if (dx2 > dx1) { // B is in the right
    while (S[1] < B[1]) { // C -> B
      ColorIterator line(SC, EC, E[0] - S[0]);
      double dz = ((E[0] - S[0]) > 0)?(E[2] - S[2])/(E[0] - S[0]):0;
      double e = E[0], y = S[1], z = S[2];
      for (double x = S[0]; x < e; ++x, line.next()) {
        m_FB.setColor(x, y, z, *line);
        z += dz;
      }
      ++S[1];
      ++E[1];
      S[0] += dx1;
      S[2] += dz1;
      E[0] += dx2;
      E[2] += dz2;
      SC.r += dc1.r; SC.g += dc1.g; SC.b += dc1.b;
      EC.r += dc2.r; EC.g += dc2.g; EC.b += dc2.b;
    }
    E = B;
    EC = c2;
    while (S[1] < A[1]) {
      ColorIterator line(SC, EC, E[0] - S[0]);
      double dz = ((E[0] - S[0])>0)?(E[2] - S[2])/(E[0] - S[0]):0;
      double e = E[0], y = S[1], z = S[2];
      for (double x = S[0]; x < e; ++x, line.next()) {
        m_FB.setColor(x, y, z, *line);
        z += dz;
      }
      ++S[1];
      ++E[1];
      S[0] += dx1;
      S[2] += dz1;
      E[0] += dx3;
      E[2] += dz3;
      SC.r += dc1.r; SC.g += dc1.g; SC.b += dc1.b;
      EC.r += dc3.r; EC.g += dc3.g; EC.b += dc3.b;
    }
  }
  else { // B is in the left
    // down half
    while (S[1] < B[1]) {
      ColorIterator line(SC, EC, E[0] - S[0]);
      double dz = ((E[0] - S[0])>0)? (E[2] - S[2])/(E[0] - S[0]):0;
      double e = E[0], y = S[1], z = S[2];
      for (double x = S[0]; x < e; ++x, line.next()) {
        m_FB.setColor(x, y, z, *line);
        z += dz;
      }
      ++S[1];
      ++E[1];
      S[0] += dx2;
      S[2] += dz2;
      E[0] += dx1;
      E[2] += dz1;
      SC.r += dc2.r; SC.g += dc2.g; SC.b += dc2.b;
      EC.r += dc1.r; EC.g += dc1.g; EC.b += dc1.b;
    }
    // top half
    S = B;
    SC = c2;
    while (S[1] < A[1]) {
      ColorIterator line(SC, EC, E[0] - S[0]);
      double dz = ((E[0] - S[0]) > 0)?(E[2] - S[2])/(E[0] - S[0]):0;
      double e = E[0], y = S[1], z = S[2];
      for (double x = S[0]; x < e; ++x, line.next()) {
        m_FB.setColor(x, y, z, *line);
        z += dz;
      }
      ++S[1];
      ++E[1];
      S[0] += dx3;
      S[2] += dz3;
      E[0] += dx1;
      E[2] += dz1;
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
    ModelVertex v1(v, n, fn, t);

    v  = Model::self().getObject()->triangles[i].vindices[1];
    n  = Model::self().getObject()->triangles[i].nindices[1];
    t  = Model::self().getObject()->triangles[i].tindices[1];
    ModelVertex v2(v, n, fn, t);

    v  = Model::self().getObject()->triangles[i].vindices[2];
    n  = Model::self().getObject()->triangles[i].nindices[2];
    t  = Model::self().getObject()->triangles[i].tindices[2];
    ModelVertex v3(v, n, fn, t);

    if (pSolid) {
      Triangle tri(v1, v2, v3);
      draw(pSpace, tri);

      Line l1(v1, v2);
      Line l2(v1, v3);
      Line l3(v2, v3);
      draw(pSpace, l1);
      draw(pSpace, l2);
      draw(pSpace, l3);
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

