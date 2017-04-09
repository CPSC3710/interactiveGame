#include "robot.h"
#include "config.h"

#include <iostream>

//------------------------------------------------------------------ constructor
// Implementation notes:
//  Initializes the vertices of the robots primitive components such as
//  the base and the head
//------------------------------------------------------------------------------
Robot::Robot(const Coordinate3D& coordinate) : Object(coordinate) {
  // initialize origin of the robot
  origin[0] = static_cast<float>(this->m_coordinate3D.viewX());
  origin[1] = static_cast<float>(this->m_coordinate3D.viewY());
  origin[2] = static_cast<float>(this->m_coordinate3D.viewZ());

  // initialize the origin of the robot's head
  originHead[0] = static_cast<float>(origin[0] + baseHeight);
  originHead[1] = static_cast<float>(origin[1] + baseHeight);
  originHead[2] = static_cast<float>(origin[2] + baseHeight);

  // initialize the vertices of the base of the robot
  GLfloat bb[8][3] = {{baseWidth, origin[1] + baseHeight, baseWidth},
                      {-baseWidth, origin[1] + baseHeight, baseWidth},
                      {-baseWidth, origin[1], baseWidth},
                      {baseWidth, origin[1], baseWidth},
                      {baseWidth, origin[1] + baseHeight, -baseWidth},
                      {-baseWidth, origin[1] + baseHeight, -baseWidth},
                      {-baseWidth, origin[1], -baseWidth},
                      {baseWidth, origin[1], -baseWidth}};

  // initialize the vertices of the head of the robot
  GLfloat hh[8][3] = {{headWidth, originHead[1] + headHeight, headWidth},
                      {-headWidth, originHead[1] + headHeight, headWidth},
                      {-headWidth, originHead[1], headWidth},
                      {headWidth, originHead[1], headWidth},
                      {headWidth, originHead[1] + headHeight, -headWidth},
                      {-headWidth, originHead[1] + headHeight, -headWidth},
                      {-headWidth, originHead[1], -headWidth},
                      {headWidth, originHead[1], -headWidth}};

  // write values into our member variables
  for (uint64_t i = 0; i < 8; i++) {
    for (uint64_t j = 0; j < 3; j++) {
      base[i][j] = bb[i][j];
      head[i][j] = hh[i][j];
    }
  }

  // configure antenna
  m_antenna.setScale(0.1, 0.4, 0.1);
  m_antenna.setRotate(-90, 1, 0, 0);
  m_antenna.setRotateDelta(0, 0, 0, 1, 0.3);

  // configure eyes
  m_eyeLeft.setScale(0.07, 0.07, 0.07);
  m_eyeLeft.setRotate(180, 0, 1, 0);
  m_eyeRight.setScale(0.07, 0.07, 0.07);
  m_eyeRight.setRotate(180, 0, 1, 0);

  // configure neck piece
  m_neck.setScale(0.25, 0.2, 0.25);
  m_neck.setRotate(-90, 1, 0, 0);
}

//------------------------------------------------------------------------- draw
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void Robot::draw() {
  glPushMatrix();
  glTranslatef(static_cast<float>(this->m_coordinate3D.viewX()),
               static_cast<float>(this->m_coordinate3D.viewY()),
               static_cast<float>(this->m_coordinate3D.viewZ()));
  glRotatef(static_cast<float>(this->angleRobotBase), 0, 1, 0);

  // draw robot head and rotate based on parameters set by key presses
  glPushMatrix();
  glTranslatef(0, 0.13, 0);  // move up for neck piece
  glRotatef(static_cast<float>(this->angleRobotHead), 0, 1, 0);
  this->drawHead();

  // draw neck piece
  glPushMatrix();
  glTranslatef(0, 1.3, 0);
  m_neck.draw();
  glPopMatrix();

  // draw antenna
  glPushMatrix();
  glTranslatef(0, 1.9, 0);
  m_antenna.draw();
  glPopMatrix();

  // draw eyes
  glPushMatrix();
  glTranslatef(0, 1.75, -0.35);  // shifting reference frame to eye position
  glPushMatrix();
  glTranslatef(-0.1, 0, 0);  // shift left eye to left
  m_eyeLeft.draw();
  glPopMatrix();  // done left eye
  glPushMatrix();
  glTranslatef(0.1, 0, 0);  // shift right eye to right
  m_eyeRight.draw();
  glPopMatrix();  // done right eye
  glPopMatrix();  // done both eyes
  glPopMatrix();  // done drawing head

  this->drawBase();
  glPopMatrix();
}

//------------------------------------------------------------------------ print
// Implementation notes:
//  Prints "B" for "bot" of "Robot"
//------------------------------------------------------------------------------
void Robot::print() { std::cout << "B"; }

//------------------------------------------------------------- viewCoordinate3D
// Implementation notes:
//  Self explanatory
//------------------------------------------------------------------------------
const Coordinate3D& Robot::viewCoordinate3D() const {
  return this->m_coordinate3D;
}

//------------------------------------------------------------- attemptRightTurn
// Implementation notes:
//  If the robot is at a location where it is valid to turn (intersection),
//  then update the robotDirection index (relative to the DIRECTION array),
//  and write the new value for angleRobot respective to this new value
//  Moves FORWARDS circularly through DIRECTION array
//------------------------------------------------------------------------------
void Robot::attemptRightTurn() {
  if (this->robotAtIntersection) {
    this->robotDirection = (this->robotDirection + 1) % 4;

    this->angleRobotBase = this->DIRECTION[this->robotDirection];
  }
}

//-------------------------------------------------------------- attemptLeftTurn
// Implementation notes:
//  If the robot is at a location where it is valid to turn (intersection),
//  then update the robotDirection index (relative to the DIRECTION array),
//  and write the new value for angleRobot respective to this new value.
//  Moves BACKWARDS circularly through DIRECTION array
//------------------------------------------------------------------------------
void Robot::attemptLeftTurn() {
  if (this->robotAtIntersection) {
    this->robotDirection = (this->robotDirection + (4 - 1)) % 4;

    this->angleRobotBase = this->DIRECTION[this->robotDirection];
  }
}

//----------------------------------------------------------- attemptMoveForward
// Implementation notes:
//  Attempts to move the robot forward one grid position. The robot must stay
//  within the boundaries, and the grid position in front of it must be valid
// (eg. a street), if both conditions are met, the robot moves forward.
//------------------------------------------------------------------------------
void Robot::attemptMoveForward() {
  int64_t i = this->robotDirection;
  int64_t x = this->m_coordinate3D.viewX() + this->dx[i];
  int64_t y = this->m_coordinate3D.viewY() + this->dy[i];
  int64_t z = this->m_coordinate3D.viewZ() + this->dz[i];

  // if in boundary, update the coordinate values
  if (positionIsWithinBounds(x, y, z)) {
    this->m_coordinate3D.setX(static_cast<int64_t>(x));
    this->m_coordinate3D.setY(static_cast<int64_t>(y));
    this->m_coordinate3D.setZ(static_cast<int64_t>(z));
  }
}

void Robot::turnHeadRight() { this->angleRobotHead = -45; }
void Robot::turnHeadLeft() { this->angleRobotHead = 45; }
void Robot::turnHeadForward() { this->angleRobotHead = 0; }

//------------------------------------------------------- positionIsWithinBounds
// Implementation notes:
//  Return false if the coordinates given are "out of boundary", which implies
//  the move should not be allowed
//------------------------------------------------------------------------------
bool Robot::positionIsWithinBounds(const int64_t& x, const int64_t& y,
                                   const int64_t& z) {
  if (x < 0 || x >= static_cast<int64_t>(GRID_DIMENSIONS) || y < 0 ||
      y >= static_cast<int64_t>(GRID_DIMENSIONS) || z < 0 ||
      z >= static_cast<int64_t>(GRID_DIMENSIONS)) {
    return false;
  } else {
    return true;
  }
}

//--------------------------------------------------------------------- drawBase
// Implementation notes:
//  Uses the vertices stored in private member base to draw the base of the
//  robot as specified in the assignment.  Note this allow draws the extra
//  shapes on the exterior like the inner rect on the front and the triangles
//  on the back
//------------------------------------------------------------------------------
void Robot::drawBase() {
  float front = 0.7;
  float fact = 0.6;
  float offy = 0.2;

  // for triangles to be drawn on back of robot
  GLfloat tri[3][3] = {{this->base[2][0] * fact, this->base[2][1] + offy,
                        static_cast<float>(this->base[2][2] * 1.001)},
                       {this->base[3][0] * fact, this->base[3][1] + offy,
                        static_cast<float>(this->base[3][2] * 1.001)},
                       {0.0, static_cast<float>(this->base[1][1] * 0.25),
                        static_cast<float>(this->base[3][2] * 1.001)}};

  // 6 cube faces
  glBegin(GL_QUADS);

  // yellow - back of the robot
  glColor3f(1.0, 1.0, 0.0);
  glVertex3fv(this->base[0]);
  glVertex3fv(this->base[1]);
  glVertex3fv(this->base[2]);
  glVertex3fv(this->base[3]);

  glEnd();

  // red - inner triangles on the robot
  glBegin(GL_TRIANGLES);

  // bottom triangle
  glColor3f(1.0, 0.0, 0.0);
  glVertex3fv(tri[0]);
  glVertex3fv(tri[1]);
  glVertex3fv(tri[2]);

  // top triangle
  float off2 = 0.55;
  glVertex3f(tri[0][0], tri[0][1] + off2, tri[0][2]);
  glVertex3f(tri[1][0], tri[1][1] + off2, tri[1][2]);
  glVertex3f(tri[2][0], tri[2][1] + off2, tri[2][2]);

  glEnd();

  glBegin(GL_QUADS);

  // red - front of the robot
  glColor3f(1.0, 0.0, 0.0);
  glVertex3fv(this->base[5]);
  glVertex3fv(this->base[4]);
  glVertex3fv(this->base[7]);
  glVertex3fv(this->base[6]);

  // green - inner rect on front
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(this->base[5][0] * front, this->base[5][1] * front,
             this->base[5][2] * 1.001);
  glVertex3f(this->base[4][0] * front, this->base[4][1] * front,
             this->base[4][2] * 1.001);
  glVertex3f(this->base[7][0] * front, this->base[7][1] * front,
             this->base[7][2] * 1.001);
  glVertex3f(this->base[6][0] * front, this->base[6][1] * front,
             this->base[6][2] * 1.001);

  // green
  glColor3f(0.0, 1.0, 0.0);
  glVertex3fv(this->base[4]);
  glVertex3fv(this->base[0]);
  glVertex3fv(this->base[3]);
  glVertex3fv(this->base[7]);

  // blue
  glColor3f(0.0, 0.0, 1.0);
  glVertex3fv(this->base[1]);
  glVertex3fv(this->base[5]);
  glVertex3fv(this->base[6]);
  glVertex3fv(this->base[2]);

  // light blue
  glColor3f(0.0, 1.0, 1.0);
  glVertex3fv(this->base[4]);
  glVertex3fv(this->base[5]);
  glVertex3fv(this->base[1]);
  glVertex3fv(this->base[0]);

  // pink
  glColor3f(1.0, 0.0, 1.0);
  glVertex3fv(this->base[3]);
  glVertex3fv(this->base[2]);
  glVertex3fv(this->base[6]);
  glVertex3fv(this->base[7]);

  glEnd();
}

//--------------------------------------------------------------------- drawHead
// Implementation notes:
//  Uses the vertices stored in private member head to draw the head of the
//  robot.
//
//  #TODO_CB add the neck piece, the cylinder eyes, and the rotating antenna.
//------------------------------------------------------------------------------
void Robot::drawHead() {
  // 6 cube faces
  glBegin(GL_QUADS);

  // green - back of the robot head
  glColor3f(0.0, 1.0, 0.0);
  glVertex3fv(this->head[0]);
  glVertex3fv(this->head[1]);
  glVertex3fv(this->head[2]);
  glVertex3fv(this->head[3]);

  // red - front of the robot face
  glColor3f(1.0, 0.0, 0.0);
  glVertex3fv(this->head[5]);
  glVertex3fv(this->head[4]);
  glVertex3fv(this->head[7]);
  glVertex3fv(this->head[6]);

  // pink
  glColor3f(1.0, 0.0, 1.0);
  glVertex3fv(this->head[4]);
  glVertex3fv(this->head[0]);
  glVertex3fv(this->head[3]);
  glVertex3fv(this->head[7]);

  // blue
  glColor3f(0.0, 0.0, 1.0);
  glVertex3fv(this->head[1]);
  glVertex3fv(this->head[5]);
  glVertex3fv(this->head[6]);
  glVertex3fv(this->head[2]);

  // light blue
  glColor3f(0.0, 1.0, 1.0);
  glVertex3fv(this->head[4]);
  glVertex3fv(this->head[5]);
  glVertex3fv(this->head[1]);
  glVertex3fv(this->head[0]);

  // pink
  glColor3f(1.0, 0.0, 1.0);
  glVertex3fv(this->head[3]);
  glVertex3fv(this->head[2]);
  glVertex3fv(this->head[6]);
  glVertex3fv(this->head[7]);

  glEnd();
}