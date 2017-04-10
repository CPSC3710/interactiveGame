#ifndef TRIANGULARPRISM_H
#define TRIANGULARPRISM_H

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

	//-------------------------------------------------------------------- print
	// Brief Description
	//  Prints "T" (Representing "TriangularPrism") to the console, which 
	//  can be used for debugging purposes.
	//
	// Method:    print
	// FullName:  TriangularPrism::print
	// Access:    public 
	// Returns:   void
	//--------------------------------------------------------------------------
	void print();

	//--------------------------------------------------------- viewCoordinate3D
	// Brief Description
	//  Returns a const reference to the Coordinate3D of the TriangularPrism
	//
	// Method:    viewCoordinate3D
	// FullName:  TriangularPrism::viewCoordinate3D
	// Access:    public 
	// Returns:   const Coordinate3D&
	//--------------------------------------------------------------------------
   const Coordinate3D& viewCoordinate3D() const;

    bool isDestroyable() const override;

private:

};
#endif
