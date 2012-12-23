//===- ProjectTest.cpp ----------------------------------------------------===//
//
//                     The MCLinker Project
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "ProjectTest.h"
#include <Triangle/Vertex.h>
#include <Triangle/Vectors.h>
#include <Triangle/Camera.h>

#include <string>

using namespace luba;
using namespace luba::test;


// Constructor can do set-up work for all test here.
ProjectTest::ProjectTest()
{
}

// Destructor can do clean-up work that doesn't throw exceptions here.
ProjectTest::~ProjectTest()
{
}

// SetUp() will be called immediately before each test.
void ProjectTest::SetUp()
{
}

// TearDown() will be called immediately after each test.
void ProjectTest::TearDown()
{
}

#include <iostream>
using namespace std;
//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
TEST_F(ProjectTest, camera_test)
{
  vec3 VRP(2.0, 1.0, 1.0);
  vec3 VPN(0.0, 0.0, 0.0);
  vec3 VUP(0.0, 1.0, 0.0);
  Camera c(VRP, VPN, VUP);

/**
  cerr << c.rotate() << endl;
  cerr << c.translate() << endl;

  cerr << c.transform() << endl;
**/
}

