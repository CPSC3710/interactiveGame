#ifndef RECTANGULARPRISM_H
#define RECTANGULARPRISM_H

#include "object.h"

class RectangularPrism : public Object
{
public:

	//-------------------------------------------------------------- constructor
	// Brief Description
	//  Constructor for a Rectangular Prism
	//
	// Method:    RectangularPrism
	// FullName:  RectangularPrism::RectangularPrism
	// Access:    public 
	// Returns:   None
	// Parameter: const Coordinate3D& coordinate
	//--------------------------------------------------------------------------
	RectangularPrism(
		const Coordinate3D& coordinate);

	//--------------------------------------------------------------------- draw
	// Brief Description
	//  Draws the Rectangular Prism to the screen at its X Y Z coordinates.
	//
	// Method:    draw
	// FullName:  RectangularPrism::draw
	// Access:    public 
	// Returns:   void
	//--------------------------------------------------------------------------
	void draw();

	//-------------------------------------------------------------------- print
	// Brief Description
	//  Prints "R" (Representing "RectangularPrism") to the console, which
	//  can be used for debugging purposes.
	//
	// Method:    print
	// FullName:  RectangularPrism::print
	// Access:    public 
	// Returns:   void
	//--------------------------------------------------------------------------
	void print();

	//--------------------------------------------------------- viewCoordinate3D
	// Brief Description
	//  Returns a const reference to the Coordinate3D of the RectangularPrism
	//
	// Method:    viewCoordinate3D
	// FullName:  RectangularPrism::viewCoordinate3D
	// Access:    public 
	// Returns:   const Coordinate3D&
	//--------------------------------------------------------------------------
	const Coordinate3D& viewCoordinate3D() const;

private:

};

#endif