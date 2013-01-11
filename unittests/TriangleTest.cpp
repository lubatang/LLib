//===- TriangleTest.cpp ----------------------------------------------------===//
//
//                     The MCLinker Project
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "TriangleTest.h"
#include <Triangle/Vertex.h>
#include <Triangle/Space.h>
#include <Triangle/DrawTriangle.h>
#include <Triangle/Vectors.h>

#include <string>
#include <iostream>

using namespace std;
using namespace luba;
using namespace luba::test;


// Constructor can do set-up work for all test here.
TriangleTest::TriangleTest()
{
}

// Destructor can do clean-up work that doesn't throw exceptions here.
TriangleTest::~TriangleTest()
{
}

// SetUp() will be called immediately before each test.
void TriangleTest::SetUp()
{
}

// TearDown() will be called immediately after each test.
void TriangleTest::TearDown()
{
}

//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
TEST_F(TriangleTest, has_area_test)
{
  Vertex v1, v2, v3;
  v1.setCoord(0, 2, 0);
  v2.setCoord(2, 0, 0);
  v3.setCoord(0, 0, 0);

  Triangle t1(v1, v2, v3);

  ASSERT_TRUE(t1.v1().x() == v1.x());
  ASSERT_TRUE(t1.v1().y() == v1.y());
  ASSERT_TRUE(t1.v1().z() == v1.z());

  ASSERT_TRUE(t1.v2().x() == v2.x());
  ASSERT_TRUE(t1.v2().y() == v2.y());
  ASSERT_TRUE(t1.v2().z() == v2.z());

  ASSERT_TRUE(t1.v3().x() == v3.x());
  ASSERT_TRUE(t1.v3().y() == v3.y());
  ASSERT_TRUE(t1.v3().z() == v3.z());

  DrawTriangle drawer(t1.v1(), t1.v2(), t1.v3());
  ASSERT_TRUE(drawer.hasArea());

  v1.setCoord(2, 2, 0);
  v2.setCoord(2, 0, 0);
  v3.setCoord(1.5, 0, 0);
  Triangle t2(v1, v2, v3);
  DrawTriangle drawer2(t2.v1(), t2.v2(), t2.v3());
  ASSERT_FALSE(drawer2.hasArea());
}

TEST_F(TriangleTest, begin_iterator_test)
{
  Vertex v1, v2, v3;
  v1.setCoord(0, 4, 0);
  v2.setCoord(2, 2, 0);
  v3.setCoord(0, 0, 0);

  Triangle t(v1, v2, v3);
  DrawTriangle drawer(t.v1(), t.v2(), t.v3());
  ASSERT_TRUE(drawer.hasArea());

  DrawTriangle::const_iterator horizon, hEnd = drawer.end();
  for (horizon = drawer.begin(); horizon != hEnd; horizon.next()) {
    DrawLine::const_iterator pixel, pEnd = horizon->end();
    //cerr << "line: " << (horizon->begin())->coord() << " -> " << (horizon->end())->coord() << endl;
    pixel = horizon->begin();
    while (pixel != pEnd) {
      //cerr << "  " << pixel->coord() << endl;
      pixel.next();
    }
  }
}


TEST_F(TriangleTest, left_triangle_test)
{
  Vertex v1, v2, v3;
  v1.setCoord(2, 4, 0);
  v2.setCoord(0, 2, 0);
  v3.setCoord(2, 0, 0);

  Triangle t(v1, v2, v3);
  DrawTriangle drawer(t.v1(), t.v2(), t.v3());
  ASSERT_TRUE(drawer.hasArea());

  DrawTriangle::const_iterator horizon, hEnd = drawer.end();
  for (horizon = drawer.begin(); horizon != hEnd; horizon.next()) {
    DrawLine::const_iterator pixel, pEnd = horizon->end();
    // cerr << "line: " << (horizon->begin())->coord() << " -> " << (horizon->end())->coord() << endl;
    pixel = horizon->begin();
    while (pixel != pEnd) {
      // cerr << "  " << pixel->coord() << endl;
      pixel.next();
    }
  }
}

TEST_F(TriangleTest, up_isoceles_triangle_test)
{
  Vertex v1, v2, v3;
  v1.setCoord(3, 2, 0);
  v2.setCoord(2, 0, 0);
  v3.setCoord(4, 0, 0);

  Triangle t(v1, v2, v3);
  DrawTriangle drawer(t.v1(), t.v2(), t.v3());
   // cerr << "triangle: " << t.v1().coord() << ", " << t.v2().coord() << ", " << t.v3().coord() << endl; 
  ASSERT_TRUE(drawer.hasArea());

  DrawTriangle::const_iterator horizon, hEnd = drawer.end();
  for (horizon = drawer.begin(); horizon != hEnd; horizon.next()) {
    DrawLine::const_iterator pixel, pEnd = horizon->end();
    // cerr << "line: " << (horizon->begin())->coord() << " -> " << (horizon->end())->coord() << endl;
    pixel = horizon->begin();
    while (pixel != pEnd) {
      // cerr << "  " << pixel->coord() << endl;
      pixel.next();
    }
  }
}

TEST_F(TriangleTest, down_isoceles_triangle_test)
{
  Vertex v1, v2, v3;
  v1.setCoord(3, 4, 0);
  v2.setCoord(2, 6, 0);
  v3.setCoord(4, 6, 0);

  Triangle t(v1, v2, v3);
  DrawTriangle drawer(t.v1(), t.v2(), t.v3());
  // cerr << "triangle: " << t.v1().coord() << ", " << t.v2().coord() << ", " << t.v3().coord() << endl; 
  ASSERT_TRUE(drawer.hasArea());

  DrawTriangle::const_iterator horizon, hEnd = drawer.end();
  for (horizon = drawer.begin(); horizon != hEnd; horizon.next()) {
    DrawLine::const_iterator pixel, pEnd = horizon->end();
    // cerr << "line: " << (horizon->begin())->coord() << " -> " << (horizon->end())->coord() << endl;
    pixel = horizon->begin();
    while (pixel != pEnd) {
      // cerr << "  " << pixel->coord() << endl;
      pixel.next();
    }
  }
}

TEST_F(TriangleTest, special_triangle_test)
{
  Vertex v1, v2, v3;
  v1.setCoord(900, 747.214, 400);
  v2.setCoord(747.214, 500, 0);
  v3.setCoord(900, 252.786, 400);

  Triangle t(v1, v2, v3);
  DrawTriangle drawer(t.v1(), t.v2(), t.v3());
  ASSERT_TRUE(drawer.hasArea());

  DrawTriangle::const_iterator horizon, hEnd = drawer.end();
  for (horizon = drawer.begin(); horizon != hEnd; horizon.next()) {
    DrawLine::const_iterator pixel, pEnd = horizon->end();
    pixel = horizon->begin();
    while (pixel != pEnd) {
      pixel.next();
    }
  }
}

TEST_F(TriangleTest, order_test)
{
  Vertex v1, v2, v3;
  v1.setCoord(1.1, 6.2, 0);
  v2.setCoord(1.1, 3.2, 0);
  v3.setCoord(7.2, 3.2, 0);

  Triangle t1(v1, v2, v3);
  Triangle t2(v2, v1, v3);
  ASSERT_TRUE(t1.v1().coord() == t2.v1().coord());
  ASSERT_TRUE(t1.v2().coord() == t2.v2().coord());
  ASSERT_TRUE(t1.v3().coord() == t2.v3().coord());

  Triangle t3(v3, v2, v1);
  ASSERT_TRUE(t3.v1().coord() == t2.v1().coord());
  ASSERT_TRUE(t3.v2().coord() == t2.v2().coord());
  ASSERT_TRUE(t3.v3().coord() == t2.v3().coord());
}

TEST_F(TriangleTest, raster)
{
  
  Vertex p1, p2, p3;
  p1.setCoord(99.1751, 904.583, 500);
  p2.setCoord(899.173, 904.579, 500);
  p3.setCoord(899.15, 104.632, 500);

  Triangle pTriangle(p1, p2, p3);

  const Vertex& v1 = pTriangle.v1();
  const Vertex& v2 = pTriangle.v2();
  const Vertex& v3 = pTriangle.v3();

  if ((v1.y() - v2.y()) < 1 && (v2.y() - v3.y()) < 1) {
    //cerr << "a horizontal line. v1.y must >= v2.y, and v2.y must >= v3.y" << endl;
    return;
  }

  if (fabs(v1.x() - v2.x()) < 1 && fabs(v2.x() - v3.x()) < 1) {
    //cerr << "a vertical line." << endl;
    return;
  }

  float dx1 = (v1.x() - v3.x())/(v1.y() - v3.y());
  float dx2 = (v2.x() - v3.x())/(v2.y() - v3.y());

  DrawLine long_edge(v3, v1);
  DrawLine down_edge(v3, v2);
  DrawLine up_edge(v2, v1);

  int scan_y = (int)v3.y();
/// Print All
  //cerr << "Long: " << long_edge.begin()->coord() << " to " << long_edge.end()->coord() << endl;
  DrawLine::const_iterator pixel, pEnd = long_edge.end();
  for (pixel = long_edge.begin(); pixel != pEnd; pixel.next()) {
    //cerr << "  " << pixel->coord() << endl;
  }
  //cerr << "Down: " << down_edge.begin()->coord() << " to " << down_edge.end()->coord() << endl;
  pEnd = down_edge.end();
  for (pixel = down_edge.begin(); pixel != pEnd; pixel.next()) {
    //cerr << "  " << pixel->coord() << endl;
  }
  //cerr << "Up  : " << up_edge.begin()->coord()   << " to " << up_edge.end()->coord()   << endl;
  pEnd = up_edge.end();
  for (pixel = up_edge.begin(); pixel != pEnd; pixel.next()) {
    //cerr << "  " << pixel->coord() << endl;
  }
///
  if (dx2 > dx1) { ///< v2 is in the right
    //cerr << "v2 is in the right" << endl;
    DrawLine::const_iterator left  = long_edge.begin();
    DrawLine::const_iterator right = down_edge.begin();

    if (down_edge.begin()->y() == down_edge.end()->y()) {
      //cerr << "down is horizon" << endl;
      ++scan_y;
      right = up_edge.begin();
    }
    else {
      //cerr << "down triangle" << endl;
      while (scan_y != down_edge.end()->y()) {
        while (scan_y != left.y())
          left.next();
        while (scan_y != right.y())
          right.next();
        //cerr << "\thorizon from " << left->coord() << " to " << right->coord() << endl;
        ++scan_y;
      }
      right = up_edge.begin();
    }

    //cerr << "up triangle" << endl;
    while (scan_y != long_edge.end()->y()) {
      while (scan_y != left.y())
        left.next();
      while (scan_y != right.y())
        right.next();
      //cerr << "\thorizon from " << left->coord() << " to " << right->coord() << endl;
      ++scan_y;
    }
  }
  else { ///< v2 is in the left
    //cerr << "v2 is in the left" << endl;
    DrawLine::const_iterator left  = down_edge.begin();
    DrawLine::const_iterator right = long_edge.begin();

    //cerr << "down triangle" << endl;
    while (scan_y != down_edge.end()->y()) {
      while (scan_y != left.y())
        left.next();
      while (scan_y != right.y())
        right.next();
      //cerr << "\thorizon from " << left->coord() << " to " << right->coord() << endl;
      ++scan_y;
    }

    if (up_edge.begin().y() == up_edge.end().y()) {
      //cerr << "up is horizon" << endl;
      return;
    }
    else {
      left = up_edge.begin();

      //cerr << "up triangle" << endl;
      while (scan_y != long_edge.end()->y()) {
        while (scan_y != left.y())
          left.next();
        while (scan_y != right.y())
          right.next();
        //cerr << "\thorizon from " << left->coord() << " to " << right->coord() << endl;
        ++scan_y;
      }
    }
  }
}

