#include "street.h"

#include <iostream>

//------------------------------------------------------------------ constructor
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
Street::Street(
	const Coordinate3D& coordinate) :
	Object(coordinate)
{
	m_origin[0] = this->viewCoordinate3D().viewX();
	m_origin[1] = this->viewCoordinate3D().viewY();
	m_origin[2] = this->viewCoordinate3D().viewZ();

	GLdouble sv[4][3] = {
		{m_origin[0] + m_baseWidth, m_origin[1] + m_baseWidth, m_origin[2]},
		{m_origin[0] - m_baseWidth, m_origin[1] + m_baseWidth, m_origin[2]},
		{m_origin[0] - m_baseWidth, m_origin[1] - m_baseWidth, m_origin[2]},
		{m_origin[0] + m_baseWidth, m_origin[1] + m_baseWidth, m_origin[2]}
	};
	//for (uint64_t i = 0; i < 8; i++) {
	//	for (uint64_t j = 0; j < 3; j++) {
	//		m_streetVert[i][j] = sv[i][j];
	//	}
	//}

}

//------------------------------------------------------------------------- draw
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void Street::draw()
{
	//glPushMatrix();

	//glTranslated(
	//	this->m_coordinate3D.viewX(),
	//	this->m_coordinate3D.viewY(),
	//	this->m_coordinate3D.viewZ()
	//);

	//glColor4d(0.8, 0.8, 0.8, 1.0);

	//glBegin(GL_QUADS);
	//glNormal3d(0.0, 0.0, 1.0);

	//glVertex3dv(m_streetVert[0]);
	//glVertex3dv(m_streetVert[1]);
	//glVertex3dv(m_streetVert[2]);
	//glVertex3dv(m_streetVert[3]);

	//glEnd();

	//glPopMatrix();
}

//------------------------------------------------------------------------ Print
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void Street::print()
{
	std::cout << "S";
}

//------------------------------------------------------------- viewCoordinate3D
// Implementation notes:
//  Self explanatory
//------------------------------------------------------------------------------
const Coordinate3D& Street::viewCoordinate3D() const
{
	return this->m_coordinate3D;
}

