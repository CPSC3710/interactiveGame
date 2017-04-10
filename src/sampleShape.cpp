#include "sampleShape.h"

#include <iostream>

//------------------------------------------------------------------ constructor
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
SampleShape::SampleShape(const Coordinate3D& coordinate) : Object(coordinate)
{

}

//------------------------------------------------------------------------- draw
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void SampleShape::draw()
{
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

//------------------------------------------------------------------------ Print
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void SampleShape::print()
{
	std::cout << "C";
}

//------------------------------------------------------------- viewCoordinate3D
// Implementation notes:
//  Self explanatory
//------------------------------------------------------------------------------
const Coordinate3D& SampleShape::viewCoordinate3D() const
{
	return this->m_coordinate3D;
}