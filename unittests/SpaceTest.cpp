//===- SpaceTest.cpp ------------------------------------------------------===//
//
//                     The MCLinker Project
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "SpaceTest.h"
#include <Triangle/Vertex.h>
#include <Triangle/Vectors.h>
#include <Triangle/Camera.h>

#include <string>

using namespace luba;
using namespace luba::test;


// Constructor can do set-up work for all test here.
SpaceTest::SpaceTest()
{
}

// Destructor can do clean-up work that doesn't throw exceptions here.
SpaceTest::~SpaceTest()
{
}

// SetUp() will be called immediately before each test.
void SpaceTest::SetUp()
{
}

// TearDown() will be called immediately after each test.
void SpaceTest::TearDown()
{
}

#include <iostream>
using namespace std;

//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
TEST_F(SpaceTest, map_test)
{
  Space s(100, 100, 100);
  Vertex v;
  v.x() = 0.5;
  v.y() = -0.5;
  v.z() = 0;

  s.map(v);

  ASSERT_EQ(75, v.x());
  ASSERT_EQ(25, v.y());
  ASSERT_EQ(50, v.z());
}

