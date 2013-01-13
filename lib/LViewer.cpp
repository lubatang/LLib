/************************************************************************
    OpenGL Viewer using "glut"
-------------------------------------------------------------------------

  Version 1.2 - August 10 2004

-------------------------------------------------------------------------
  Author: Chen Ying-Chieh

*************************************************************************/

#include <LViewer/LViewer.h>
#include <LTranslateMatrix/LTranslateMatrix.h>

#include <stdio.h>
#include <math.h>
#include <string.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <Triangle/ManagedStatic.h>
#include <Events/Event.h>
#include <Events/KeyEvent.h>
#include <Events/MouseEvent.h>
#include <Events/EventRegistry.h>

using namespace LLib::Math;
using namespace LLib::Viewer;

static luba::ManagedStatic<luba::MouseEvent> g_MouseEvent;

//===----------------------------------------------------------------------===//
// function for rendering screen
//===----------------------------------------------------------------------===//
GLubyte * LLib::Viewer::readScreenBits(int channelNumbers, int *w, int *h)
{
  long  bitsize, width;
  GLint viewport[4];
  GLubyte *bits;

  glReadBuffer(GL_BACK); // Sets the Reading Source to Offscreen(Back) Buffer
  glFinish() ;

  glGetIntegerv(GL_VIEWPORT,viewport);
  *w = viewport[2];
  *h = viewport[3];
  width = viewport[2]*channelNumbers;
  bitsize = width * viewport[3];
  if((bits = (GLubyte*)calloc(bitsize,1)) == NULL) {
    return (NULL);
  }
  glFinish();
  glPixelStorei(GL_PACK_ALIGNMENT,4);
  glPixelStorei(GL_PACK_ROW_LENGTH,0);
  glPixelStorei(GL_PACK_SKIP_ROWS,0);
  glPixelStorei(GL_PACK_SKIP_PIXELS,0);

  if (channelNumbers==4) {
    glReadPixels(0,0,viewport[2],viewport[3],GL_RGBA,GL_UNSIGNED_BYTE,bits);
  }
  else if( channelNumbers == 3) {
    glReadPixels(0,0,viewport[2],viewport[3],GL_RGB,GL_UNSIGNED_BYTE,bits);
  }
  return bits;
}

bool LLib::Viewer::readScreenBits( GLubyte * bits, int channelNumbers, int w, int h)
{
  return readScreenBits(bits, channelNumbers * w * h, channelNumbers);
}

bool LLib::Viewer::readScreenBits( GLubyte * bits, long bitsize, int channelNumbers)
{
  GLint viewport[4];

  glGetIntegerv(GL_VIEWPORT,viewport);
  if(bitsize != viewport[2] * viewport[3] * channelNumbers) {
    return false;
  }

  glReadBuffer(GL_BACK); // Sets the Reading Source to Offscreen(Back) Buffer
  glFinish() ;

  glPixelStorei(GL_PACK_ALIGNMENT,4);
  glPixelStorei(GL_PACK_ROW_LENGTH,0);
  glPixelStorei(GL_PACK_SKIP_ROWS,0);
  glPixelStorei(GL_PACK_SKIP_PIXELS,0);

  if (channelNumbers==4) {
    glReadPixels(0,0,viewport[2],viewport[3],GL_RGBA,GL_UNSIGNED_BYTE,bits);
  }
  else if( channelNumbers == 3) {
    glReadPixels(0,0,viewport[2],viewport[3],GL_RGB,GL_UNSIGNED_BYTE,bits);
  }
  return true;
}

GLfloat * LLib::Viewer::readScreenFloat(int channelNumbers, int *w, int *h)
{
  long  bitsize, width;
  GLint viewport[4];
  GLfloat *fbits;

  glReadBuffer(GL_BACK); // Sets the Reading Source to Offscreen(Back) Buffer
  glFinish() ;

  glGetIntegerv(GL_VIEWPORT,viewport);
  *w = viewport[2];
  *h = viewport[3];
  width = viewport[2]*channelNumbers;
  bitsize = width * viewport[3];
  if((fbits = (GLfloat*)calloc(bitsize,sizeof(GLfloat))) == NULL) {
    return (NULL);
  }
  glFinish();
  glPixelStorei(GL_PACK_ALIGNMENT,4);
  glPixelStorei(GL_PACK_ROW_LENGTH,0);
  glPixelStorei(GL_PACK_SKIP_ROWS,0);
  glPixelStorei(GL_PACK_SKIP_PIXELS,0);

  if (channelNumbers==4) {
    glReadPixels(0,0,viewport[2],viewport[3],GL_RGBA,GL_FLOAT,fbits);
  }
  else if( channelNumbers == 3) {
    glReadPixels(0,0,viewport[2],viewport[3],GL_RGB,GL_FLOAT,fbits);
  }
  return fbits;
}


void renderTextureOnScreenTop( GLuint tex, float xMin, float xMax, float yMin, float yMax, float uMin, float uMax, float vMin, float vMax, bool board)
{
   /*
        (uMax,vMin)    (uMax,vMax)
        ----------
        |        |
        |        |
        ----------
        (uMin,vMin)  (uMin,vMax)
   */
        glDisable(GL_DEPTH_TEST);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();  // push projection matrix
        glLoadIdentity();
        gluOrtho2D(0, 1, 0, 1);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();  // push modelview matrix
        glLoadIdentity();
        // render the quad with texture "tex"
        {
          glEnable(GL_TEXTURE_2D);
          glBindTexture(GL_TEXTURE_2D, tex);
          glColor3f(1,1,1);
          glBegin(GL_QUADS);
          //        glColor3f(0,0,0);
          glTexCoord2f(uMin,vMin);
          glVertex2f(xMin, yMin);

          //        glColor3f(1,0,0);
          glTexCoord2f(uMax, vMin);
          glVertex2f(xMax, yMin);

          //        glColor3f(1,1,1);
          glTexCoord2f(uMax, vMax);
          glVertex2f(xMax, yMax);

          //        glColor3f(0,0,1);
          glTexCoord2f(uMin, vMax);
          glVertex2f(xMin, yMax);

          glEnd();
          glDisable(GL_TEXTURE_2D);
        }
        // render the border of quad
        if(board)
        {
          //      glColor3f(1,1,1);
          glColor3f(0,0,0);
          glBegin(GL_LINE_STRIP);
          glVertex2f(xMin, yMin);
          glVertex2f(xMax, yMin);
          glVertex2f(xMax, yMax);
          glVertex2f(xMin, yMax);
          glVertex2f(xMin, yMin);
          glEnd();
        }
        glPopMatrix();  // pop modelview matrix
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();  // pop projection matrix
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_DEPTH_TEST);
      }

      void LLib::Viewer::renderTextureOnScreenTop( GLuint tex, float xMin, float xMax, float yMin, float yMax)
      {
        /*
        (0,1)        (1,1)
        ----------
        |        |
        |        |
        ----------
        (0,0)      (1,0)
        */
        glDisable(GL_DEPTH_TEST);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();  // push projection matrix
        glLoadIdentity();
        gluOrtho2D(0, 1, 0, 1);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();  // push modelview matrix
        glLoadIdentity();
        // render the quad with texture "tex"
        {
          glEnable(GL_TEXTURE_2D);
          glBindTexture(GL_TEXTURE_2D, tex);
          glColor3f(1,1,1);
          glBegin(GL_QUADS);
          //        glColor3f(0,0,0);
          glTexCoord2f(0,0);
          glVertex2f(xMin, yMin);

          //        glColor3f(1,0,0);
          glTexCoord2f(1,0);
          glVertex2f(xMax, yMin);

          //        glColor3f(1,1,1);
          glTexCoord2f(1,1);
          glVertex2f(xMax, yMax);

          //        glColor3f(0,0,1);
          glTexCoord2f(0,1);
          glVertex2f(xMin, yMax);

          glEnd();
          glDisable(GL_TEXTURE_2D);
        }
        // render the border of quad
        {
          //      glColor3f(1,1,1);
          glColor3f(0,0,0);
          glBegin(GL_LINE_STRIP);
          glVertex2f(xMin, yMin);
          glVertex2f(xMax, yMin);
          glVertex2f(xMax, yMax);
          glVertex2f(xMin, yMax);
          glVertex2f(xMin, yMin);
          glEnd();
        }
        glPopMatrix();  // pop modelview matrix
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();  // pop projection matrix
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_DEPTH_TEST);

      }


void renderTextOnScreenTop(char * text, bool isReset)
{
  // change openGL states
  {
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();  // push projection matrix
    glLoadIdentity();
    gluOrtho2D(0, 512, 0, 512);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();  // push modelview matrix
    glLoadIdentity();
  }
  // render text
  if(text != NULL) {
    static int line = 1;
    int len = strlen( text);
    if(isReset)
      line = 1;
    glRasterPos3d( 10, 512 - 20 * line,0);
    for (int i=0; i< len; i++) {
      switch(text[i]) {
        case '\n':
          glRasterPos3d( 10, 512 - 20 * ++line,0);
          break;
        case '\t':
          for(int j=0; j<8; j++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ' ');
          break;
        default:
          glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
      }
    }
  }
  // restore openGL states
  {
    glPopMatrix();  // pop modelview matrix
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();  // pop projection matrix
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
  }
} // end of renderTextOnScreenTop

//===----------------------------------------------------------------------===//
// Static Initialization
//===----------------------------------------------------------------------===//
LTranslateMatrix LViewer::viewMatrix(vec3(0, 400, 0), vec3(0, 0, 0), vec3(0, 0, 1));

LTranslateMatrix LViewer::nullMatrix;
LTranslateMatrix * LViewer::controlMatrix = &LViewer::viewMatrix;
LTranslateMatrix * LViewer::currentViewMatrix = &LViewer::viewMatrix;

// class static initialize
bool __isFlagRegistered[32] = {false};
int __flagN[10];
int __flag[32];

bool* LViewer::isFlagRegistered = __isFlagRegistered;
int * LViewer::flagN = __flagN;
int * LViewer::flag  = __flag;


int LViewer::win_id = 0;
//GLUI * LViewer::gluiContext = NULL;


vec3 LViewer::ballTracingCenter;
vec3 LViewer::modelCenter      = vec3( 0, 0, 0);

double  LViewer::seeda      = 0;
double  LViewer::phi      = 0;
double  LViewer::DirLength    = 10;
float  LViewer::FOV      = 60;
int    LViewer::width      = 300;
int    LViewer::height      = 300;

double  LViewer::nearPlane    = 50.0;
double  LViewer::farPlane    = 3000.0;

int    LViewer::currentFlagN  =0;
double  LViewer::preX      =0;
double  LViewer::preY      =0;
double  LViewer::prepreX    =0;
double  LViewer::prepreY    =0;
int    LViewer::mouseLKey    = KEYUP;
int    LViewer::mouseRKey    = KEYUP;
int    LViewer::mouseMKey    = KEYUP;

float  LViewer::moveSpeedMode  = LVIEWER_HIGH;
bool  LViewer::modelCenterMode= true;
bool  LViewer::rotating        = false;
int*  LViewer::rotatingMouseKey= NULL;

void (*  LViewer::m_drawModel)    (void);
void (* LViewer::m_init)      (void) = NULL;
void (* LViewer::m_idlef)      (void) = NULL;
int  (* LViewer::m_keyboard)    (unsigned char key, int x, int y) = NULL;
void (* LViewer::m_changScreenSize)  (int w, int h)  = NULL;
int  (* LViewer::m_mouseFun)    (int button, int state, int x, int y) = NULL;
int  (* LViewer::m_motionFun)    (int x, int y) = NULL;

// private
bool  LViewer::m_isFullScreen = false;
int    LViewer::tmpWinX = -1;  // for full screen
int    LViewer::tmpWinY = -1;  // for full screen
int    LViewer::tmpWinW = -1;  // for full screen
int    LViewer::tmpWinH = -1;  // for full screen

// Function List
void _renderScreen(void);
void _changScreenSize(int x, int y);
void _keyboard(unsigned char key, int x, int y);
void _specialKey(int key, int x, int y);
void _mouse(int button, int state, int x, int y);
void _init_gl(void);

void _changScreenSize(int w, int h)
{
  GLfloat aspect;

  glViewport(0, 0, w, h);
  LViewer::width = w;
  LViewer::height = h;

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  if (h==0) h = 1;

  aspect = w/(float)h;

  gluPerspective(  LViewer::FOV, aspect, LViewer::getNearPlane(), LViewer::getFarPlane());


  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  return ;
}

void _keyboard(unsigned char key, int x, int y)
{
  // user defined keyboard function
  if (LViewer::m_keyboard != NULL) {
    if(FINISH == (*LViewer::m_keyboard)(key, x, y))
      return ;
  }

  // default keyboard action
  if (key == 'q' || key == 'Q')
    exit(1);
  else if ( key == 'r' || key == 'R' ) {
    LViewer::controlMatrix->reset();
  }
  else if ( key =='s' || key == 'S') {
    if (LViewer::moveSpeedMode == LVIEWER_HIGH) {
      printf("Move Speed Mode Change to LOW.\n");
      LViewer::moveSpeedMode = LVIEWER_LOW;
      LViewer::controlMatrix->setMoveSpeed( LVIEWER_LOW );
    }
    else {
      printf("Move Speed Mode Change to HIGH.\n");
      LViewer::moveSpeedMode = LVIEWER_HIGH;
      LViewer::controlMatrix->setMoveSpeed( LVIEWER_HIGH );
    }

  }

  // flag [A-Za-z]
  if ( (key - 'a'<32) && (key -'a' >=0)) {
    LViewer::flag[key - 'a'] ^= 1;
  }
  else if ( (key - 'A'<32) && (key -'A' >=0)) {
    LViewer::flag[key - 'A'] ^= 1;
  }

  // numbers [0-9]
  if ( (key - '0'<10) && (key -'0' >=0)) {
    LViewer::flagN[LViewer::currentFlagN] = 0;
    LViewer::currentFlagN = key - '0';
    LViewer::flagN[key - '0'] = 1;
  }

  static luba::KeyEvent event;
  event.setKey(key);
  luba::EventRegistry::self().keyEvent(&event);

  glutPostRedisplay();
}

void _specialKey(int key, int x, int y)
{
  static luba::KeyEvent event;
  event.setKey(key);
  luba::EventRegistry::self().keyEvent(&event);
  // Refresh the Window
  glutPostRedisplay();

}

void MoveEvent(int x, int y)
{
  double difX, difY;

  if ( LViewer::mouseLKey == KEYDOWN || 
       LViewer::mouseRKey == KEYDOWN ||
       LViewer::mouseMKey == KEYDOWN ) {  
    difX = -x + LViewer::preX;
    difY = -y + LViewer::preY;

    LViewer::prepreX = LViewer::preX;
    LViewer::prepreY = LViewer::preY;

    LViewer::preX = x;
    LViewer::preY = y;

    LViewer::controlMatrix->moveView(difX, difY);
  }

  glutPostRedisplay();
}

void _motion(int x, int y)
{
  // user defined keyboard function
  if (LViewer::m_motionFun != NULL) {
    if( FINISH == (*LViewer::m_motionFun)( x, y))
      return ;
  }

  g_MouseEvent->setCoord(x, y);
  luba::EventRegistry::self().mouseMoveEvent(&*g_MouseEvent);
  MoveEvent(x, y);
}


void _mouse(int button, int state, int x, int y)
{
  // user defined keyboard function
  if (LViewer::m_mouseFun != NULL)
  {
    if( FINISH == (*LViewer::m_mouseFun)(button, state, x, y))
      return ;
  }


  g_MouseEvent->reset();
  g_MouseEvent->setCoord(x, y);

  LViewer::rotating = false;
  if(button == 0 )        // mouse left key
  {
    g_MouseEvent->setButton(luba::MouseEvent::LeftButton);

    if (state == KEYDOWN)      // left key down
    {
      luba::EventRegistry::self().mousePressEvent(&*g_MouseEvent);
      LViewer::rotating = false;
      LViewer::prepreX = LViewer::preX = x;
      LViewer::prepreY = LViewer::preY = y;
      LViewer::mouseLKey = KEYDOWN;
    }
    else              // left key up
    {
      luba::EventRegistry::self().mouseReleaseEvent(&*g_MouseEvent);
      LViewer::rotating = true;
      LViewer::mouseLKey = KEYUP;
      LViewer::rotatingMouseKey = &LViewer::mouseLKey;
    }
  }

  if (button == 1)          // mouse middle
  {
    g_MouseEvent->setButton(luba::MouseEvent::MidButton);
    if (state == KEYDOWN)      // middle key down
    {
      luba::EventRegistry::self().mousePressEvent(&*g_MouseEvent);
      LViewer::rotating = false;
      LViewer::prepreX = LViewer::preX = x;
      LViewer::prepreY = LViewer::preY = y;
      LViewer::mouseMKey = KEYDOWN;
    }
    else              // left key up
    {
      luba::EventRegistry::self().mouseReleaseEvent(&*g_MouseEvent);
      LViewer::rotating = true;
      LViewer::mouseMKey = KEYUP;
      LViewer::rotatingMouseKey = &LViewer::mouseMKey;
    }
  }

  if (button == 2)          // mouse right key
  {
    g_MouseEvent->setButton(luba::MouseEvent::RightButton);
    if (state == KEYDOWN)      // right key down
    {
      luba::EventRegistry::self().mousePressEvent(&*g_MouseEvent);
      LViewer::rotating = false;
      LViewer::prepreX = LViewer::preX = x;
      LViewer::prepreY = LViewer::preY = y;
      LViewer::mouseRKey = KEYDOWN;
    }
    else              // right key up
    {
      luba::EventRegistry::self().mouseReleaseEvent(&*g_MouseEvent);
      LViewer::rotating = true;
      LViewer::mouseRKey = KEYUP;
      LViewer::rotatingMouseKey = &LViewer::mouseRKey;
    }
  }
}

void _renderScreen(void)
{
    // FPS calculation:
      //static unsigned int framecount = 0;
      //static LLib::Timer::LTimer2 timer;
      //double duration = timer.getTime(1);
      //if (duration > 1.0)
      //{
      //  char buf[64];
      //  sprintf(buf, "FPS: %4.2lf", framecount / duration);
      //  framecount = 0;
      //  glutSetWindowTitle(buf);
      //}
      //framecount++;


    // for FPS calculation begin  1/2
      //LARGE_INTEGER counterS, counterE, fre;
      //int fps = 1;
      //fps &= QueryPerformanceCounter( &counterS);
      
    // for FPS calculation end
    /*
      printf("viewer Postion: (%6.3lf, %6.3lf, %6.3lf) look at (%6.3lf, %6.3lf, %6.3lf)\n\tup (%6.3lf, %6.3lf, %6.3lf)\n", 
            LViewer::viewerUpDirection[0], LViewer::viewerUpDirection[1], LViewer::viewerUpDirection[2]
        );
    */


      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      LViewer::currentViewMatrix->applyView();

      
    // Model  begin
      glPushMatrix();
        (*LViewer::m_drawModel)();
      glPopMatrix();
    // Model end
      

    // for FPS calculation end
    glutSwapBuffers();

    //// for FPS calculation begin 2/2
    //  fps &= QueryPerformanceCounter( &counterE);  // get end time
    //  fps &= QueryPerformanceFrequency( &fre);    // get sample frequence
    //  if(fps)
    //  {
    //    printf("\rfps:%lf", (fre.QuadPart / (double) (counterE.QuadPart - counterS.QuadPart)) );
    //  }
}


void LViewer::init_gl(void)
{

//      LViewer::viewMatrix = LTranslateMatrix();
//      LViewer::controlMatrix  = &LViewer::viewMatrix;
  int i;

  for (i=0; i<32; i++)
    LViewer::flag[i] = 1;
  for (i=0; i<10; i++)
    LViewer::flagN[i] = 0;
  LViewer::flagN[0] = 1;
  LViewer::currentFlagN = 0;


// init glew()
#ifdef USE_GLEW
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    /* Problem: glewInit failed, something is seriously wrong. */
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    exit(1);
  }
  fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  //  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CCW);

  if (LViewer::m_init != NULL) {
    LViewer::m_init();
  }

}

void LViewer::_idle()
{
  if (LViewer::rotating && *LViewer::rotatingMouseKey == KEYUP && 
      !(  fabs(-LViewer::preX + LViewer::prepreX) < 3 &&
            fabs(-LViewer::preY + LViewer::prepreY) < 3  )
        ) {
    double x = LViewer::preX;
    double y = LViewer::preY;
    *LViewer::rotatingMouseKey = KEYDOWN;
    LViewer::preX = LViewer::prepreX;
    LViewer::preY = LViewer::prepreY;
    MoveEvent( x, y);
    *LViewer::rotatingMouseKey = KEYUP;
  }
  if (NULL != LViewer::m_idlef) {
    if( glutGetWindow() != LViewer::win_id )
      glutSetWindow( LViewer::win_id );
    LViewer::m_idlef();
  }
  return;
}

void LViewer::createWindow( void (*renderFunc)(void), void (*idleFunc)(void), void (*initFunc)(void),  int width /*= -1*/, int height /*= -1*/, float nearPlane /*= -1*/, float farPlane /*= -1*/ )
{
  if(nearPlane != -1)  LLib::Viewer::LViewer::setNearPlane(nearPlane);
  if(farPlane != -1)  LLib::Viewer::LViewer::setFarPlane(farPlane);
      
  if(width != -1) LLib::Viewer::LViewer::setWidth(width);
  if(height!= -1) LLib::Viewer::LViewer::setHeight(height);

  LLib::Viewer::LViewer::setDrawModelFunc(renderFunc);
  LLib::Viewer::LViewer::setIdleFunc(idleFunc);
  LLib::Viewer::LViewer::setInitFunc(initFunc);

  LLib::Viewer::LViewer::showWindowByGlut();

  return ;
}

void LViewer::showWindowByGlut()
{

  if (!m_changScreenSize) {
    m_changScreenSize = _changScreenSize;
  }

  glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(LViewer::width,LViewer::height);

  LViewer::win_id = glutCreateWindow("space viewer");
/**
  if (LViewer::gluiContext) {
    LViewer::gluiContext = GLUI_Master.create_glui( "glui", 0, LViewer::width+2, 0);  //create a GLUI object

    GLUI_Master.set_glutIdleFunc( _idle );
    GLUI_Master.set_glutSpecialFunc( _specialKey );
    GLUI_Master.set_glutKeyboardFunc(_keyboard);
    GLUI_Master.set_glutMouseFunc(_mouse);
    GLUI_Master.set_glutDisplayFunc(_renderScreen);
    GLUI_Master.set_glutReshapeFunc(m_changScreenSize);
  }
  else {
**/
    glutIdleFunc(_idle);
    glutSpecialFunc(_specialKey);
    glutKeyboardFunc(_keyboard);
    glutMouseFunc(_mouse);

    glutDisplayFunc(_renderScreen);
    glutReshapeFunc(m_changScreenSize);
//  }
  glutMotionFunc(_motion);
        
  init_gl();

  glutMainLoop();
}

LViewer::LViewer()  {}

LViewer::~LViewer()  {}
