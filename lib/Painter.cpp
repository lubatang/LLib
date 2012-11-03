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
#include <Triangle/Vertex.h>
#include <Triangle/FrameBuffer.h>
#include <Triangle/Color.h>

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
  DrawLine draw(pSpace, pLine);

  Color color;
  Color from, to;

  pLine.front().getColor(from);
  pLine.rear().getColor(to);

  DrawLine::const_iterator pixel = draw.begin(), pEnd = draw.end();
  while(pixel != pEnd) {
    color.r = pixel.z();
    color.g = pixel.z();
    color.b = pixel.z();
    m_FB.setColor(pixel.x(), pixel.y(), color);
    pixel.next();
  }
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

    Line l1(v1, v2);
    Line l2(v2, v3);
    Line l3(v3, v1);

    draw(pSpace, l1);
    draw(pSpace, l2);
    draw(pSpace, l3);
  }

  return true;
}

