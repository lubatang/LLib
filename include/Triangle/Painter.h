//===- Painter.h ----------------------------------------------------------===//
//
// Copyright (C), 2012-
// Luba Tang <lubatang@gmail.com>
//===----------------------------------------------------------------------===//
#ifndef LUBA_PAINTER_H
#define LUBA_PAINTER_H
#include <Triangle/Vertex.h>

namespace luba {

class FrameBuffer;
class Space;
class Camera;
class Light;
class Material;
class Vertex;
class Line;
class Triangle;
class Model;
class Color;

class Painter
{
public:
  explicit Painter(FrameBuffer& pFB, const Camera& pCamera, const Light& pLight);

  bool draw(const Space& pSpace, Model& pModel, bool pSolid) const;

  bool draw(const Triangle& pTriangle, const Material& pMaterial) const;
  bool draw(const Line& pLine, const Material& pMaterial) const;
  bool draw(const Vertex& pVertex, const Material& pMaterial) const;

private:
  bool drawHorizon(const Vertex& pLeft, const Vertex& pRight,
                   const Material& pMaterial) const;

private:
  FrameBuffer& m_FB;
  const Camera& m_Camera;
  const Light& m_Light;
};

} // end of namespace luba

#endif

