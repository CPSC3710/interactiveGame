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

}

//------------------------------------------------------------------------- draw
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void RectangularPrism::draw()
{

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
