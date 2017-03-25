#ifndef TRIANGULARPRISM_H
#define TRIANGULARPRISM_H

#include "object.h"

class TriangularPrism : public Object
{
public:

	//-------------------------------------------------------------- constructor
	// Brief Description
	//  Constructor for a Triangular Prism
	//
	// Method:    TriangularPrism
	// FullName:  TriangularPrism::TriangularPrism
	// Access:    public 
	// Returns:   None
	// Parameter: const Coordinate3D& coordinate
	//--------------------------------------------------------------------------
	TriangularPrism(
		const Coordinate3D& coordinate);

	//--------------------------------------------------------------------- draw
	// Brief Description
	//  Draws the Triangular Prism to the screen at its X Y Z coordinates.
	//
	// Method:    draw
	// FullName:  TriangularPrism::draw
	// Access:    public 
	// Returns:   void
	//--------------------------------------------------------------------------
	void draw();

private:

};
#endif