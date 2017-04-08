#include "robot.h"
#include "config.h"

#include <iostream>

//------------------------------------------------------------------ constructor
// Implementation notes:
//  Initializes the vertices of the robots primitive components such as
//  the base and the head
//------------------------------------------------------------------------------
Robot::Robot(
	const Coordinate3D& coordinate) :
	Object(coordinate)
{
	// initialize origin of the robot
	origin[0] = static_cast<float>(this->m_coordinate3D.viewX());
	origin[1] = static_cast<float>(this->m_coordinate3D.viewY());
	origin[2] = static_cast<float>(this->m_coordinate3D.viewZ());

	// initialize the origin of the robot's head
	originHead[0] = static_cast<float>(origin[0] + baseHeight);
	originHead[1] = static_cast<float>(origin[1] + baseHeight);
	originHead[2] = static_cast<float>(origin[2] + baseHeight);

	// initialize the vertices of the base of the robot
	GLfloat bb[8][3] = {
		//{baseWidth, origin[1] + baseHeight, baseWidth},
		//{-baseWidth, origin[1] + baseHeight, baseWidth},
		//{-baseWidth, origin[1], baseWidth},
		//{baseWidth, origin[1], baseWidth},
		//{baseWidth, origin[1] + baseHeight, -baseWidth},
		//{-baseWidth, origin[1] + baseHeight, -baseWidth},
		//{-baseWidth, origin[1], -baseWidth},
		//{baseWidth, origin[1], -baseWidth}
		{baseWidth, baseWidth, origin[2]}, //first 4 are bottom
		{ -baseWidth, baseWidth, origin[2] },
		{ -baseWidth, -baseWidth, origin[2] },
		{ baseWidth, -baseWidth, origin[2] },
		{ baseWidth, baseWidth, origin[2] + baseHeight }, // last 4 are top
		{ -baseWidth, baseWidth, origin[2] + baseHeight },
		{- baseWidth, -baseWidth, origin[2] + baseHeight },
		{ baseWidth, -baseWidth, origin[2] + baseHeight }
	};

	// initialize the vertices of the head of the robot
	GLfloat hh[8][3] = {
		//{headWidth, originHead[1] + headHeight, headWidth},
		//{-headWidth, originHead[1] + headHeight, headWidth},
		//{-headWidth, originHead[1], headWidth},
		//{headWidth, originHead[1], headWidth},
		//{headWidth, originHead[1] + headHeight, -headWidth},
		//{-headWidth, originHead[1] + headHeight, -headWidth},
		//{-headWidth, originHead[1], -headWidth},
		//{headWidth, originHead[1], -headWidth}
		{ headWidth, headWidth, originHead[2] }, // first 4 are bottom
		{ -headWidth, headWidth, originHead[2] },
		{ -headWidth, -headWidth, originHead[2] },
		{ headWidth, -headWidth, originHead[2] },
		{ headWidth, headWidth, originHead[2] + headHeight },	// Last 4 are top
		{ -headWidth, headWidth, originHead[2] + headHeight },
		{ -headWidth, -headWidth, originHead[2] + headHeight },
		{ headWidth, -headWidth, originHead[2] + headHeight }
	};

	// write values into our member variables
	for(uint64_t i = 0; i < 8; i++)
	{
		for(uint64_t j = 0; j < 3; j++)
		{
			base[i][j] = bb[i][j];
			head[i][j] = hh[i][j];
		}
	}
}

//------------------------------------------------------------------------- draw
// Implementation notes:
//  #TODO
//------------------------------------------------------------------------------
void Robot::draw()
{
	glPushMatrix();

	glTranslatef(
		static_cast<float>(this->m_coordinate3D.viewX()),
		static_cast<float>(this->m_coordinate3D.viewY()),
		static_cast<float>(this->m_coordinate3D.viewZ()));

	glRotatef(
		static_cast<float>(this->angleRobotBase),
		0, 
		0,
		1);

	// draw robot head and rotate based on parameters set by key presses
	glPushMatrix();

	glRotatef(
		static_cast<float>(this->angleRobotHead),
		0,
		0,
		1);

	this->drawHead();

	glPopMatrix();

	// draw robot base, at the position specified by rx ry rz, this
	// also moves the head with it
	this->drawBase();

	glPopMatrix();
}

//------------------------------------------------------------------------ print
// Implementation notes:
//  Prints "B" for "bot" of "Robot"
//------------------------------------------------------------------------------
void Robot::print()
{
	std::cout << "B";
}

//------------------------------------------------------------- viewCoordinate3D
// Implementation notes:
//  Self explanatory
//------------------------------------------------------------------------------
const Coordinate3D& Robot::viewCoordinate3D() const
{
	return this->m_coordinate3D;
}

//------------------------------------------------------------- attemptRightTurn
// Implementation notes:
//  If the robot is at a location where it is valid to turn (intersection),
//  then update the robotDirection index (relative to the DIRECTION array),
//  and write the new value for angleRobot respective to this new value
//  Moves FORWARDS circularly through DIRECTION array
//------------------------------------------------------------------------------
void Robot::attemptRightTurn()
{
	if(this->robotAtIntersection)
	{
		this->robotDirection =
			(this->robotDirection + 1) % 4;

		this->angleRobotBase =
			this->DIRECTION[this->robotDirection];
	}
}

//-------------------------------------------------------------- attemptLeftTurn
// Implementation notes:
//  If the robot is at a location where it is valid to turn (intersection),
//  then update the robotDirection index (relative to the DIRECTION array),
//  and write the new value for angleRobot respective to this new value.
//  Moves BACKWARDS circularly through DIRECTION array
//------------------------------------------------------------------------------
void Robot::attemptLeftTurn()
{
	if(this->robotAtIntersection)
	{
		this->robotDirection =
			(this->robotDirection + (4 - 1)) % 4;

		this->angleRobotBase =
			this->DIRECTION[this->robotDirection];
	}
}

//----------------------------------------------------------- attemptMoveForward
// Implementation notes:
//  Attempts to move the robot forward one grid position. The robot must stay
//  within the boundaries, and the grid position in front of it must be valid
// (eg. a street), if both conditions are met, the robot moves forward.
//------------------------------------------------------------------------------
void Robot::attemptMoveForward()
{
	int64_t i = this->robotDirection;
	int64_t x = this->m_coordinate3D.viewX() + this->dx[i];
	int64_t y = this->m_coordinate3D.viewY() + this->dy[i];
	int64_t z = this->m_coordinate3D.viewZ() + this->dz[i];

	// if in boundary, update the coordinate values
	if(positionIsWithinBounds(x, y, z))
	{
		this->m_coordinate3D.setX(static_cast<int64_t>(x));
		this->m_coordinate3D.setY(static_cast<int64_t>(y));
		this->m_coordinate3D.setZ(static_cast<int64_t>(z));
	}
}

//------------------------------------------------------- positionIsWithinBounds
// Implementation notes:
//  Return false if the coordinates given are "out of boundary", which implies
//  the move should not be allowed
//------------------------------------------------------------------------------
bool Robot::positionIsWithinBounds(
	const int64_t& x,
	const int64_t& y,
	const int64_t& z)
{
	if(x < 0
		|| x >= static_cast<int64_t>(GRID_DIMENSIONS)
		|| y < 0
		|| y >= static_cast<int64_t>(GRID_DIMENSIONS)
		|| z < 0 ||
		z >= static_cast<int64_t>(GRID_DIMENSIONS))
	{
		return false;
	}
	else
	{
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
void Robot::drawBase()
{
	float front = 0.7;
	float fact = 0.6;
	float offy = 0.2;

	// for triangles to be drawn on back of robot
	GLfloat tri[3][3] = {
		{this->base[3][0] * fact, 
		this->base[3][1] * 1.001,
		static_cast<float>(this->base[3][2]) + offy },
		{this->base[2][0] * fact, 
		this->base[2][1] * 1.001,
		static_cast<float>(this->base[2][2]) + offy },
		{0.0,
		static_cast<float>(this->base[7][1] * 1.001),
		static_cast<float>(this->base[6][2] * 0.25)}};

	// 6 cube faces
	glBegin(GL_QUADS);

	// yellow - back of the robot
	glColor3f(1.0, 1.0, 0.0);
	glVertex3fv(this->base[2]);
	glVertex3fv(this->base[3]);
	glVertex3fv(this->base[7]);
	glVertex3fv(this->base[6]);

	glEnd();

	// red - inner triangles on the robot
	glBegin(GL_TRIANGLES);

	// bottom triangle
	glColor3f(1.0, 0.0, 0.0);
	glVertex3fv(tri[2]);
	glVertex3fv(tri[1]);
	glVertex3fv(tri[0]);

	// top triangle
	float off2 = 0.55;
	glVertex3f(tri[2][0], tri[2][1], tri[2][2] + off2);
	glVertex3f(tri[1][0], tri[1][1], tri[1][2] + off2);
	glVertex3f(tri[0][0], tri[0][1], tri[0][2] + off2);

	glEnd();

	glBegin(GL_QUADS);

	// red - front of the robot
	glColor3f(1.0, 0.0, 0.0);
	glVertex3fv(this->base[0]);
	glVertex3fv(this->base[1]);
	glVertex3fv(this->base[5]);
	glVertex3fv(this->base[4]);

	// green - inner rect on front
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(this->base[0][0] * front, this->base[0][1] * 1.001,
		this->base[0][2] * front);
	glVertex3f(this->base[1][0] * front, this->base[1][1] * 1.001,
		this->base[1][2] * front);
	glVertex3f(this->base[5][0] * front, this->base[5][1] * 1.001,
		this->base[5][2] * front);
	glVertex3f(this->base[4][0] * front, this->base[4][1] * 1.001,
		this->base[4][2] * front);

	// green - right
	glColor3f(0.0, 1.0, 0.0);
	glVertex3fv(this->base[0]);
	glVertex3fv(this->base[4]);
	glVertex3fv(this->base[7]);
	glVertex3fv(this->base[3]);

	// blue - left
	glColor3f(0.0, 0.0, 1.0);
	glVertex3fv(this->base[1]);
	glVertex3fv(this->base[2]);
	glVertex3fv(this->base[6]);
	glVertex3fv(this->base[5]);

	// light blue - top
	glColor3f(0.0, 1.0, 1.0);
	glVertex3fv(this->base[4]);
	glVertex3fv(this->base[5]);
	glVertex3fv(this->base[6]);
	glVertex3fv(this->base[7]);

	// pink - bottom
	glColor3f(1.0, 0.0, 1.0);
	glVertex3fv(this->base[0]);
	glVertex3fv(this->base[3]);
	glVertex3fv(this->base[2]);
	glVertex3fv(this->base[1]);

	glEnd();
}

//--------------------------------------------------------------------- drawHead
// Implementation notes:
//  Uses the vertices stored in private member head to draw the head of the
//  robot. 
//
//  #TODO_CB add the neck piece, the cylinder eyes, and the rotating antenna.
//------------------------------------------------------------------------------
void Robot::drawHead()
{
	// 6 cube faces
	glBegin(GL_QUADS);

	// yellow - back of the robot head
	glColor3f(1.0, 1.0, 0.0);
	glVertex3fv(this->head[2]);
	glVertex3fv(this->head[3]);
	glVertex3fv(this->head[7]);
	glVertex3fv(this->head[6]);

	// red - front of the robot face
	glColor3f(1.0, 0.0, 0.0);
	glVertex3fv(this->head[0]);
	glVertex3fv(this->head[1]);
	glVertex3fv(this->head[5]);
	glVertex3fv(this->head[4]);

	// green - right
	glColor3f(0.0, 1.0, 0.0);
	glVertex3fv(this->head[0]);
	glVertex3fv(this->head[4]);
	glVertex3fv(this->head[7]);
	glVertex3fv(this->head[3]);

	// blue - left
	glColor3f(0.0, 0.0, 1.0);
	glVertex3fv(this->head[1]);
	glVertex3fv(this->head[2]);
	glVertex3fv(this->head[6]);
	glVertex3fv(this->head[5]);

	// light blue - top
	glColor3f(0.0, 1.0, 1.0);
	glVertex3fv(this->head[4]);
	glVertex3fv(this->head[5]);
	glVertex3fv(this->head[6]);
	glVertex3fv(this->head[7]);

	// pink - bottom
	glColor3f(1.0, 0.0, 1.0);
	glVertex3fv(this->head[0]);
	glVertex3fv(this->head[3]);
	glVertex3fv(this->head[2]);
	glVertex3fv(this->head[1]);

	glEnd();
}