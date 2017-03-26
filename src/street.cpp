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

}

//------------------------------------------------------------------------- draw
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void Street::draw()
{

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

