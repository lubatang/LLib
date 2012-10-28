#include <LLib.h>
#include <framework.h>


using LLib::Viewer::LViewer;
using LLib::Math::LTranslateMatrix;


/// function pointers
static void (*renderFunc)(const LCamera cam, const LLight lit, FrameBuffer * colorBuff, RENDER_MODE mode) = NULL;
static void (*initFunc)() = NULL;


/// global variables
FrameBuffer *colorBuff = NULL;
unsigned int texID = 0;
RENDER_MODE renderMode = SOLID;


bool g_isOutputPPM = false;


LTranslateMatrix lightMatrix(vec3(100, 100, 0), vec3(0,0,0), vec3(0, 1, 0));



void showHelp()
{
  printf("======================================================\n");
  printf("Help:\n");
  printf("\tH/h: show help menu.\n");
  printf("\tV/v: set mouse to control the eye position\n");
  printf("\tL/l: set mouse to control the light position\n");
  printf("\tM/m: switch rendering mode.\n");
  printf("\tS/s: moving speed changing.\n");
  printf("\tU/u: move up.\n");
  printf("\tD/d: move down.\n");
  printf("\tO/o: Output current framebuffer.\n");
  printf("\tQ/q: Quit.\n");
  printf("======================================================\n");
}


void initGL()
{
  if(initFunc) (*initFunc)();

  /// GL texture

  /* Create and bind a texture object */
  glGenTextures(1, &texID);
  glBindTexture(GL_TEXTURE_2D, texID);

  /* Set texture parameters */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  const unsigned char *bits = colorBuff->getUCharArray();
  glTexImage2D(GL_TEXTURE_2D, 0, 3, colorBuff->getWidth(), colorBuff->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, bits);
  return ;
}

void updateTex()
{
  glBindTexture(GL_TEXTURE_2D, texID);
  const unsigned char *bits = colorBuff->getUCharArray();
  glTexImage2D(GL_TEXTURE_2D, 0, 3, colorBuff->getWidth(), colorBuff->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, bits);

  return ;
}


void dumpFramebufferAsPPM()
{
  static int count = 0;
  char buff[1024] ;
  sprintf(buff, "screen%03d.ppm", count++);

  printf("screen is dumped as %s.\n", buff);

  colorBuff->saveAsPPM(buff);
}

void drawFunc()
{
  
  const LCamera cam(LViewer::viewMatrix.getPos3v(), LViewer::viewMatrix.getPos3v() + LViewer::viewMatrix.getViewDir3v(), LViewer::viewMatrix.getUpDir3v());
  const LLight lit(lightMatrix.getPos3v());

  if(renderFunc && colorBuff)  
  {
    (*renderFunc)(cam, lit, colorBuff, renderMode);

    updateTex();
    LLib::Viewer::renderTextureOnScreenTop(texID, 0, 1, 0, 1);
  }

  if(g_isOutputPPM) { 
    g_isOutputPPM = false;
    dumpFramebufferAsPPM();
  }
}



void idle()
{
  if(LViewer::flag['H'-'A'])
  {
    LViewer::flag['H'-'A'] ^=1;
    showHelp();
  }

  if(!LViewer::flag['L'-'A'])
  {
    LViewer::flag['L'-'A'] ^=1;
    printf("Controlling Light.\n");
    LViewer::setCurrentControlMatrix(& lightMatrix);
  }

  if(!LViewer::flag['V'-'A'])
  {
    LViewer::flag['V'-'A'] ^=1;
    printf("Controlling Eye.\n");
    LViewer::setCurrentControlMatrix(& LViewer::viewMatrix);

  }

  if(!LViewer::flag['M'-'A'])
  {
    LViewer::flag['M'-'A'] ^=1;
    renderMode = (RENDER_MODE)((renderMode +1) % NUM);
    printf("Current render Mode is %s\n", (renderMode==0)? "WIRE":"SOLID");
  }

  if(!LViewer::flag['O'-'A'])
  {
    LViewer::flag['O'-'A'] ^=1;
    g_isOutputPPM = true;
  }


  glutPostRedisplay();
  return ;
}



int initAndRunLViewer(int winW,
                      int winH,
                      void (*render)(const LCamera cam, const LLight lit, FrameBuffer * colorB, RENDER_MODE mode),
                      void (*initFun)())
{
  renderFunc = render;
  initFunc   = initFun;

  colorBuff = new FrameBuffer(winW, winH);
  

  LViewer::setWindowSize(winW, winH);
  LViewer::setIdleFunc(idle);
  LViewer::setInitFunc(initGL);
  LViewer::setDrawModelFunc(drawFunc);
  
  LViewer::showWindowByGlut();

  delete colorBuff;

  return 0;
}


