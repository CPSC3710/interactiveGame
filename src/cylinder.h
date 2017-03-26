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

	//-------------------------------------------------------------------- print
	// Brief Description
	//  Prints "C" (Representing "Cylinder") to the console, which can be used
	//  for debugging purposes.
	//
	// Method:    print
	// FullName:  Cylinder::print
	// Access:    public 
	// Returns:   void
	//--------------------------------------------------------------------------
	void print();

	//--------------------------------------------------------- viewCoordinate3D
	// Brief Description
	//  Returns a const reference to the Coordinate3D of the Cylinder
	//
	// Method:    viewCoordinate3D
	// FullName:  Cylinder::viewCoordinate3D
	// Access:    public 
	// Returns:   const Coordinate3D&
	//--------------------------------------------------------------------------
	const Coordinate3D& viewCoordinate3D() const;

private:

};

#endif