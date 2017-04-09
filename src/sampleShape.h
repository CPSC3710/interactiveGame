#ifndef SAMPLESHAPE_H
#define SAMPLESHAPE_H

#include "object.h"

#include <GL/gl.h>    // OpenGL itself. Linux
#include <GL/glu.h>   // GLU support library. Linux
#include <GL/glut.h>  // GLUT support library. Linux

class SampleShape : public Object {
 public:
  SampleShape(const Coordinate3D& coordinate);

  void draw();
  void print();

  const Coordinate3D& viewCoordinate3D() const;

 private:
  GLUquadric* quad;
};

#endif