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
#include <Triangle/Triangle.h>
#include <Triangle/DrawLine.h>
#include <Triangle/Vertex.h>
#include <Triangle/FrameBuffer.h>
#include <Triangle/Color.h>
#include <Triangle/ColorIterator.h>

#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;
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

/**
  DrawTriangle drawer(pSpace, v1, v2, v3);

  DrawTriangle::const_iterator horizon, hEnd = drawer.end();
  for (horizon = drawer.begin(); horizon != hEnd; horizon.next()) {
    unsigned int x, xEnd = horizon->x2(), y = horizon->y();
    for (x = horizon->x1(); x < xEnd; ++x) {
      m_FB.setColor(x, y, );
    }
  }
**/
  return true;
}

bool Painter::draw(const Space& pSpace, Model& pModel) const
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

    Triangle tri(v1, v2, v3);
    draw(pSpace, tri);

    Line l1(v1, v2);
    Line l2(v2, v3);
    Line l3(v1, v3);
    draw(pSpace , l1);
    draw(pSpace , l2);
    draw(pSpace , l3);
  }

  return true;
}

