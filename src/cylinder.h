#ifndef CYLINDER_H
#define CYLINDER_H

#include "object.h"

class Cylinder : public Object
{
public:

	//-------------------------------------------------------------- constructor
	// Brief Description
	//  Constructor for a Cylinder
	//
	// Method:    Cylinder
	// FullName:  Cylinder::Cylinder
	// Access:    public 
	// Returns:   None
	// Parameter: const Coordinate3D& coordinate
	//--------------------------------------------------------------------------
	Cylinder(
		const Coordinate3D& coordinate);

	//--------------------------------------------------------------------- draw
	// Brief Description
	//  Draws the Cylinder to the screen at its X Y Z coordinates.
	//
	// Method:    draw
	// FullName:  Cylinder::draw
	// Access:    public 
	// Returns:   void
	//--------------------------------------------------------------------------
	void draw();

private:

};

#endif