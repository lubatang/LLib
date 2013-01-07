#ifndef TA_IMAGE_H
#define TA_IMAGE_H

#include <vector>
#include <stdio.h>
#include <string>

class Image
{
public:
  class PixelColor
  {
  public:
    PixelColor() {
      this->color[0] = this->color[1] = this->color[2] = 0.0f;
    }

    float color[3];
  };

public:
  Image();
  virtual ~Image();
    
  std::vector<PixelColor> data;

  //the width and the height of the image
  int width;
  int height;

  //read the image and store it at the data
  bool read(const char* pFileName);
    
  //modify here
  //-------------------------------------------------------------------------
  //get the pixel color at (u,v)
  //u,v are between 0.0 and 1.0
  //....
  //-------------------------------------------------------------------------
};

#endif

