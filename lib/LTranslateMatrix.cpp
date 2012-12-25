#include <LTranslateMatrix/LTranslateMatrix.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <cmath>

using namespace LLib::Math;
using namespace std;
using namespace luba;

void LTranslateMatrix::initialize(vec3 pos, vec3 targetPos, vec3 up)
{
  this->pos      =  pos;
  this->backDir  =  (pos - targetPos).normalize();
  this->upDir    =  up.normalize();
  this->rightDir  =  CrossProduct(this->upDir, this->backDir).normalize();  //  X = Y cross Z

  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      this->RotationMatrix[i*4+j] = (i==j)? 1.0f:0.0f;    // Identity Matrix


  this->sphereCenter  = vec3(0,0,0);
  this->moveSpeed  = 1;
}

LTranslateMatrix::LTranslateMatrix( vec3 pos, vec3 targetPos, vec3 up)
{
  initialize( pos, targetPos, up);
}

LTranslateMatrix::LTranslateMatrix()
{
  initialize( vec3( 0, 0, 0),  vec3( 0, 0, -1),  vec3( 0, 1, 0));
}

LTranslateMatrix::LTranslateMatrix(double pos[3], double targetPos[3], double up[3])
{
  initialize(
    vec3( pos[0], pos[1], pos[2]),
    vec3( targetPos[0], targetPos[1], targetPos[2]),
    vec3( up[0], up[1], up[2])
  );
}

LTranslateMatrix::~LTranslateMatrix()
{}

const mat3 LTranslateMatrix::getRotationMat3() const
{
  return mat3( this->rightDir, this->upDir, -this->backDir);
}

const mat4 LTranslateMatrix::getRotationMat4() const
{
  return mat4( vec4(rightDir, 0), vec4(upDir, 0), vec4(backDir, 1.0), vec4(0,0,0,1));
}

void LTranslateMatrix::moveOnSphere( double dX, double dY)
{
  // ball tarcing
  this->rightDir =  CrossProduct(this->upDir, this->backDir).normalize();
  this->backDir  = -1* (  this->sphereCenter - this->pos 
                   +  dY * this->upDir * this->moveSpeed
                   -  dX * this->rightDir* this->moveSpeed).normalize();

  double len = (this->sphereCenter - this->pos).length();
  this->pos = (this->sphereCenter + (this->backDir * len));

  this->rightDir  =  CrossProduct(this->upDir, this->backDir).normalize();
  this->upDir    =  CrossProduct(this->backDir, this->rightDir).normalize();
}

void LTranslateMatrix::moveView(double dX, double dY)
{
  const double uu = 0.03;
  double phi  = dX * uu;
  double theta  = dY * uu;

  if (phi < -180.0)    phi += 360.0;
  if (phi >  180.0)    phi -= 360.0;
  if (theta < -90.0)  theta = -90.0;
  if (theta < -90.0)  theta = -90.0;

  double cosTheta  = cos( theta * Math::PI / 180.0);
  double sinTheta  = sin( theta * Math::PI / 180.0);
  double cosPhi    = cos( phi * Math::PI / 180.0);
  double sinPhi    = sin( phi * Math::PI / 180.0);

  this->backDir  =    cosPhi * cosTheta * this->backDir
                    +  sinPhi * cosTheta * this->rightDir
                    -  sinTheta * this->upDir;
  this->rightDir  = CrossProduct(this->upDir, this->backDir).normalize();
  this->upDir    = CrossProduct(this->backDir, this->rightDir).normalize();

  return;
}

void LTranslateMatrix::move3D( double dX, double dY)
{
  if (fabs(dX) < fabs(dY))
    this->pos  =  this->pos + (- this->backDir) * this->moveSpeed * dY;
  else
    this->pos  = this->pos + (- this->rightDir) * this->moveSpeed * dX;      
}

void LTranslateMatrix::move3DUpDown( double direction /* = 1 */, double dX /* = 0 */)
{
  dX = (dX==0)? this->moveSpeed: dX;
  this->pos = this->pos + this->upDir * dX * direction;
}

void LTranslateMatrix::move3DLeftRight( double direction /* = 1 */, double dX /* = 0 */)
{
  dX = (dX==0)? this->moveSpeed: dX;
  this->pos = this->pos + this->rightDir * dX * direction;
}

void LTranslateMatrix::move3DFrontBack( double direction /* = 1 */, double dX /* = 0 */)
{
  dX = (dX==0)? this->moveSpeed: dX;
  this->pos = this->pos - this->backDir * dX * direction;
}

void LTranslateMatrix::setMoveSpeed( double newSpeed)
{
  this->moveSpeed = newSpeed;
  return;
}

void LTranslateMatrix::reset()
{
  this->pos    = vec3( 0, 0, -1);
  this->backDir  = vec3( 0, 0,  1);
  this->upDir    = vec3( 0, 1, 0);
  this->rightDir  = vec3( 1, 0 ,0);

  for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
      this->RotationMatrix[i*4+j] = (i==j)? 1.0f:0.0f;  // Identity Matrix
  this->moveSpeed = 1;
}

void LTranslateMatrix::applyView()
{
  this->RotationMatrix[0]    = (float) this->rightDir[0];
  this->RotationMatrix[4]    = (float) this->rightDir[1];
  this->RotationMatrix[8]    = (float) this->rightDir[2];
  this->RotationMatrix[12]  = 0;
  this->RotationMatrix[1]    = (float) this->upDir[0];
  this->RotationMatrix[5]    = (float) this->upDir[1];
  this->RotationMatrix[9]    = (float) this->upDir[2];
  this->RotationMatrix[13]  = 0;
  this->RotationMatrix[2]    = (float) this->backDir[0];
  this->RotationMatrix[6]    = (float) this->backDir[1];
  this->RotationMatrix[10]  = (float) this->backDir[2];
  this->RotationMatrix[14]  = 0;
  this->RotationMatrix[3]    = 0;
  this->RotationMatrix[7]    = 0;
  this->RotationMatrix[11]  = 0;
  this->RotationMatrix[15]  = 1;
      
  glMultMatrixf(this->RotationMatrix);
  glTranslated(-this->pos[0], -this->pos[1], -this->pos[2]);
/*
      vec3 a = (this->pos - backDir);
      gluLookAt( this->pos[0], this->pos[1], this->pos[2],
              a[0], a[1], a[2],
              this->upDir[0], this->upDir[1], this->upDir[2]);
*/      
}

void LTranslateMatrix::applyViewRot()
{
  this->RotationMatrix[0]    = (float) this->rightDir[0];
  this->RotationMatrix[4]    = (float) this->rightDir[1];
  this->RotationMatrix[8]    = (float) this->rightDir[2];
  this->RotationMatrix[12]  = 0;
  this->RotationMatrix[1]    = (float) this->upDir[0];
  this->RotationMatrix[5]    = (float) this->upDir[1];
  this->RotationMatrix[9]    = (float) this->upDir[2];
  this->RotationMatrix[13]  = 0;
  this->RotationMatrix[2]    = (float) this->backDir[0];
  this->RotationMatrix[6]    = (float) this->backDir[1];
  this->RotationMatrix[10]  = (float) this->backDir[2];
  this->RotationMatrix[14]  = 0;
  this->RotationMatrix[3]    = 0;
  this->RotationMatrix[7]    = 0;
  this->RotationMatrix[11]  = 0;
  this->RotationMatrix[15]  = 1;

  glMultMatrixf(this->RotationMatrix);
  //glTranslated(-this->pos[0], -this->pos[1], -this->pos[2]);
  /*
  vec3 a = (this->pos - backDir);
  gluLookAt( this->pos[0], this->pos[1], this->pos[2],
  a[0], a[1], a[2],
  this->upDir[0], this->upDir[1], this->upDir[2]);
  */      
}

void LTranslateMatrix::applyObj()    // inverse lookAt
{
  this->RotationMatrix[0]    = (float) this->rightDir[0];
  this->RotationMatrix[1]    = (float) this->rightDir[1];
  this->RotationMatrix[2]    = (float) this->rightDir[2];
  this->RotationMatrix[3]    = 0;
  this->RotationMatrix[4]    = (float) this->upDir[0];
  this->RotationMatrix[5]    = (float) this->upDir[1];
  this->RotationMatrix[6]    = (float) this->upDir[2];
  this->RotationMatrix[7]    = 0;
  this->RotationMatrix[8]    = (float) this->backDir[0];
  this->RotationMatrix[9]    = (float) this->backDir[1];
  this->RotationMatrix[10]  = (float) this->backDir[2];
  this->RotationMatrix[11]  = 0;
  this->RotationMatrix[12]  = 0;
  this->RotationMatrix[13]  = 0;
  this->RotationMatrix[14]  = 0;
  this->RotationMatrix[15]  = 1;

  glTranslated( this->pos[0], this->pos[1], this->pos[2]);
  glMultMatrixf(this->RotationMatrix);

//      this->sphereCenter = this->pos - this->backDir;

  /*
  vec3 a = (this->pos - backDir);
  gluLookAt( this->pos[0], this->pos[1], this->pos[2],
  a[0], a[1], a[2],
  this->upDir[0], this->upDir[1], this->upDir[2]);
  */      
}

void LTranslateMatrix::applyObjRot()    // inverse lookAt
{
  this->RotationMatrix[0]    = (float) this->rightDir[0];
  this->RotationMatrix[1]    = (float) this->rightDir[1];
  this->RotationMatrix[2]    = (float) this->rightDir[2];
  this->RotationMatrix[3]    = 0;
  this->RotationMatrix[4]    = (float) this->upDir[0];
  this->RotationMatrix[5]    = (float) this->upDir[1];
  this->RotationMatrix[6]    = (float) this->upDir[2];
  this->RotationMatrix[7]    = 0;
  this->RotationMatrix[8]    = (float) this->backDir[0];
  this->RotationMatrix[9]    = (float) this->backDir[1];
  this->RotationMatrix[10]  = (float) this->backDir[2];
  this->RotationMatrix[11]  = 0;
  this->RotationMatrix[12]  = 0;
  this->RotationMatrix[13]  = 0;
  this->RotationMatrix[14]  = 0;
  this->RotationMatrix[15]  = 1;

  //glTranslated( this->pos[0], this->pos[1], this->pos[2]);
  glMultMatrixf(this->RotationMatrix);


  //      this->sphereCenter = this->pos - this->backDir;

  /*
  vec3 a = (this->pos - backDir);
  gluLookAt( this->pos[0], this->pos[1], this->pos[2],
  a[0], a[1], a[2],
  this->upDir[0], this->upDir[1], this->upDir[2]);
  */      
}

void LTranslateMatrix::render3CoordAxisGL( float scaleLen)
{
  // position
  {
    glPointSize(10);
    glColor3f(1,1,1);
    glBegin(GL_POINTS);
    glVertex3dv(this->getPos3v().native());
    glEnd();
    glPointSize(1);

  }
  // 3 coordinate lines
  {
    glBegin(GL_LINES);
    // front
    glColor3f(0,1,1);
    glVertex3dv( this->pos.native());
    glVertex3dv( (this->pos - scaleLen * this->backDir).native());
    // up
    glColor3f(1,0,1);
    glVertex3dv( this->pos.native());
    glVertex3dv( (this->pos + scaleLen * this->upDir).native());
    // right
    glColor3f(1,1,0);
    glVertex3dv( this->pos.native());
    glVertex3dv( (this->pos + scaleLen * this->rightDir).native());
    glEnd();
  }
  // 3 characters 'D','U','R' on the 3 corrdinate lines
  {
    glColor3f(0,1,1);
    glRasterPos3dv((this->pos - scaleLen * this->backDir).native());
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'D');

    glColor3f(1,0,1);
    glRasterPos3dv( (this->pos + scaleLen * this->upDir).native());
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'U');

    glColor3f(1,1,0);
    glRasterPos3dv( (this->pos + scaleLen * this->rightDir).native());
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'R');
  }
}

