#include "sampleShape.h"

#include <iostream>

float angle = 0;
//------------------------------------------------------------------ constructor
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
SampleShape::SampleShape(const Coordinate3D& coordinate) : Object(coordinate) {
  quad = gluNewQuadric();
  gluQuadricNormals(quad, GLU_SMOOTH);
}

//------------------------------------------------------------------------- draw
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void SampleShape::draw() {
  // GLUquadric* quad = gluNewQuadric();
  // gluQuadricNormals(quad, GLU_SMOOTH);
  glPushMatrix();
  // glRotated(90., 1., 0., 0.);
  glTranslatef(0, 0, 0);

  // glPushMatrix();
  glScalef(0.5, 3, 0.5);
  glRotatef(-90, 1, 0, 0);

  // gluCylinder(quad, 1, 1, 2, 36, 24);
  // forward facing top yellow face.
  glPushMatrix();
  glTranslatef(0, 0, 1);
  glColor3f(1, 1, 0);
  gluDisk(quad, 0, 1, 16, 10);
  glPopMatrix();

  // backward facing bottom light blue face.
  glPushMatrix();
  glTranslatef(0, 0, 0);
  glRotatef(180, 1, 0, 0);
  glColor3f(0, 1, 1);
  gluDisk(quad, 0, 1, 16, 10);
  glPopMatrix();

  // draw the wrapping rect for the cylinder
  glPushMatrix();
  glColor3f(1, 0, 0);
  // glTranslatef(0, 0, 0);
  gluCylinder(quad, 1, 1, 1, 16, 10);
  glPopMatrix();

  angle -= 0.5;
  // glPopMatrix();
  glPopMatrix();
}

//------------------------------------------------------------------------ Print
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void SampleShape::print() { std::cout << "C"; }

//------------------------------------------------------------- viewCoordinate3D
// Implementation notes:
//  Self explanatory
//------------------------------------------------------------------------------
const Coordinate3D& SampleShape::viewCoordinate3D() const {
  return this->m_coordinate3D;
}