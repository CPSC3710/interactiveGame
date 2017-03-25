#include "coordinate3d.h"

//------------------------------------------------------------------ constructor
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
Coordinate3D::Coordinate3D(
	const int64_t& x,
	const int64_t& y,
	const int64_t& z)
{
	this->m_x = x;
	this->m_y = y;
	this->m_z = z;
}

//------------------------------------------------------------------------ viewX
// Implementation notes:
//  Self explanatory
//------------------------------------------------------------------------------
const int64_t& Coordinate3D::viewX() const
{
	return this->m_x;
}

//------------------------------------------------------------------------ viewY
// Implementation notes:
//  Self explanatory
//------------------------------------------------------------------------------
const int64_t& Coordinate3D::viewY() const
{
	return this->m_y;
}

//------------------------------------------------------------------------ viewZ
// Implementation notes:
//  Self explanatory
//------------------------------------------------------------------------------
const int64_t& Coordinate3D::viewZ() const
{
	return this->m_z;
}