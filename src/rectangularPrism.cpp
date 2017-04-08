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
	m_origin[0] = this->m_coordinate3D.viewX();
	m_origin[1] = this->m_coordinate3D.viewY();
	m_origin[2] = this->m_coordinate3D.viewZ();

	GLdouble rv[8][3] = {
		{ m_origin[0] + m_baseWidth, m_origin[1] + m_baseWidth, m_origin[2] },
		{ m_origin[0] - m_baseWidth, m_origin[1] + m_baseWidth, m_origin[2] },
		{ m_origin[0] - m_baseWidth, m_origin[1] - m_baseWidth, m_origin[2] },
		{ m_origin[0] + m_baseWidth, m_origin[1] - m_baseWidth, m_origin[2] },
		{ m_origin[0] + m_baseWidth, m_origin[1] + m_baseWidth, m_origin[2] + m_baseHeight},
		{ m_origin[0] - m_baseWidth, m_origin[1] + m_baseWidth, m_origin[2] + m_baseHeight },
		{ m_origin[0] - m_baseWidth, m_origin[1] - m_baseWidth, m_origin[2] + m_baseHeight },
		{ m_origin[0] + m_baseWidth, m_origin[1] - m_baseWidth, m_origin[2] + m_baseHeight }
	};
	for (uint64_t i = 0; i < 8; i++) {
		for (uint64_t j = 0; j < 3; j++) {
			rectVerts[i][j] = rv[i][j];
		}
	}

}

//------------------------------------------------------------------------- draw
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void RectangularPrism::draw()
{
	glPushMatrix();
	glColor4d(1.0, 0.0, 0.0, 1.0);
	glTranslated(
		this->m_coordinate3D.viewX(), 
		this->m_coordinate3D.viewY(), 
		this->m_coordinate3D.viewZ()
		);
	glBegin(GL_QUADS);	// Base
	glNormal3d(0.0, 0.0, -1.0);
	glVertex2dv(rectVerts[0]);
	glVertex2dv(rectVerts[1]);
	glVertex2dv(rectVerts[2]);
	glVertex2dv(rectVerts[3]);
	glEnd();
	glBegin(GL_QUADS);	// Front
	glNormal3d(0.0, 1.0, 0.0);
	glVertex2dv(rectVerts[0]);
	glVertex2dv(rectVerts[4]);
	glVertex2dv(rectVerts[5]);
	glVertex2dv(rectVerts[1]);
	glEnd();
	glBegin(GL_QUADS);	// Right
	glNormal3d(-1.0, 0.0, 0.0);
	glVertex2dv(rectVerts[0]);
	glVertex2dv(rectVerts[3]);
	glVertex2dv(rectVerts[7]);
	glVertex2dv(rectVerts[4]);
	glEnd();
	glBegin(GL_QUADS);	// Back
	glNormal3d(0.0, -1.0, 0.0);
	glVertex2dv(rectVerts[2]);
	glVertex2dv(rectVerts[6]);
	glVertex2dv(rectVerts[7]);
	glVertex2dv(rectVerts[3]);
	glEnd();
	glBegin(GL_QUADS);	// Left
	glNormal3d(1.0, 0.0, 0.0);
	glVertex2dv(rectVerts[1]);
	glVertex2dv(rectVerts[5]);
	glVertex2dv(rectVerts[6]);
	glVertex2dv(rectVerts[2]);
	glEnd();
	glBegin(GL_QUADS);	// Top
	glNormal3d(0.0, 0.0, 1.0);
	glVertex2dv(rectVerts[4]);
	glVertex2dv(rectVerts[7]);
	glVertex2dv(rectVerts[6]);
	glVertex2dv(rectVerts[5]);
	glEnd();

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
