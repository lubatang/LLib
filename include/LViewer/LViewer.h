/************************************************************************
    OpenGL Viewer using "glut"
-------------------------------------------------------------------------

  Version 1.2 - August 10 2004

-------------------------------------------------------------------------
  Author: Chen Ying-Chieh

*************************************************************************/

#ifndef _LVIEWER_H_
#define _LVIEWER_H_


#include <stdlib.h>

//#include <gl/glew.h>
//#ifndef USE_GLEW
//  #define USE_GLEW
//#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <LGlobal/LGlobal.h>
#include <LTranslateMatrix/LTranslateMatrix.h>

using namespace LLib::Math;
using namespace luba;

namespace LLib
{

  namespace Viewer
  {
    /* =====================================================*/
    /* function for get the bits from screen. */
    bool      readScreenBits( GLubyte * bits, int channelNumbers, int w, int h);
    bool      readScreenBits( GLubyte * bits, long bitsize, int channelNumbers);
    GLubyte * readScreenBits(int channelNumbers, int *w, int *h);
    GLfloat * readScreenFloat(int channelNumbers, int *w, int *h);

    /* function for rendering screen */
    void renderTextureOnScreenTop( GLuint tex, float xMin, float xMax, float yMin, float yMax);
    void renderTextureOnScreenTop( GLuint tex, float xMin, float xMax, float yMin, float yMax, float uMin, float uMax, float vMin, float vMax, bool board);
    
    void renderTextOnScreenTop(char * text, bool isReset = true);


    /* =====================================================*/
    static const int    KEYDOWN        =  0;
    static const int    KEYUP        =  1;
    static const double    LVIEWER_HIGH    =  1;
    static const double    LVIEWER_LOW      =  0.1;

    static const int    FINISH        = 1;
    static const int    UNFINISH      = 0;

    class LViewer
    {
      public:
        static int win_id;
        // static GLUI * gluiContext;

        static LTranslateMatrix *controlMatrix;
        static LTranslateMatrix *currentViewMatrix;
        static LTranslateMatrix viewMatrix;
        static LTranslateMatrix nullMatrix;

        static bool* isFlagRegistered;
        static int * flag;
        static int * flagN;
      
        static vec3 viewerPosition;
        static vec3 viewerDirection;      // z
        static vec3 viewerUpDirection;    // y
        static vec3 viewerLeftDirection;  // x
        static vec3 ballTracingCenter;
        static vec3 modelCenter;
        static double seeda;
        static double phi;
        static double DirLength;

        static float FOV;
        static int width;
        static int height;

        static double nearPlane;
        static double farPlane;


    // ず场 status 把计
        static int    currentFlagN;
        static double preX;
        static double preY;
        static double prepreX;
        static double prepreY;

        static int mouseLKey;
        static int mouseRKey;
        static int mouseMKey;

        static float moveSpeedMode;
        static bool modelCenterMode;
        static bool rotating;
        static int *rotatingMouseKey;
    // ず场 function points
    
        static void (*m_drawModel)    (void);
        static int  (*m_keyboard)    (unsigned char key, int x, int y);
        static int  (*m_mouseFun)    (int button, int state, int x, int y);
        static int  (*m_motionFun)    (int x, int y);

    private:  
        static void (*m_init)      (void);
        static void (*m_idlef)      (void);
        static void (*m_changScreenSize)  (int x, int y);
        
    /*
        static void (*renderScreen)    (void);
        static void (*specialKey)    (int key, int x, int y);
        
        
    */
        static bool m_isFullScreen;
        static int tmpWinX;  // for full screen
        static int tmpWinY;  // for full screen
        static int tmpWinW;
        static int tmpWinH;

    private:  
        LViewer();
        ~LViewer();

    public:
        static void createWindow(void (*renderFunc)(void),  void (*idleFunc)(void),  void (*initFunc)(void), int width=-1, int height=-1, float nearPlane = -1, float farPlane = -1);
        static void showWindowByGlut();
        static void init_gl(void);
        static void _idle(void);

        //static void enableGLUI()      { LViewer::gluiContext = (GLUI*) 1; return; };

        static void setCurrentControlMatrix( LTranslateMatrix * matrix = &LViewer::viewMatrix)  { LViewer::controlMatrix = matrix; };
        static void setCurrentViewMatrix( LTranslateMatrix * matrix = &LViewer::viewMatrix)  { LViewer::currentViewMatrix = matrix; };

        static void setModelCenter ( vec3 value ) {
          LViewer::modelCenterMode = true;
          LViewer::controlMatrix->setSphereCenter3v( LViewer::modelCenter = value);
        }

        static void setDrawModelFunc    ( void (*drawModelP)    (void))                  { m_drawModel = drawModelP;};
        static void setInitFunc        ( void (*init)        (void))                  { m_init = init;};
        static void setIdleFunc        ( void (*idle)        (void))                  { m_idlef = idle;};
        static void setKeyboardFunc      ( int  (*keyboard)      (unsigned char key, int x, int y))    { m_keyboard = keyboard;};
        static void setMouseFunc      ( int  (*mouseFun)      (int button, int state, int x, int y))  { m_mouseFun = mouseFun;}; 
        static void setMotionFunc      ( int  (*motionP)      (int x, int y))              { m_motionFun = motionP;};
        static void setChangScreenSizeFunc  ( void (*changScreenSize)  (int w, int h))              { m_changScreenSize = changScreenSize; };

        static void setFOV          ( float fov)  {LViewer::FOV = fov;};
        static float getFOV          ( )        {return LViewer::FOV;};

        static void  setWidth        ( int width)        {LViewer::width = width;};
        static void setHeight        ( int height)        {LViewer::height = height;};
        static void setWindowSize      ( int width, int height)  {LViewer::width = width; LViewer::height = height;}
        static int  getWidth        ()        { return LViewer::width;};
        static int  getHeight        ()        { return LViewer::height;};
        static void updateScreenSize    ()        { LViewer::width = glutGet((GLenum)GLUT_WINDOW_WIDTH); LViewer::height = glutGet((GLenum)GLUT_WINDOW_HEIGHT);};

        static void    setNearPlane      ( double n)        {LViewer::nearPlane = n;};
        static void    setFarPlane        ( double f)        {LViewer::farPlane = f;};
        static void    setNearFarPlane      ( double n, double f)  {LViewer::nearPlane = n; LViewer::farPlane = f;};
        static double  getNearPlane      ()      {return LViewer::nearPlane;};
        static double  getFarPlane        ()      {return LViewer::farPlane;};

    /*
        static void setRenderScerrnFunc    ( void (*renderScreenP)    (void))                  { renderScreen = renderScreenP;};
        static void setchangeScreenSizeFunc  ( void (*changeScreenSizeP)  (int x, int y))              { changeScreenSize = changeScreenSizeP;};
        static void setKeyboardFunc      ( void (*keyboardP)      (unsigned char key, int x, int y))    { keyboard = keyboardP;};
        static void setSpecialKeyFunc    ( void (*specialKeyP)    (int key, int x, int y))        { specialKey = specialKeyP;};
        
    */
    // Real actions functions
        static void    setWinPos(int x, int y)            {  glutPositionWindow(x, y);};
        static int    getWinPosX()                {  return glutGet((GLenum)GLUT_WINDOW_X);};
        static int    getWinPosY()                {  return glutGet((GLenum)GLUT_WINDOW_Y);};
        static void    getWinPos(int *winX, int *winY)        {  *winX = getWinPosY(); *winY = getWinPosY();};

        static bool    isFullScreen()                {  return m_isFullScreen;};
        static void    reshapeWindowSize(int width, int height)  {  m_isFullScreen = false; setWindowSize(width, height); glutReshapeWindow(width, height); };
        static void    switchFullScreenAndWindow()  
        {
          if(!m_isFullScreen)  
          {
            tmpWinX = getWinPosX(); tmpWinY = getWinPosY();
            tmpWinW = getWidth();  tmpWinH = getHeight();
            glutFullScreen();
            m_isFullScreen = true;
          } else {  // else already full screen.
            reshapeWindowSize(tmpWinW, tmpWinH);
            setWinPos(  tmpWinX , tmpWinY );
            m_isFullScreen = false;
          }
        }
    };
  } // namespace of Viewer
} // namespace of LLib

#endif
