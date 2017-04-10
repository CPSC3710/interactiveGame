#ifndef RECTANGULARPRISM_H
#define RECTANGULARPRISM_H

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

class RectangularPrism : public Object
{
public:

	//-------------------------------------------------------------- constructor
	// Brief Description
	//  Constructor for a Triangular Prism
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
	//  Draws the Triangular Prism to the screen at its X Y Z coordinates.
	//
	// Method:    draw
	// FullName:  RectangularPrism::draw
	// Access:    public 
	// Returns:   void
	//--------------------------------------------------------------------------
	void draw();

	//-------------------------------------------------------------------- print
	// Brief Description
	//  Prints "T" (Representing "RectangularPrism") to the console, which 
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

    bool isDestroyable() const override;

private:
   GLUquadric* m_quad;
};
#endif
