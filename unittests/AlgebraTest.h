//===- AlgebraTest.h ------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef ALGEBRA_TEST_H
#define ALGEBRA_TEST_H

#include <gtest.h>


namespace luba {
namespace test {

class AlgebraTest : public ::testing::Test
{
public:
  // Constructor can do set-up work for all test here.
  AlgebraTest();

  // Destructor can do clean-up work that doesn't throw exceptions here.
  virtual ~AlgebraTest();

  // SetUp() will be called immediately before each test.
  virtual void SetUp();

  // TearDown() will be called immediately after each test.
  virtual void TearDown();
};

} // namespace of test
} // namespace of luba

#endif

