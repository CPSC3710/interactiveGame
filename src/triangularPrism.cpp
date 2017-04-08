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
	m_origin[0] = this->m_coordinate3D.viewX();
	m_origin[1] = this->m_coordinate3D.viewY();
	m_origin[2] = this->m_coordinate3D.viewZ();


	GLdouble tv[5][3] = {
		{ m_origin[0], m_origin[1], m_origin[2] + m_baseHeight },
		{ m_origin[0] + m_baseWidth, m_origin[1] + m_baseWidth, m_origin[2] },
		{ m_origin[0] - m_baseWidth, m_origin[1] + m_baseWidth, m_origin[2] },
		{ m_origin[0] - m_baseWidth, m_origin[1] - m_baseWidth, m_origin[2] },
		{ m_origin[0] + m_baseWidth, m_origin[1] - m_baseWidth, m_origin[2] }
	};
	for (uint64_t i = 0; i < 5; i++) {
		for (uint64_t j = 0; j < 3; j++) {
			triVerts[i][j] = tv[i][j];
		}
	}

}

//------------------------------------------------------------------------- draw
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void TriangularPrism::draw()
{
	glPushMatrix();
	glColor4d(1.0, 0.0, 0.0, 1.0);
	glTranslated(
		this->m_coordinate3D.viewX(),
		this->m_coordinate3D.viewY(),
		this->m_coordinate3D.viewZ()
	);

	glBegin(GL_TRIANGLE_FAN);
	glVertex3dv(triVerts[0]);
	glVertex3dv(triVerts[1]);
	glVertex3dv(triVerts[2]);
	glVertex3dv(triVerts[3]);
	glVertex3dv(triVerts[4]);

	glEnd();

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
