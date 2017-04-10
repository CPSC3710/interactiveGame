#include "rectangularPrism.h"

#include <iostream>

//------------------------------------------------------------------ constructor
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
RectangularPrism::RectangularPrism(
   const Coordinate3D& coordinate) :
   Object(coordinate)
{
   this->m_quad = gluNewQuadric();
   gluQuadricNormals(this->m_quad, GLU_SMOOTH);   
}

//------------------------------------------------------------------------- draw
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void RectangularPrism::draw()
{
   glPushMatrix();
   // translate according to coordinate position
   glTranslatef(static_cast<float>(this->viewCoordinate3D().viewX()) + 0.5,
		static_cast<float>(this->viewCoordinate3D().viewY()) + 0.5,
		static_cast<float>(this->viewCoordinate3D().viewZ()));
   // set scale of entire cylinder object
   // glScalef(this->m_scale[0], this->m_scale[1], this->m_scale[2]);
   // set initial, base-line rotation for entire cylinder object
   // glRotatef(this->m_rotate[0], this->m_rotate[1], this->m_rotate[2],
   //           this->m_rotate[3]);

   // glPushMatrix();  // update the rotation according to delta setting here
   // glRotatef(this->m_rotateDelta[0], this->m_rotateDelta[1],
   //           this->m_rotateDelta[2], this->m_rotateDelta[3]);

   // top circular face; blue
   glPushMatrix();
   glTranslatef(0, 0, 1.5);
   glColor3f(1, 0, 1);
   gluDisk(this->m_quad, 0, 0.4, 4, 10);
   glPopMatrix();

   // bottom circular face; light blue
   glPushMatrix();
   glTranslatef(0, 0, 0);
   glRotatef(180, 1, 0, 0);
   glColor3f(0, 1, 1);
   gluDisk(this->m_quad, 0, 0.4, 4, 10);
   glPopMatrix();

   // draw the wrapping rect for the cylinder
   glPushMatrix();
   glColor3f(1, 0, 1);
   gluQuadricTexture(this->m_quad, 1);
   gluCylinder(this->m_quad, 0.4, 0.4, 1.5, 4, 10);
   glPopMatrix();

   // update the angle for rotateDelta using the delta change
   // this->m_rotateDelta[0] += this->m_rotateDelta[4];
   /*std::cout << this->m_rotateDelta[0] << ", " << this->m_rotateDelta[4]
     << std::endl;*/
   // glPopMatrix();

   glPopMatrix();

}

//------------------------------------------------------------------------ Print
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void RectangularPrism::print()
{
   std::cout << "R";
}

//------------------------------------------------------------- viewCoordinate3D
// Implementation notes:
//  Self explanatory
//------------------------------------------------------------------------------
const Coordinate3D& RectangularPrism::viewCoordinate3D() const
{
   return this->m_coordinate3D;
}

bool RectangularPrism::isDestroyable() const {
   return true;
}
