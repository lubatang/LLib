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
#include <algebra/algebra.h>

#include <string>

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
TEST_F(LineTest, draw_line)
{
  Space s(100, 100, 100);
}

