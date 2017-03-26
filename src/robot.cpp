#include "robot.h"

#include <iostream>

//------------------------------------------------------------------ constructor
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
Robot::Robot(
	const Coordinate3D& coordinate) :
	Object(coordinate)
{

}

//------------------------------------------------------------------------- draw
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void Robot::draw()
{

}

//------------------------------------------------------------------------ Print
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void Robot::print()
{
	std::cout << "B";
}

//------------------------------------------------------------- viewCoordinate3D
// Implementation notes:
//  Self explanatory
//------------------------------------------------------------------------------
const Coordinate3D& Robot::viewCoordinate3D() const
{
	return this->m_coordinate3D;
}
