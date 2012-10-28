//===- Painter.cpp --------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#include <Triangle/Painter.h>
#include <Triangle/Model.h>
#include <Triangle/Line.h>
#include <Triangle/Vertex.h>
#include <Triangle/FrameBuffer.h>
#include <Triangle/Color.h>

using namespace luba;

#include <fstream>
using namespace std;

static ofstream log_file("log.text", ios::trunc);
//===----------------------------------------------------------------------===//
// Helper Function
//===----------------------------------------------------------------------===//
void luba::map(FrameBuffer& pFB, Coord& pCoord, unsigned int& pX, unsigned int& pY)
{
  pX = (pFB.getWidth() + (int)(pFB.getWidth() * pCoord.x)) >> 1;
  pY = (pFB.getHeight() + (int)(pFB.getHeight() * pCoord.y)) >> 1;
}

//===----------------------------------------------------------------------===//
// Painter
//===----------------------------------------------------------------------===//
inline bool Painter::draw(FrameBuffer& pFB,
                          unsigned int pX, unsigned int pY,
                          Color& pColor) const
{
  log_file << "    " << "<pix X=" << pX << " Y=" << pY << ">" << endl;
  pFB.setColor(pX, pY, pColor);
  return true;
}

inline bool
Painter::draw(FrameBuffer& pFB, Coord& pCoord, Color& pColor) const
{
  unsigned int x, y;
  map(pFB, pCoord, x, y);
  return draw(pFB, x, y, pColor);
}

bool Painter::draw(FrameBuffer& pFB, Vertex& pVertex) const
{
  Coord coord;
  pVertex.getCoord(coord);

  Color color;
  pVertex.getColor(color);

  return draw(pFB, coord, color);
}

bool Painter::draw(FrameBuffer& pFB, Line& pLine) const
{
  Coord front, rear;
  pLine.front().getCoord(front);
  pLine.rear().getCoord(rear);

  unsigned int x0, y0, x1, y1;
  map(pFB, front, x0, y0);
  map(pFB, rear, x1, y1);

  unsigned int tmp;
  if (x0 > x1) {
    // from left to right
    tmp = x1;
    x1 = x0;
    x0 = tmp;

    tmp = y1;
    y1 = y0;
    y0 = tmp;
  }

  log_file << "  " << "<line from (" << x0 << ", " << y0 << ") to (" << x1 << ", " << y1 << ")>" << endl;

  int dX = x1 - x0;
  int dY = y1 - y0;
  int D  = 2*dY - dX;

  int incrE = 2 * dY;
  int incrNE = 2 * (dY - dX);

  int x = x0;
  int y = y0;

  Color value;
  pLine.front().getColor(value);
  draw(pFB, x, y, value);

  while (x < x1) {
    if (D <= 0) {
      D += incrE;
      ++x;
    }
    else {
      D += incrNE;
      ++x;
      ++y;
    }
    draw(pFB, x, y, value);
  }
  log_file << "  " << "</line>" << endl;
}

bool Painter::draw(FrameBuffer& pFB, Model& pModel) const
{
  if (!Model::self().isValid())
    return false;

  log_file << "<model>" << endl;
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

    draw(pFB, l1);
    draw(pFB, l2);
    draw(pFB, l3);
  }

  log_file << "</model>" << endl;
  return true;
}

