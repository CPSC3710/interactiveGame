#ifndef CYLINDER_H
#define CYLINDER_H

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

class Cylinder : public Object {
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
  Cylinder(const Coordinate3D& coordinate);

  // Cody Barnson - Apr 8, 2017
  // Sets the private member variables for this object's scale of each component
  void setScale(float scaleX, float scaleY, float scaleZ);

  // Sets the INITIAL rotation values for this object.  These serve as the base
  // line values, they do not change on a per draw call basis.
  void setRotate(float angle, float x, float y, float z);

  // Sets the continuous rotation values for this object.  'angle' is the
  // starting value (in degrees), which is modified by 'delta' each call, and
  // the rotation occurs about the axis specified by x y z.
  void setRotateDelta(float angle, float x, float y, float z, float delta);

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
  GLUquadric* m_quad;
  float m_scale[3] = {1.0, 1.0, 1.0};        // x, y, z
  float m_rotate[4] = {0.0, 0.0, 0.0, 0.0};  // Initial or base-line setting for
                                             // rotation of entire 3D cylinder;
                                             // order is angle (degrees), axis
                                             // of rotation x, y, z
  float m_rotateDelta[5] = {0.0, 0.0, 0.0, 0.0,
                            0.0};  // setting for continuous rotation; order is
                                   // angle (degrees; this is the value that is
                                   // modified by the 5th element, the delta),
                                   // axis of rotation x, y, z, then delta angle
                                   // change each update
};

#endif