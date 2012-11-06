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
  m_FB.setColor(x, y, pColor);
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
    m_FB.setColor(pixel.x(), pixel.y(), *color);
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
  pSpace.map(v1, S.x, S.y, S.z);
  pSpace.map(v1, E.x, E.y, E.z);

  pSpace.map(v1, A.x, A.y, A.z);
  pSpace.map(v2, B.x, B.y, B.z);
  pSpace.map(v3, C.x, C.y, C.z);

  if ((unsigned int)A.y == (unsigned int)B.y && (unsigned int)B.y == (unsigned int)C.y)
    return true;

  float dx1, dx2, dx3;
  dx1 = (v3.x - v1.x)/(v1.y - v3.y); // A -> C
  dx2 = (v2.x - v1.x)/(v1.y - v2.y); // A -> B
  dx3 = (v3.x - v2.x)/(v2.y - v3.y); // B -> C

  Color color(255, 255, 0);
  if (dx2 > dx1) { // B is in the right
    while (S.y >= B.y) {
      unsigned int e = E.x, y = S.y;
      for (unsigned int x = S.x; x <= e; ++x)
        m_FB.setColor(x, y, color);
      --S.y;
      --E.y;
      S.x += dx1;
      E.x += dx2;
    }
    E = B;
    while (S.y >= C.y) {
      unsigned int e = E.x, y = S.y;
      for (unsigned int x = S.x; x <= e; ++x)
        m_FB.setColor(x, y, color);
      --S.y;
      --E.y;
      S.x += dx1;
      E.x += dx3;
    }
  }
  else { // B is in the left
    while (S.y >= B.y) {
      unsigned int e = E.x, y = S.y;
      for (unsigned int x = S.x; x <= e; ++x)
        m_FB.setColor(x, y, color);
      --S.y;
      --E.y;
      S.x += dx2;
      E.x += dx1;
    }
    S = B;
    while (S.y >= C.y) {
      unsigned int e = E.x, y = S.y;
      for (unsigned int x = S.x; x <= e; ++x)
        m_FB.setColor(x, y, color);
      --S.y;
      --E.y;
      S.x += dx3;
      E.x += dx1;
    }
  }
/**
  DrawTriangle drawer(pSpace, v1, v2, v3, c1, c2, c3);

  DrawTriangle::const_iterator horizon, hEnd = drawer.end();
  for (horizon = drawer.begin(); horizon != hEnd; horizon.next()) {

    ColorIterator color = ColorIterator(horizon.c1(),
                                        horizon.c2(),
                                        horizon->distance());
    DrawLine::const_iterator pixel, pEnd = horizon->end();
    for (pixel = horizon->begin(); pixel != pEnd; pixel.next(), color.next()) {
      m_FB.setColor(pixel.x(), pixel.y(), *color);
    }
  }
**/
  return true;
}

bool Painter::draw(const Space& pSpace, Model& pModel) const
{
  if (!Model::self().isValid())
    return false;

cerr << "<Model>" << endl;
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

    Triangle tri(v1, v2, v3);
    draw(pSpace, tri);

    Line l1(v1, v2);
    Line l2(v2, v3);
    Line l3(v1, v3);
    draw(pSpace , l1);
    draw(pSpace , l2);
    draw(pSpace , l3);

    draw(pSpace, v1);
    draw(pSpace, v2);
    draw(pSpace, v3);
  }

cerr << "</Model>" << endl;
  return true;
}

