//===- ImageTest.cpp ------------------------------------------------------===//
//
//                     The MCLinker Project
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "ImageTest.h"
#include <Triangle/Image.h>
#include <Triangle/BumpMap.h>

#include <string>

using namespace luba;
using namespace luba::test;


// Constructor can do set-up work for all test here.
ImageTest::ImageTest()
{
}

// Destructor can do clean-up work that doesn't throw exceptions here.
ImageTest::~ImageTest()
{
}

// SetUp() will be called immediately before each test.
void ImageTest::SetUp()
{
}

// TearDown() will be called immediately after each test.
void ImageTest::TearDown()
{
}

#include <iostream>
using namespace std;

//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
TEST_F(ImageTest, map_test)
{
  std::string path(TOPDIR);
  path += "/data/ppm/duckCM.ppm";

  Image image;
  ASSERT_TRUE(image.read(path, false));

  ASSERT_EQ(512, image.width());
  ASSERT_EQ(512, image.height());

  Color color1 = image.getColor<Image::Nearest>(1.0, 1.0);
  ASSERT_EQ(0.0, color1.b());
  Color color2 = image.getColor<Image::Nearest>(0.0, 0.0);
  ASSERT_EQ(0.0, color2.b());
}

TEST_F(ImageTest, bump_test)
{
  std::string path(TOPDIR);
  path += "/data/ppm/duckCM.ppm";
  BumpMap image;
  ASSERT_TRUE(image.read(path));

  ASSERT_EQ(512, image.width());
  ASSERT_EQ(512, image.height());

  vec3 color1 = image.getNorm(1.0, 1.0);
  ASSERT_EQ(0.0, color1[2]);
  vec3 color2 = image.getNorm(0.0, 0.0);
  ASSERT_EQ(0.0, color2[2]);
}

