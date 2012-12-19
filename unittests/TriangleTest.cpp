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
#include <algebra/algebra.h>

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
<<<<<<< HEAD
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

