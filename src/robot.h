#ifndef ROBOT_H
#define ROBOT_H

#include "object.h"

#include <GL/gl.h>    // OpenGL itself. Linux
#include <GL/glu.h>   // GLU support library. Linux
#include <GL/glut.h>  // GLUT support library. Linux

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

  // March 27, Cody
  // if the robot is at a location where it is valid to turn (intersection),
  // then update the robotDirection index (relative to the DIRECTION array),
  // and write the new value for angleRobot respective to this new value
  void turnRobotLeft();
  void turnRobotRight();

  // If valid, moves the robot 'forward'.  Where forward is the direction the
  // robot is currently facing
  void moveRobotForward();

 private:
  //--------------------------------------------------------------------------
  // helper functions
  //--------------------------------------------------------------------------
  bool robotInBound(
      int32_t x, int32_t y,
      int32_t z);  // TODO: add implementation based on boundary of grid

  // uses the vertices stored in private member base to draw the base of the
  // robot as specified in the assignment.  Note this allow draws the extra
  // shapes on the exterior like the inner rect on the front and the triangles
  // on the back
  void drawRobotBase();

  // uses the vertices stored in private member head to draw the head of the
  // robot.  TODO: add the neck piece, the cylinder eyes, and the rotating
  // antenna.
  void drawRobotHead();

  // enables turning
  bool robotAtIntersection = true;

  const int32_t DIRECTION[4] = {0, -90, -180, -270};
  uint32_t robotDirection = 0;  // an index, the refers to position in DIRECTION
                                // to infer the rotation direction of base robot

  const int32_t dx[4] = {0, 1, 0, -1};
  const int32_t dy[4] = {0, 0, 0, 0};
  const int32_t dz[4] = {-1, 0, 1, 0};

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
};

#endif