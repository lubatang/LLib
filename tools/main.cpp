//===- main.cpp -----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//

#ifdef __APPLE__
//openGL related library
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

//the framework library
#include <framework.h>

//the OBJ model library
#include <GLM/glm.h>
#include <Triangle/Model.h>
#include <Triangle/Space.h>
#include <Triangle/Painter.h>
#include <Triangle/FrameBuffer.h>
#include <Triangle/Camera.h>

#include <unistd.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>

#include <gtest.h>

using namespace luba;

//===----------------------------------------------------------------------===//
// Helper Functions
//===----------------------------------------------------------------------===//
static void help()
{
  std::cout << "Usage:\n"
            << "  lviewer -f [input object file]\n\tor\n  lviewer -f [input object file] -b [bump map file]\n";
}

static void error(const std::string& pMesg)
{
  std::cerr << "Error: ";
  std::cerr << pMesg << std::endl;
  exit(0);
}

int unit_test( int argc, char* argv[] )
{
  testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}

//////////////////////////////////////////////////////////////////////////
// render
//  This is the rendering function
//////////////////////////////////////////////////////////////////////////
void render(const Camera& pCam, const Light& pLight, FrameBuffer* pFB)
{  
  // Connects MVC pattern
  //   Model   : Model
  //   View    : Space
  //   Control : Painter
  Space space(800, 800, 800);
  space.setOrigin(100, 100, 100);
  Painter painter(*pFB, pCam, pLight);
  if (!painter.draw(space, Model::self())) {
    error("cannot draw the model");
  }
}


//////////////////////////////////////////////////////////////////////////
// init()
//  This function will be called once when the program starts.
//////////////////////////////////////////////////////////////////////////
void init()
{
  //move the object to the origin
  //scale to -1~+1
  glmUnitize(Model::self().getObject());
  
  //calculate the vertex normals
  glmFacetNormals(Model::self().getObject());
  glmVertexNormals(Model::self().getObject() ,90.0);
}

int main(int argc, char ** argv)
{
  std::string file;
  std::string bump_map;
  int option;
  while ((option = getopt(argc, argv, "f:b:t?h")) != -1) {
    switch (option) {
      case 'f': {
        file = std::string(optarg);
        break;
      }
      case 'b': {
        bump_map = std::string(optarg);
        break;
      }
      case 't': {
        unit_test(argc, argv);
        exit(0);
        break;
      }
      case '?':
      case 'h':
      default: {
        help();
        exit(0);
      }
    }
  }

  if (file.empty()) {
    help();
    error("no inputs.");
  }

  // initialize Model.
  Model::Initialize(argc, argv, file, bump_map);

  //get into a rendering loop
  initAndRunLViewer(1000, 1000, render, init);

  return 0;
}

