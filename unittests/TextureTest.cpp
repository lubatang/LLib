//===- TextureTest.cpp ----------------------------------------------------===//
//
//                     The MCLinker Project
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "TextureTest.h"
#include <Triangle/Texture.h>
#include <Triangle/Color.h>

using namespace luba;
using namespace luba::test;


// Constructor can do set-up work for all test here.
TextureTest::TextureTest()
{
}

// Destructor can do clean-up work that doesn't throw exceptions here.
TextureTest::~TextureTest()
{
}

// SetUp() will be called immediately before each test.
void TextureTest::SetUp()
{
}

// TearDown() will be called immediately after each test.
void TextureTest::TearDown()
{
}

//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
TEST_F(TextureTest, create_n_shrink)
{
  Texture texture;
  texture.resize(10, 10);
  Texture::iterator texel, tEnd = texture.end();
  Color color(0, 0, 0);
  Color addend(0.01, 0.01, 0.01);
  for (texel = texture.begin(); texel != tEnd; ++texel) {
    *texel = color;
    color += addend;
  }
  EXPECT_TRUE(Color(0.39, 0.39, 0.39) == texture.at(9, 3));
}

