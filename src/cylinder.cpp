#include "cylinder.h"

#include <iostream>

//------------------------------------------------------------------ constructor
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
Cylinder::Cylinder(const Coordinate3D& coordinate) : Object(coordinate) {
  this->m_quad = gluNewQuadric();
  gluQuadricNormals(this->m_quad, GLU_SMOOTH);
}

// Sets the private member variables for this object's scale of each component
void Cylinder::setScale(float scaleX, float scaleY, float scaleZ) {
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
void Cylinder::setRotate(float angle, float x, float y, float z) {
  this->m_rotate[0] = angle;
  this->m_rotate[1] = x;
  this->m_rotate[2] = y;
  this->m_rotate[3] = z;
}

// Sets the continuous rotation values for this object.  'angle' is the
// starting value (in degrees), which is modified by 'delta' each call, and
// the rotation occurs about the axis specified by x y z.
void Cylinder::setRotateDelta(float angle, float x, float y, float z,
                              float delta) {
  this->m_rotateDelta[0] = angle;
  this->m_rotateDelta[1] = x;
  this->m_rotateDelta[2] = y;
  this->m_rotateDelta[3] = z;
  this->m_rotateDelta[4] = delta;
}

//------------------------------------------------------------------------- draw
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void Cylinder::draw() {
  glPushMatrix();
  // translate according to coordinate position
  glTranslatef(static_cast<float>(this->viewCoordinate3D().viewX()),
               static_cast<float>(this->viewCoordinate3D().viewY()),
               static_cast<float>(this->viewCoordinate3D().viewZ()));
  // set scale of entire cylinder object
  glScalef(this->m_scale[0], this->m_scale[1], this->m_scale[2]);
  // set initial, base-line rotation for entire cylinder object
  glRotatef(this->m_rotate[0], this->m_rotate[1], this->m_rotate[2],
            this->m_rotate[3]);

  // glPushMatrix();  // update the rotation according to delta setting here
  glRotatef(this->m_rotateDelta[0], this->m_rotateDelta[1],
            this->m_rotateDelta[2], this->m_rotateDelta[3]);

  // top circular face; yellow
  glPushMatrix();
  glTranslatef(0, 0, 1);
  glColor3f(1, 1, 0);
  gluDisk(this->m_quad, 0, 1, 16, 10);
  glPopMatrix();

  // bottom circular face; light blue
  glPushMatrix();
  glTranslatef(0, 0, 0);
  glRotatef(180, 1, 0, 0);
  glColor3f(0, 1, 1);
  gluDisk(this->m_quad, 0, 1, 16, 10);
  glPopMatrix();

  // draw the wrapping rect for the cylinder
  glPushMatrix();
  glColor3f(1, 0, 0);
  gluQuadricTexture(this->m_quad, 1);
  gluCylinder(this->m_quad, 1, 1, 1, 16, 10);
  glPopMatrix();

  // update the angle for rotateDelta using the delta change
  this->m_rotateDelta[0] += this->m_rotateDelta[4];
  /*std::cout << this->m_rotateDelta[0] << ", " << this->m_rotateDelta[4]
            << std::endl;*/
  // glPopMatrix();

  glPopMatrix();
}

//------------------------------------------------------------------------ Print
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void Cylinder::print() { std::cout << "C"; }

//------------------------------------------------------------- viewCoordinate3D
// Implementation notes:
//  Self explanatory
//------------------------------------------------------------------------------
const Coordinate3D& Cylinder::viewCoordinate3D() const {
  return this->m_coordinate3D;
}
