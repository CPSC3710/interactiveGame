#ifndef SAMPLESHAPE_H
#define SAMPLESHAPE_H

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

class SampleShape : public Object
{
public:
	SampleShape(const Coordinate3D& coordinate);

	void draw();
	void print();

	const Coordinate3D& viewCoordinate3D() const;
};

#endif