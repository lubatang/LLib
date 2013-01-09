//===- ImageTest.h --------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef IMAGE_TEST_H
#define IMAGE_TEST_H

#include <Triangle/Image.h>
#include <gtest.h>


namespace luba {
namespace test {

class ImageTest : public ::testing::Test
{
public:
  // Constructor can do set-up work for all test here.
  ImageTest();

  // Destructor can do clean-up work that doesn't throw exceptions here.
  virtual ~ImageTest();

  // SetUp() will be called immediately before each test.
  virtual void SetUp();

  // TearDown() will be called immediately after each test.
  virtual void TearDown();
};

} // namespace of test
} // namespace of luba

#endif

