// 3DGP_framework.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
#include <Triangle/Model.h>
#include <Triangle/Space.h>
#include <Triangle/Painter.h>
#include <Triangle/FrameBuffer.h>

using namespace luba;

//===----------------------------------------------------------------------===//
// Helper Functions
//===----------------------------------------------------------------------===//
static void help()
{
  std::cout << "Usage:\n"
            << "  lviewer -f [input object file]\n";
}

static void error(const std::string& pMesg)
{
  std::cerr << "Error: ";
  std::cerr << pMesg << std::endl;
  exit(0);
}

//////////////////////////////////////////////////////////////////////////
// render
//  This is the rendering function
//////////////////////////////////////////////////////////////////////////
void render(const LCamera cam, const LLight lit, FrameBuffer* pFB, RENDER_MODE pRenderMode)
{  
  vec3 pos,target,up;
  cam.getVectors(pos, target, up);
  // how to use: just like the input of gluLookAt
  //   camera position (   pos.n[0],    pos.n[1],   pos.n[2] )   initial value: (0,250,0)
  //   camera target   (target.n[0], target.n[1],target.n[2] )   initial value: (0,249,0)
  //   camera upVector (    up.n[0],     up.n[1],    up.n[2] )   initial value: (1,0,0)

  vec3 lightS;
  lightS = lit.getPos();

  // Connects MVC pattern
  //   Model   : Model
  //   View    : Space
  //   Control : Painter
  Space space(800, 800, 800);
  space.setOrigin(100, 100, 0);
  Painter painter(*pFB);
  bool solid = (pRenderMode == SOLID);
  static bool prev_solid = true;
  if (prev_solid != solid) {
    pFB->clear();
    prev_solid = solid;
  }
  if (!painter.draw(space, Model::self(), solid)) {
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
  int option;
  while ((option = getopt(argc, argv, "f:?h")) != -1) {
    switch (option) {
      case 'f': {
        file = std::string(optarg);
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

  if (file.empty())
    error("no inputs.");

  // initialize Model.
  Model::Initialize(argc, argv, file);

  //get into a rendering loop
  initAndRunLViewer(1000, 1000, render, init);

  return 0;
}

