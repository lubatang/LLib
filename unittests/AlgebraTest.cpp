//===- AlgebraTest.cpp ----------------------------------------------------===//
//
//                     The MCLinker Project
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "AlgebraTest.h"
#include <Triangle/Vertex.h>
#include <Triangle/Vectors.h>

#include <string>
#include <iostream>

using namespace std;
using namespace luba;
using namespace luba::test;


// Constructor can do set-up work for all test here.
AlgebraTest::AlgebraTest()
{
}

// Destructor can do clean-up work that doesn't throw exceptions here.
AlgebraTest::~AlgebraTest()
{
}

// SetUp() will be called immediately before each test.
void AlgebraTest::SetUp()
{
}

// TearDown() will be called immediately after each test.
void AlgebraTest::TearDown()
{
}

//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
TEST_F(AlgebraTest, translate_test)
{
  Vertex v;
  v.x() = 50;
  v.y() = -50;
  v.z() = 0;

  translate(v.coord(), 50, 50, 50);

  ASSERT_EQ(100, v.x());
  ASSERT_EQ(0, v.y());
  ASSERT_EQ(50, v.z());
}

