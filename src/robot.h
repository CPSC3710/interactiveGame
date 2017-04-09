#ifndef ROBOT_H
#define ROBOT_H

#include "cylinder.h"
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

class Robot : public Object {
 public:
  //-------------------------------------------------------------- constructor
  // Brief Description
  //  Constructor for the Robot
  //
  // Method:    Robot
  // FullName:  Robot::Robot
  // Access:    public
  // Returns:   None
  // Parameter: const Coordinate3D& coordinate
  //--------------------------------------------------------------------------
  Robot(const Coordinate3D& coordinate);

  // Constructor that also sets the maximum grid dimensions for the robot
  /* Robot(const Coordinate3D& coordinate, const uint64_t gridMax);*/

  //--------------------------------------------------------------------- draw
  // Brief Description
  //  Draws the Robot to the screen at its X Y Z coordinates.
  //
  // Method:    draw
  // FullName:  Robot::draw
  // Access:    public
  // Returns:   void
  //--------------------------------------------------------------------------
  void draw();

  //-------------------------------------------------------------------- print
  // Brief Description
  //  Prints "B" (Representing "Bot" of "Robot") to the console, which
  //  can be used for debugging purposes.
  //
  // Method:    print
  // FullName:  Robot::print
  // Access:    public
  // Returns:   void
  //--------------------------------------------------------------------------
  void print();

  //--------------------------------------------------------- viewCoordinate3D
  // Brief Description
  //  Returns a const reference to the Coordinate3D of the Robot
  //
  // Method:    viewCoordinate3D
  // FullName:  Robot::viewCoordinate3D
  // Access:    public
  // Returns:   const Coordinate3D&
  //--------------------------------------------------------------------------
  const Coordinate3D& viewCoordinate3D() const;

  //---------------------------------------------------------- attemptLeftTurn
  // Brief Description
  //  Attempts to turn the robot left. This is only possible at an
  //  intersection, or fork (edge of the grid/city)
  //
  // Method:    attemptLeftTurn
  // FullName:  Robot::attemptLeftTurn
  // Access:    public
  // Returns:   void
  //--------------------------------------------------------------------------
  void attemptLeftTurn();

  //--------------------------------------------------------- attemptRightTurn
  // Brief Description
  //  Attempts to turn the robot right. This is only possible at an
  //  intersection, or fork (edge of the grid/city)
  //
  // Method:    attemptRightTurn
  // FullName:  Robot::attemptRightTurn
  // Access:    public
  // Returns:   void
  //--------------------------------------------------------------------------
  void attemptRightTurn();

  //------------------------------------------------------- attemptMoveForward
  // Brief Description
  //  Attempts to move the robot forward. This is only possible if the move
  //  forward is still within the bounds of the grid/city.
  //  intersection, or fork (edge of the grid/city)
  //
  // Method:    attemptMoveForward
  // FullName:  Robot::attemptMoveForward
  // Access:    public
  // Returns:   bool
  //--------------------------------------------------------------------------
  bool attemptMoveForward();

  // move robot to 0, 0
  void resetPositionToOrigin();

  // Cody Barnson, Apr 8, 2017
  void turnHeadRight();
  void turnHeadLeft();
  void turnHeadForward();

 private:
  bool isPositionInBounds(int32_t x, int32_t y) const;
  bool isPositionOnStreet(int32_t x, int32_t y) const;
  bool isRobotAtIntersection() const;

  //-----------------------------------------------------------------
  // drawBase
  // Brief Description
  //  Helper function of draw which draws the base of the robot.
  //
  // Method:    drawBase
  // FullName:  Robot::drawBase
  // Access:    public
  // Returns:   void
  //--------------------------------------------------------------------------
  void drawBase();

  //----------------------------------------------------------------- drawHead
  // Brief Description
  //  Helper function of draw which draws the head of the robot.
  //
  // Method:    drawHead
  // FullName:  Robot::drawHead
  // Access:    public
  // Returns:   void
  //--------------------------------------------------------------------------
  void drawHead();

  // enables turning
  bool robotAtIntersection = true;

  const int32_t DIRECTION[4] = {0, -90, -180, -270};

  // an index, the refers to position in DIRECTION
  // to infer the rotation direction of base robot
  uint32_t robotDirection = 0;

  // N E S W === updated for "Z is up".
  const int32_t dx[4] = {0, 1, 0, -1};
  const int32_t dy[4] = {1, 0, -1, 0};
  const int32_t dz[4] = {0, 0, 0, 0};

  int32_t angleRobotBase = 0;
  int32_t angleRobotHead = 0;

  int32_t angleFaceLeft = 45;
  int32_t angleFaceRight = -45;
  int32_t angleFaceForward = 0;

  GLfloat origin[3];
  GLfloat baseHeight = 1.5;
  GLfloat baseWidth = 0.5;

  GLfloat originHead[3];
  GLfloat headHeight = 0.5;
  GLfloat headWidth = 0.25;

  GLfloat base[8][3];
  GLfloat head[8][3];

  Cylinder m_antenna = Cylinder(Coordinate3D(0, 0, 0));
  Cylinder m_eyeLeft = Cylinder(Coordinate3D(0, 0, 0));
  Cylinder m_eyeRight = Cylinder(Coordinate3D(0, 0, 0));
  Cylinder m_neck = Cylinder(Coordinate3D(0, 0, 0));

  // SampleShape m_body = SampleShape(Coordinate3D(0, 0, 0));
};

#endif
