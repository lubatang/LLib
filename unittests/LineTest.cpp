//===- LineTest.cpp -------------------------------------------------------===//
//
//                     The MCLinker Project
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "LineTest.h"
#include <Triangle/Vertex.h>
#include <Triangle/Space.h>
#include <Triangle/DrawLine.h>
#include <Triangle/Vectors.h>

#include <string>
#include <iostream>

using namespace std;
using namespace luba;
using namespace luba::test;


// Constructor can do set-up work for all test here.
LineTest::LineTest()
{
}

// Destructor can do clean-up work that doesn't throw exceptions here.
LineTest::~LineTest()
{
}

// SetUp() will be called immediately before each test.
void LineTest::SetUp()
{
}

// TearDown() will be called immediately after each test.
void LineTest::TearDown()
{
}

//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
TEST_F(LineTest, draw_line_xy)
{
  Vertex a, b;
  a.setCoord(0, 100, 0);
  b.setCoord(100, 0, 0);

  DrawLine draw(a, b);

  DrawLine::const_iterator pixel, pEnd = draw.end();
  unsigned int counter = 0;
  for (pixel = draw.begin(); pixel != pEnd; pixel.next()) {
    ++counter;
  }
  ASSERT_EQ(100, counter);
}

TEST_F(LineTest, draw_line_xyz)
{
  Vertex a, b;
  a.setCoord(0, 0, 0);
  b.setCoord(3, 0, 4); // steep on XY and XZ plane

  DrawLine draw(a, b);

  DrawLine::const_iterator pixel, pEnd = draw.end();
  unsigned int counter = 0;
  for (pixel = draw.begin(); pixel != pEnd; pixel.next()) {
    cerr << pixel->coord() << endl;
    ++counter;
  }
  ASSERT_EQ(3, counter);
  ASSERT_EQ(3, draw.distance());
}

TEST_F(LineTest, draw_line_xyz2)
{
  Vertex a, b;
  a.setCoord(0, 0, 0);
  b.setCoord(0, 16, 4); // steep on XY and XZ plane

  DrawLine draw(a, b);

  DrawLine::const_iterator pixel, pEnd = draw.end();
  unsigned int counter = 0;
  for (pixel = draw.begin(); pixel != pEnd; pixel.next()) {
    ++counter;
  }
  ASSERT_EQ(16, counter);
  ASSERT_EQ(16, draw.distance());
}

TEST_F(LineTest, draw_line_horizon)
{
  Vertex a, b;
  a.setCoord(15.6, 3, 20);
  b.setCoord(39.2, 3, 15);

  DrawLine draw(a, b);
  DrawLine::const_iterator pixel, pEnd = draw.end();

  pixel = draw.begin();
  ASSERT_EQ(15, pixel->x());
  ASSERT_EQ(3, pixel->y());
  ASSERT_EQ(24, draw.distance());
  pixel.next();
  pixel.next();
  pixel.next();
  ASSERT_EQ(18, pixel->x());
  ASSERT_EQ(3, pixel->y());
}

TEST_F(LineTest, draw_line_min)
{
  Vertex a, b;
  a.setCoord(0.1, 0, 0);
  b.setCoord(0.5, 0, 0);

  DrawLine draw(a, b);
  ASSERT_EQ(0, draw.distance());

  a.setCoord(0.9, 0, 0);
  b.setCoord(1.1, 0, 0);
  draw.setTerminals(a, b);
  ASSERT_EQ(1, draw.distance());

}

