// 3DGP_framework.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

GLMmodel *OBJ;
int screenWidth = 600;
int screenHeight = 400;

//////////////////////////////////////////////////////////////////////////
// render
//  This is the rendering function
//////////////////////////////////////////////////////////////////////////
void render(const LCamera cam, const LLight lit, FrameBuffer * colorBuff, RENDER_MODE renderingMode)
{  
  vec3 pos,target,up;
  cam.getVectors(pos, target, up);
  // how to use: just like the input of gluLookAt
  //   camera position (   pos.n[0],    pos.n[1],   pos.n[2] )   initial value: (0,250,0)
  //   camera target   (target.n[0], target.n[1],target.n[2] )   initial value: (0,249,0)
  //   camera upVector (    up.n[0],     up.n[1],    up.n[2] )   initial value: (1,0,0)
  
  vec3 lightS;
  lightS = lit.getPos();
  // how to use: it's just a position coordinate
  //   light position ( lightS.n[0], lightS.n[1], lightS.n[2] )   initial value: (100,100,0)
  
  colorBuff;//to assign pixel color
  //how to use: here is an example
  Color cc;
  for(int i=0;i<colorBuff->getWidth();i++){
    for(int j=0;j<colorBuff->getHeight();j++){
      cc.r = rand()%256;
      cc.g = rand()%256;
      cc.b = rand()%256;
      colorBuff->setColor(i,j,cc);
    }
  }
  
  renderingMode;
  //how to use: here is an example
  if(renderingMode==WIRE){
    //the rendering mode is WIRE
  }
  if(renderingMode==SOLID){
    //the rendering mode is SOLID
  }
  
  OBJ;
  //how to use: here is an example
  //traverse the triangle of the model (and render them urself)
  for(int i=0;i<(int)OBJ->numtriangles;i++){

    //the index of each vertices
    int indv1 = OBJ->triangles[i].vindices[0];
    int indv2 = OBJ->triangles[i].vindices[1];
    int indv3 = OBJ->triangles[i].vindices[2];

    //the index of each normals
    int indn1 = OBJ->triangles[i].nindices[0];
    int indn2 = OBJ->triangles[i].nindices[1];
    int indn3 = OBJ->triangles[i].nindices[2];

    //the index of each texture coordinates
    int indt1 = OBJ->triangles[i].tindices[0];
    int indt2 = OBJ->triangles[i].tindices[1];
    int indt3 = OBJ->triangles[i].tindices[2];

    //for each vertices of the triangle
    for(int j=0;j<3;j++){
      //vertex data
      OBJ->vertices[indv1*3+j];
      OBJ->vertices[indv2*3+j];
      OBJ->vertices[indv3*3+j];

      //normal data
      OBJ->normals[indn1*3+j];
      OBJ->normals[indn2*3+j];
      OBJ->normals[indn3*3+j];
    }

    //for each texture coordinates of the triangle
    for(int j=0;j<2;j++){
      OBJ->texcoords[indt1*2+j];
      OBJ->texcoords[indt2*2+j];
      OBJ->texcoords[indt3*2+j];
    }

  }

}


//////////////////////////////////////////////////////////////////////////
// init()
//  This function will be called once when the program starts.
//////////////////////////////////////////////////////////////////////////
void init()
{
  //read an obj model here
  OBJ = glmReadOBJ("bunnyC.obj");
  
  //move the object to the origin
  //scale to -1~+1
  glmUnitize(OBJ);  
  
  //calculate the vertex normals
  glmFacetNormals(OBJ);  
  glmVertexNormals(OBJ,90.0);
}

int main(int argc, char ** argv)
{
  //get into a rendering loop
  initAndRunLViewer(screenWidth, screenHeight, render, init);
  
  //free the model obj
  delete OBJ;

  return 0;
}

