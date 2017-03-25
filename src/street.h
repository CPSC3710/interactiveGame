#ifndef STREET_H
#define STREET_H

#include "object.h"

class Street : public Object
{
public:

	//-------------------------------------------------------------- constructor
	// Brief Description
	//  Constructor for a Street tile
	//
	// Method:    Street
	// FullName:  Street::Street
	// Access:    public 
	// Returns:   None
	// Parameter: const Coordinate3D& coordinate
	//--------------------------------------------------------------------------
	Street(
		const Coordinate3D& coordinate);

	//--------------------------------------------------------------------- draw
	// Brief Description
	//  Draws a Street tile to the screen at its X Y Z coordinates.
	//
	// Method:    draw
	// FullName:  Street::draw
	// Access:    public 
	// Returns:   void
	//--------------------------------------------------------------------------
	void draw();

private:

};
#endif