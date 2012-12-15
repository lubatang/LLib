//===- SpaceTest.h --------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef SPACE_TEST_H
#define SPACE_TEST_H

#include <Triangle/Space.h>
#include <gtest.h>


namespace luba {
namespace test {

class SpaceTest : public ::testing::Test
{
public:
  // Constructor can do set-up work for all test here.
  SpaceTest();

  // Destructor can do clean-up work that doesn't throw exceptions here.
  virtual ~SpaceTest();

  // SetUp() will be called immediately before each test.
  virtual void SetUp();

  // TearDown() will be called immediately after each test.
  virtual void TearDown();
};

} // namespace of test
} // namespace of luba

#endif

