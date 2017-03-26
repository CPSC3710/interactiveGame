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

}

//------------------------------------------------------------------------- draw
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void TriangularPrism::draw()
{

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
