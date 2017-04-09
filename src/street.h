#ifndef STREET_H
#define STREET_H

#include "object.h"

// linux
#ifdef __linux__

#include <GL/gl.h>    // OpenGL itself. Linux
#include <GL/glu.h>   // GLU support library. Linux
#include <GL/glut.h>  // GLUT support library. Linux

// windows
#else

#include <GL\glut.h> // Windows version

#endif

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

	//-------------------------------------------------------------------- print
	// Brief Description
	//  Prints "S" (Representing "Street") to the console, which can be used
	//  for debugging purposes.
	//
	// Method:    print
	// FullName:  Street::print
	// Access:    public 
	// Returns:   void
	//--------------------------------------------------------------------------
	void print();

	//--------------------------------------------------------- viewCoordinate3D
	// Brief Description
	//  Returns a const reference to the Coordinate3D of the Street
	//
	// Method:    viewCoordinate3D
	// FullName:  Street::viewCoordinate3D
	// Access:    public 
	// Returns:   const Coordinate3D&
	//--------------------------------------------------------------------------
	const Coordinate3D& viewCoordinate3D() const;

private:

};
#endif