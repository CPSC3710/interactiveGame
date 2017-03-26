#include "cylinder.h"

#include <iostream>

//------------------------------------------------------------------ constructor
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
Cylinder::Cylinder(
	const Coordinate3D& coordinate) :
	Object(coordinate)
{

}

//------------------------------------------------------------------------- draw
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void Cylinder::draw()
{

}

//------------------------------------------------------------------------ Print
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void Cylinder::print()
{
	std::cout << "C";
}

//------------------------------------------------------------- viewCoordinate3D
// Implementation notes:
//  Self explanatory
//------------------------------------------------------------------------------
const Coordinate3D& Cylinder::viewCoordinate3D() const
{
	return this->m_coordinate3D;
}
