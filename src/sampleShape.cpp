#include "sampleShape.h"

#include <iostream>

float angle = 0;
//------------------------------------------------------------------ constructor
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
SampleShape::SampleShape(const Coordinate3D& coordinate) : Object(coordinate) {}

//------------------------------------------------------------------------- draw
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void SampleShape::draw() {
  glPushMatrix();
  glTranslatef(static_cast<float>(this->viewCoordinate3D().viewX()),
               static_cast<float>(this->viewCoordinate3D().viewY()),
               static_cast<float>(this->viewCoordinate3D().viewZ()));
  // set scale of entire object
  glScalef(this->m_scale[0], this->m_scale[1], this->m_scale[2]);
  // set initial, base-line rotation for entire object
  glRotatef(this->m_rotate[0], this->m_rotate[1], this->m_rotate[2],
            this->m_rotate[3]);
  // update the rotation according to delta setting here
  glRotatef(this->m_rotateDelta[0], this->m_rotateDelta[1],
            this->m_rotateDelta[2], this->m_rotateDelta[3]);

  // draw faces
  glBegin(GL_QUADS);

  glColor3f(1, 0, 0);  // front
  glVertex3f(1, 0, 1);
  glVertex3f(1, 1, 1);
  glVertex3f(0, 1, 1);
  glVertex3f(0, 0, 1);

  glColor3f(0, 1, 0);  // right
  glVertex3f(1, 0, 0);
  glVertex3f(1, 1, 0);
  glVertex3f(1, 1, 1);
  glVertex3f(1, 0, 1);

  glColor3f(0, 0, 1);  // back
  glVertex3f(0, 0, 0);
  glVertex3f(0, 1, 0);
  glVertex3f(1, 1, 0);
  glVertex3f(1, 0, 0);

  glColor3f(1, 1, 0);  // left
  glVertex3f(0, 0, 1);
  glVertex3f(0, 1, 1);
  glVertex3f(0, 1, 0);
  glVertex3f(0, 0, 0);

  glColor3f(0, 1, 1);  // bottom face
  glVertex3f(1, 0, 1);
  glVertex3f(0, 0, 1);
  glVertex3f(0, 0, 0);
  glVertex3f(1, 0, 0);

  glColor3f(1, 0, 1);  // top face
  glVertex3f(0, 1, 0);
  glVertex3f(0, 1, 1);
  glVertex3f(1, 1, 1);
  glVertex3f(1, 1, 0);

  glEnd();

  // update the angle for rotateDelta using the delta change
  this->m_rotateDelta[0] += this->m_rotateDelta[4];
  glPopMatrix();  // done all

  // GLUquadric* quad = gluNewQuadric();
  // gluQuadricNormals(quad, GLU_SMOOTH);
  /*glPushMatrix();
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
  glPopMatrix();*/
}

// Sets the private member variables for this object's scale of each component
void SampleShape::setScale(float scaleX, float scaleY, float scaleZ) {
  float EPS = 0.0001;  // epsilon, some practical minimum scale for each part
  if (scaleX < EPS) scaleX = EPS;
  if (scaleY < EPS) scaleY = EPS;
  if (scaleZ < EPS) scaleZ = EPS;
  this->m_scale[0] = scaleX;
  this->m_scale[1] = scaleY;
  this->m_scale[2] = scaleZ;
}

// Sets the INITIAL rotation values for this object.  These serve as the base
// line values, they do not change on a per draw call basis.
void SampleShape::setRotate(float angle, float x, float y, float z) {
  this->m_rotate[0] = angle;
  this->m_rotate[1] = x;
  this->m_rotate[2] = y;
  this->m_rotate[3] = z;
}

// Sets the continuous rotation values for this object.  'angle' is the
// starting value (in degrees), which is modified by 'delta' each call, and
// the rotation occurs about the axis specified by x y z.
void SampleShape::setRotateDelta(float angle, float x, float y, float z,
                                 float delta) {
  this->m_rotateDelta[0] = angle;
  this->m_rotateDelta[1] = x;
  this->m_rotateDelta[2] = y;
  this->m_rotateDelta[3] = z;
  this->m_rotateDelta[4] = delta;
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