#include "triangularPrism.h"

#include <iostream>

//------------------------------------------------------------------ constructor
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
TriangularPrism::TriangularPrism(
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
void TriangularPrism::draw()
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
   glTranslatef(0, 0, 2);
   glColor3f(0, 1, 0);
   gluDisk(this->m_quad, 0, 0.25, 3, 10);
   glPopMatrix();

   // bottom circular face; light blue
   glPushMatrix();
   glTranslatef(0, 0, 0);
   glRotatef(180, 1, 0, 0);
   glColor3f(0, 1, 1);
   gluDisk(this->m_quad, 0, 0.25, 3, 10);
   glPopMatrix();

   // draw the wrapping rect for the cylinder
   glPushMatrix();
   glColor3f(0, 1, 0);
   gluQuadricTexture(this->m_quad, 1);
   gluCylinder(this->m_quad, 0.25, 0.25, 2.0, 3, 10);
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
void TriangularPrism::print()
{
   std::cout << "T";
}

//------------------------------------------------------------- viewCoordinate3D
// Implementation notes:
//  Self explanatory
//------------------------------------------------------------------------------
const Coordinate3D& TriangularPrism::viewCoordinate3D() const
{
   return this->m_coordinate3D;
}

bool TriangularPrism::isDestroyable() const {
   return true;
}
