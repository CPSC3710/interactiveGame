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
	// Parameter: None
	//--------------------------------------------------------------------------
	RectangularPrism();

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

private:

};

#endif