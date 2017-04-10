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
  // .5, 1.5, .5
  // -.5, 1.5, .5
  // -.5, 0, .5
  // .5, 0, .5
  // .5, 1.5, -.5
  // -.5, 1.5, -.5
  // -.5, 0, -.5
  // .5, 0, -.5

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
  m_antenna.setPersistent();
  m_antenna.setScale(0.1, 0.4, 0.1);
  m_antenna.setRotate(-90, 1, 0, 0);
  // m_antenna.setRotateDelta(0, 0, 0, 1, 0);
  m_antenna.setRotateDelta(this->m_antenna_angle, 0, 0, 1, 0);
  
  // configure eyes
  m_eyeLeft.setPersistent();
  m_eyeLeft.setScale(0.07, 0.07, 0.07);
  m_eyeLeft.setRotate(180, 0, 1, 0);
  m_eyeRight.setPersistent();
  m_eyeRight.setScale(0.07, 0.07, 0.07);
  m_eyeRight.setRotate(180, 0, 1, 0);

  // configure neck piece
  m_neck.setPersistent();
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
  // old rotate for "Y is up"
  // glRotatef(static_cast<float>(this->angleRobotBase), 0, 1, 0);

  // update for "Z is up"
  glRotatef(static_cast<float>(this->angleRobotBase), 0, 0, 1);
  glRotatef(90, 1, 0, 0);

  // draw robot head and rotate based on parameters set by key presses
  glPushMatrix();
  glTranslatef(0, 0.13, 0);  // move up for neck piece
  glRotatef(static_cast<float>(this->angleRobotHead), 0, 1, 0);
  this->drawHead();

  // draw neck piece
  glPushMatrix();
  glTranslatef(0, 1.3, 0);
  m_neck.drawModified();
  glPopMatrix();

  // draw antenna
  glPushMatrix();
  glTranslatef(0, 1.9, 0);
  m_antenna.setRotateDelta(this->m_antenna_angle, 0, 0, 1, 0);
  m_antenna.drawModified();
  glPopMatrix();

  // draw eyes
  glPushMatrix();
  glTranslatef(0, 1.75, -0.25);  // shifting reference frame to eye position
  glPushMatrix();
  glTranslatef(-0.1, 0, 0);  // shift left eye to left
  m_eyeLeft.drawModified();
  glPopMatrix();  // done left eye
  glPushMatrix();
  glTranslatef(0.1, 0, 0);  // shift right eye to right
  m_eyeRight.drawModified();
  glPopMatrix();  // done right eye
  glPopMatrix();  // done both eyes
  glPopMatrix();  // done drawing head

  this->drawBase();
  glPopMatrix();
}

void Robot::resetPositionToOrigin() {
  this->m_coordinate3D.setX(0);
  this->m_coordinate3D.setY(0);
  this->m_coordinate3D.setZ(0);
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
  if (isRobotAtIntersection()) {
    this->robotDirection = (this->robotDirection + 1) % 4;
    this->angleRobotBase = this->DIRECTION[this->robotDirection];
  } else {
    std::cout << "Robot right turn failed, not at intersection" << std::endl;
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
  if (isRobotAtIntersection()) {
    this->robotDirection = (this->robotDirection + (4 - 1)) % 4;
    this->angleRobotBase = this->DIRECTION[this->robotDirection];
  } else {
    std::cout << "Robot left turn failed, not at intersection" << std::endl;
  }
}

// returns true if and only if BOTH x position mod 1 + BLOCK_SIZE is 0, and y
// position mod 1 + BLOCK_SIZE is 0; otherwise false.
bool Robot::isRobotAtIntersection() const {
  int32_t x = static_cast<int32_t>(this->viewCoordinate3D().viewX());
  int32_t y = static_cast<int32_t>(this->viewCoordinate3D().viewY());
  return ((x % (1 + BLOCK_SIZE) == 0) && (y % (1 + BLOCK_SIZE) == 0));
}

// returns true if x position mod 1 + BLOCK_SIZE is 0, or y position mod 1 +
// BLOCK_SIZE is 0, or both; otherwise false.
bool Robot::isPositionOnStreet(int32_t x, int32_t y) const {
  return ((x % (1 + BLOCK_SIZE) == 0) || (y % (1 + BLOCK_SIZE) == 0));
}

//----------------------------------------------------------- attemptMoveForward
// Implementation notes:
//  Attempts to move the robot forward one grid position. The robot must stay
//  within the boundaries, and the grid position in front of it must be valid
// (eg. a street), if both conditions are met, the robot moves forward.
//------------------------------------------------------------------------------
bool Robot::attemptMoveForward() {
  int32_t i = this->robotDirection;
  int32_t x = static_cast<int32_t>(this->m_coordinate3D.viewX()) + this->dx[i];
  int32_t y = static_cast<int32_t>(this->m_coordinate3D.viewY()) + this->dy[i];
  int32_t z = static_cast<int32_t>(this->m_coordinate3D.viewZ()) + this->dz[i];

  // if in boundary, update the coordinate values
  if (isPositionInBounds(x, y) && isPositionOnStreet(x, y)) {
    this->m_coordinate3D.setX(static_cast<int64_t>(x));
    this->m_coordinate3D.setY(static_cast<int64_t>(y));
    this->m_coordinate3D.setZ(static_cast<int64_t>(z));

    m_antenna_angle -= ROBOT_ANTENNA_ROTATE_DELTA;
    return true;
    
  }
  else
  {
	  return false;
  }
}

void Robot::turnHeadRight() { this->angleRobotHead = -45; }
void Robot::turnHeadLeft() { this->angleRobotHead = 45; }
void Robot::turnHeadForward() { this->angleRobotHead = 0; }

bool Robot::isPositionInBounds(int32_t x, int32_t y) const {
  int32_t dim = static_cast<int32_t>(GRID_DIMENSIONS);
  return (x >= 0 && x < dim && y >= 0 && y < dim);
}

//--------------------------------------------------------------------- drawBase
// Implementation notes:
//  Uses the vertices stored in private member base to draw the base of the
//  robot as specified in the assignment.  Note this allow draws the extra
//  shapes on the exterior like the inner rect on the front and the triangles
//  on the back
//------------------------------------------------------------------------------
void Robot::drawBase() {
  float front = 0.8;
  float fact = 0.6;
  float offy = 0.2;

  // for triangles to be drawn on back of robot
  GLfloat tri[3][3] = {{this->base[2][0] * fact, this->base[2][1] + offy,
                        static_cast<float>(this->base[2][2] * 1.01)},
                       {this->base[3][0] * fact, this->base[3][1] + offy,
                        static_cast<float>(this->base[3][2] * 1.01)},
                       {0.0, static_cast<float>(this->base[1][1] * 0.4),
                        static_cast<float>(this->base[3][2] * 1.01)}};

  // 6 cube faces
  glPushMatrix();
  // glPushName(2);
  glBegin(GL_QUADS);

  // yellow - back of the robot
  glColor3f(1.0, 1.0, 0.0);
  glVertex3fv(this->base[0]);
  glVertex3fv(this->base[1]);
  glVertex3fv(this->base[2]);
  glVertex3fv(this->base[3]);

  glEnd();
  // glPopName();
  glPopMatrix();

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
             this->base[5][2] * 1.01);
  glVertex3f(this->base[4][0] * front, this->base[4][1] * front,
             this->base[4][2] * 1.01);
  glVertex3f(this->base[7][0] * front, this->base[7][1] + 0.1,
             this->base[7][2] * 1.01);
  glVertex3f(this->base[6][0] * front, this->base[6][1] + 0.1,
             this->base[6][2] * 1.01);

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
