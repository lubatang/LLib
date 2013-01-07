#include <Triangle/Camera.h>
#include <LLib.h>
#include <framework.h>
#include <Triangle/FrameBuffer.h>
#include <Support/FileHandle.h>
#include <Triangle/ManagedStatic.h>

using LLib::Viewer::LViewer;
using LLib::Math::LTranslateMatrix;
using namespace luba;
using namespace std;

static RenderFuncType renderFunc = NULL;
static InitFuncType initFunc = NULL;

/// global variables
FrameBuffer *colorBuff = NULL;
unsigned int texID = 0;
RENDER_MODE renderMode = WIRE;
static ManagedStatic<Light> g_Light;

bool g_isOutputPPM = false;


void showHelp()
{
  printf("======================================================\n");
  printf("Help:\n");
  printf("\tH/h: show help menu.\n");
  printf("\tV/v: set mouse to control the eye position\n");
  printf("\tL/l: set mouse to control the light position\n");
  printf("\tT/t: set mouse to control the model position\n");
  printf("\tM/m: switch rendering mode.\n");
  printf("\tP/p: switch projection mode.\n");
  printf("\tS/s: moving speed changing.\n");
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

  FileHandle handler;
  handler.open(buff,
               FileHandle::ReadWrite | FileHandle::Create | FileHandle::Truncate,
               0755);
  colorBuff->saveAsPPM(handler);
  handler.close();
}

void drawFunc()
{  

  Camera cam(LViewer::viewMatrix.getPos3v(),
             LViewer::viewMatrix.getPos3v() + LViewer::viewMatrix.getViewDir3v(),
             LViewer::viewMatrix.getUpDir3v());

  if(renderFunc && colorBuff) {
    (*renderFunc)(cam, *g_Light, colorBuff, renderMode);

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
    LViewer::setCurrentControlMatrix(& LViewer::nullMatrix);
  }

  if(!LViewer::flag['V'-'A'])
  {
    LViewer::flag['V'-'A'] ^=1;
    printf("Controlling Eye.\n");
    LViewer::setCurrentControlMatrix(& LViewer::viewMatrix);
  }

  if (!LViewer::flag['T' - 'A']) {
    LViewer::flag['T' - 'A'] ^= 1;
    printf("Controlling Model.\n");
    LViewer::setCurrentControlMatrix(& LViewer::nullMatrix);
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

int initAndRunLViewer(unsigned int pWinW,
                      unsigned int pWinH,
                      RenderFuncType render,
                      InitFuncType initFun)
{
  renderFunc = render;
  initFunc   = initFun;

  colorBuff = new FrameBuffer(pWinW, pWinH);
  
  LViewer::setWindowSize(pWinW, pWinH);
  LViewer::setIdleFunc(idle);
  LViewer::setInitFunc(initGL);
  LViewer::setDrawModelFunc(drawFunc);
  
  LViewer::showWindowByGlut();

  delete colorBuff;

  return 0;
}


