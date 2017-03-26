#ifndef ROBOT_H
#define ROBOT_H

#include "object.h"

class Robot : public Object
{
public:

	//-------------------------------------------------------------- constructor
	// Brief Description
	//  Constructor for the Robot
	//
	// Method:    Robot
	// FullName:  Robot::Robot
	// Access:    public 
	// Returns:   None
	// Parameter: const Coordinate3D& coordinate
	//--------------------------------------------------------------------------
	Robot(
		const Coordinate3D& coordinate);

	//--------------------------------------------------------------------- draw
	// Brief Description
	//  Draws the Robot to the screen at its X Y Z coordinates.
	//
	// Method:    draw
	// FullName:  Robot::draw
	// Access:    public 
	// Returns:   void
	//--------------------------------------------------------------------------
	void draw();

	//-------------------------------------------------------------------- print
	// Brief Description
	//  Prints "B" (Representing "Bot" of "Robot") to the console, which
	//  can be used for debugging purposes.
	//
	// Method:    print
	// FullName:  Robot::print
	// Access:    public 
	// Returns:   void
	//--------------------------------------------------------------------------
	void print();

	//--------------------------------------------------------- viewCoordinate3D
	// Brief Description
	//  Returns a const reference to the Coordinate3D of the Robot
	//
	// Method:    viewCoordinate3D
	// FullName:  Robot::viewCoordinate3D
	// Access:    public 
	// Returns:   const Coordinate3D&
	//--------------------------------------------------------------------------
	const Coordinate3D& viewCoordinate3D() const;

private:

};

#endif