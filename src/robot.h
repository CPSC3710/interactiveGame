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
	// Parameter: None
	//--------------------------------------------------------------------------
	Robot();

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

private:

};

#endif