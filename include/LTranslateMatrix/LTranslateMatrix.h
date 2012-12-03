#ifndef _LTRANSLATEDMATRIX_H_
#define _LTRANSLATEDMATRIX_H_

#include <algebra3/algebra3.h>
#include <LGlobal/LGlobal.h>  // for PI

using namespace LLib::Math;


namespace LLib {
namespace Math {

/*******************************************************************
  gluLookAt is equivalent to glMultMatrixf(M); glTranslated (-eyex, -eyey, -eyez); 
  In OpenGL, matrix is column major so M = { x.x, x.y, x.z, y.x, y.y, y.z, z.x, z.y, z.z };

          s[0]  s[1]  s[2]  0
  M= [    u[0]  u[1]  u[2]  0    ],  f =  (target.pos  - eye.pos)
         -f[0] -f[1] -f[2]  0        u =  up
            0     0    0    1        s =  right
 
 ******************************************************************/

class LTranslateMatrix
{
private:
  // matrix
  vec3  pos;
  vec3 backDir;          //    Z
  vec3 upDir;            //    Y
  vec3 rightDir;          //    X
  float RotationMatrix[16];  //    M =  { X Y Z }.transpose;

  // moving
  double moveSpeed;
  vec3 sphereCenter;

public:
  LTranslateMatrix();
  LTranslateMatrix( vec3 pos, vec3 targetPos, vec3 up);
  LTranslateMatrix( double pos[3], double targetPos[3], double  up[3]);
  ~LTranslateMatrix();

  // Save & Load
  bool saveMat(const char * fname); // return true if saved, false if file not opened.
  bool loadMat(const char * fname);  // return true if loaded, false if file not found.

  // mouse control
  void moveOnSphere( double dX, double dY);
  void moveView(double dX, double dY);
  void move3D( double dX, double dY);
  // others
  void move3DUpDown(double direction = 1, double dX = 0);
  void move3DLeftRight(double direction = 1, double dX = 0);
  void move3DFrontBack(double direction = 1, double dX = 0);

  vec3 getPos3v()      const  { return this->pos;};
  vec4 getPos4v()      const  { return vec4(this->pos, 1);};
  vec3 getViewDir3v()    const  { return (-this->backDir);};
  vec3 getUpDir3v()    const  { return this->upDir;};
  vec3 getRightDir3v()  const  { return this->rightDir;};
  vec3 getSphereCenter()  const  { return this->sphereCenter;};

  const mat4 getRotationMat4()  const;
  const mat3 getRotationMat3()  const;

  void applyView();
  void applyViewRot();
  void applyObj();
  void applyObjRot();
  void reset();
  void setPos3v(double x, double y, double z)        { this->pos.set(x,y,z);};
  void setUpDir3v(double x, double y, double z)      { this->upDir.set(x,y,z);};
  void setRightDir3v(double x, double y, double z)    { this->rightDir.set(x,y,z);};
  void setSphereCenter(double x, double y, double z)    { this->sphereCenter.set(x,y,z);};
  void setSphereCenter3v( vec3 center)          { this->sphereCenter = center; return;};
  void setSphereCenter3f( float x, float y, float z)    { this->sphereCenter = vec3(x,y,z); return;};
  void setSphereCenter3d( double x, double y, double z)  { this->sphereCenter = vec3(x,y,z); return;};
  void setLookAt(vec3 pos, vec3 targetPos, vec3 up)    { initialize( pos, targetPos, up); return;};
  void setMoveSpeed(double newSpeed = 1);

  void render3CoordAxisGL( float scaleLen = 20);

  void debug();

private:
  void initialize( vec3 pos, vec3 targetPos, vec3 up);

};

}  // namespace of Matrix
}  // namesapce of LLib

#endif
