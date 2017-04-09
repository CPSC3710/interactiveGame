#include "sampleShape.h"

#include <iostream>

/*float angle = 0;*/
//------------------------------------------------------------------ constructor
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
SampleShape::SampleShape(const Coordinate3D& coordinate) : Object(coordinate) {
  /*float vv[8][3] = {{1, -1, 1},  {1, 1, 1},  {-1, 1, 1},  {-1, -1, 1},
                    {1, -1, -1}, {1, 1, -1}, {-1, 1, -1}, {-1, -1, -1}};

  float origin[3];
  origin[0] = static_cast<float>(this->m_coordinate3D.viewX());
  origin[1] = static_cast<float>(this->m_coordinate3D.viewY());
  origin[2] = static_cast<float>(this->m_coordinate3D.viewZ());

  // write values into our member variables
  for (int32_t i = 0; i < 8; i++) {
    for (int32_t j = 0; j < 3; j++) {
      this->m_verts[i][j] = vv[i][j] + origin[j];
    }
  }*/
}

//------------------------------------------------------------------------- draw
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void SampleShape::draw() {
  glBegin(GL_QUADS);                // Draw The Cube Using quads
  glColor3f(0.0f, 1.0f, 0.0f);      // Color Blue
  glVertex3f(1.0f, 1.0f, -1.0f);    // Top Right Of The Quad (Top)
  glVertex3f(-1.0f, 1.0f, -1.0f);   // Top Left Of The Quad (Top)
  glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)
  glVertex3f(1.0f, 1.0f, 1.0f);     // Bottom Right Of The Quad (Top)
  glColor3f(1.0f, 0.5f, 0.0f);      // Color Orange
  glVertex3f(1.0f, -1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
  glVertex3f(-1.0f, -1.0f, 1.0f);   // Top Left Of The Quad (Bottom)
  glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Quad (Bottom)
  glVertex3f(1.0f, -1.0f, -1.0f);   // Bottom Right Of The Quad (Bottom)
  glColor3f(1.0f, 0.0f, 0.0f);      // Color Red
  glVertex3f(1.0f, 1.0f, 1.0f);     // Top Right Of The Quad (Front)
  glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
  glVertex3f(-1.0f, -1.0f, 1.0f);   // Bottom Left Of The Quad (Front)
  glVertex3f(1.0f, -1.0f, 1.0f);    // Bottom Right Of The Quad (Front)
  glColor3f(1.0f, 1.0f, 0.0f);      // Color Yellow
  glVertex3f(1.0f, -1.0f, -1.0f);   // Top Right Of The Quad (Back)
  glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Left Of The Quad (Back)
  glVertex3f(-1.0f, 1.0f, -1.0f);   // Bottom Left Of The Quad (Back)
  glVertex3f(1.0f, 1.0f, -1.0f);    // Bottom Right Of The Quad (Back)
  glColor3f(0.0f, 0.0f, 1.0f);      // Color Blue
  glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
  glVertex3f(-1.0f, 1.0f, -1.0f);   // Top Left Of The Quad (Left)
  glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Quad (Left)
  glVertex3f(-1.0f, -1.0f, 1.0f);   // Bottom Right Of The Quad (Left)
  glColor3f(1.0f, 0.0f, 1.0f);      // Color Violet
  glVertex3f(1.0f, 1.0f, -1.0f);    // Top Right Of The Quad (Right)
  glVertex3f(1.0f, 1.0f, 1.0f);     // Top Left Of The Quad (Right)
  glVertex3f(1.0f, -1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
  glVertex3f(1.0f, -1.0f, -1.0f);   // Bottom Right Of The Quad (Right)
  glEnd();                          // End Drawing The Cube - See more at:
}

// Sets the private member variables for this object's scale of each component
/*void SampleShape::setScale(float scaleX, float scaleY, float scaleZ) {
  float EPS = 0.0001;  // epsilon, some practical minimum scale for each part
  if (scaleX < EPS) scaleX = EPS;
  if (scaleY < EPS) scaleY = EPS;
  if (scaleZ < EPS) scaleZ = EPS;
  this->m_scale[0] = scaleX;
  this->m_scale[1] = scaleY;
  this->m_scale[2] = scaleZ;


}*/

// Sets the INITIAL rotation values for this object.  These serve as the base
// line values, they do not change on a per draw call basis.
/*void SampleShape::setRotate(float angle, float x, float y, float z) {
  this->m_rotate[0] = angle;
  this->m_rotate[1] = x;
  this->m_rotate[2] = y;
  this->m_rotate[3] = z;
}*/

// Sets the continuous rotation values for this object.  'angle' is the
// starting value (in degrees), which is modified by 'delta' each call, and
// the rotation occurs about the axis specified by x y z.
/*void SampleShape::setRotateDelta(float angle, float x, float y, float z,
                                 float delta) {
  this->m_rotateDelta[0] = angle;
  this->m_rotateDelta[1] = x;
  this->m_rotateDelta[2] = y;
  this->m_rotateDelta[3] = z;
  this->m_rotateDelta[4] = delta;
}*/

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