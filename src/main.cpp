/*
		* Interactive Game
		* CPSC 3710 Final Project
		* Group members: Alex Hochheiden, Cody Barnson, Cody Crawford
*/

#define PROGRAM_TITLE "Interactive Game"

#include <stdlib.h>  // Useful for the following includes.
#include <time.h>
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>

// Switch these includes for Linux and Windows
//#include <GL\glut.h> //Windows version
#include <GL/gl.h>    // OpenGL itself. Linux
#include <GL/glu.h>   // GLU support library. Linux
#include <GL/glut.h>  // GLUT support library. Linux

// Project includes
#include "coordinate3d.h"
#include "cylinder.h"
#include "object.h"
#include "rectangularPrism.h"
#include "robot.h"
#include "street.h"
#include "triangularPrism.h"

// global variables -- config file
#include "config.h"

int32_t WINDOW_ID;
int32_t WINDOW_WIDTH = 1024;
int32_t WINDOW_HEIGHT = 600;

Object* objectGrid[GRID_DIMENSIONS][GRID_DIMENSIONS];

Robot theRobot(Coordinate3D(0, 0, 0));
std::vector<Object*> objectsInRange;

double offX, offY, offZ;
GLdouble eX, eY, eZ, atX, atY, atZ;

// Function Prototypes
void init(int32_t width, int32_t height);

void renderSceneCallback();

void resizeSceneCallback(int32_t width, int32_t height);

void keyboardCallback(unsigned char key, int32_t x, int32_t y);

void specialKeysCallback(int32_t key, int32_t x, int32_t y);

void mouseCallback(int32_t button, int32_t state, int32_t x, int32_t y);

void populateGrid();

void setStreetsAndEmptyLocations();

void populateBlocks();

void printGridToConsole();

void populateInRangeVector();

void printObjectsInRangeToConsole();

void setViewLookAt();

// Entry point
int main(int32_t argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// Window creation
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	WINDOW_ID = glutCreateWindow(PROGRAM_TITLE);

	// Register and install draw function
	glutDisplayFunc(&renderSceneCallback);

	// Idle Function
	glutIdleFunc(&renderSceneCallback);

	// Window resize calculation
	glutReshapeFunc(&resizeSceneCallback);

	// register and install functions for keyboard and mouse input
	glutKeyboardFunc(&keyboardCallback);
	glutSpecialFunc(&specialKeysCallback);
	glutMouseFunc(&mouseCallback);

	// My init
	init(WINDOW_WIDTH, WINDOW_HEIGHT);

	// OpenGl takes control
	glutMainLoop();
}

//------------------------------------------------------------------------- init
// Implementation notes:
//  Initializes various OpenGL settings and any other variables necessary
//  for the game to begin looping
//------------------------------------------------------------------------------
void init(int32_t width, int32_t height)
{
	// Seed rand with time
	srand(time(nullptr));

	// Populate the grid representing the world with random objects
	populateGrid();

	// Set the capacity of the objectsInRange container to the maximum
	// amount it can ever have
	objectsInRange.reserve(VISUAL_RANGE * VISUAL_RANGE);

	// Populate the objectsInRange vector so that the first draw is correct
	// This will be repopulated every time the robot moves
	populateInRangeVector();

	// set our offsets for the camera eye position
	offX = 0.0;
	offY = 5.0;
	offZ = 5.0;

	// set coordinates of eye position and what we are looking at (i.e. the robot)
	setViewLookAt();

	// Eye at Origin and looking -z axis
	/*eX = 5;
  eY = 5;
  eZ = 5;*/

  /* atX = 0;
 atY = 0;
 atZ = 0;*/

 // set coordinates of what we are looking at
 /*atX = theRobot.viewCoordinate3D().viewX();
atY = theRobot.viewCoordinate3D().viewY();
atZ = theRobot.viewCoordinate3D().viewZ();

// set coordinates of the eye position, using the robot coordinate3D and the
// offsets for each component x y z
eX = theRobot.viewCoordinate3D().viewX() + offX;
eY = theRobot.viewCoordinate3D().viewY() + offY;
eZ = theRobot.viewCoordinate3D().viewZ() + offZ;*/

    // Color to clear color buffer to.
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

	// Depth to clear depth buffer to; type of test.
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	// Depth Test
	glEnable(GL_DEPTH_TEST);

	// Culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Enables Smooth Color Shading; try GL_FLAT for (lack of) fun.
	glShadeModel(GL_SMOOTH);

	// Load up the correct perspective matrix; using a callback directly.
	resizeSceneCallback(width, height);
}

//---------------------------------------------------------- renderSceneCallback
// Implementation notes:
//  Essentially the draw function, a call to this represents a frame that will
//  be displayed to the screen.
//------------------------------------------------------------------------------
void renderSceneCallback()
{
	// Clear the color and depth buffers.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw all objects in range
	for(Object* inRangeObject : objectsInRange)
	{
		inRangeObject->draw();
	}

	// Test begin
	gluLookAt(eX, eY, eZ, atX, atY, atZ, 0.0, 1.0, 0.0);
	// glTranslatef(0.0f, 0.0f, -10.0f);

	// Draw the robot
	theRobot.draw();
	// glutSolidSphere(1, 20, 20);

	// length of each axis to draw
	double len = 2.0;
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(len, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, len, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, len);
	glEnd();

	// Test end

	glutSwapBuffers();
}

//---------------------------------------------------------- renderSceneCallback
// Implementation notes:
//  Called when the window is resized. Resets various settings and ensures
//  that the window is at least 1 pixel tall at the minimum to ensure a
//  crash doesn't happen.
//------------------------------------------------------------------------------
void resizeSceneCallback(int32_t width, int32_t height)
{
	if(height == 0)
	{
		// Stop core dump
		height = 1;
	}
	else
	{
		// Do nothing
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);

	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
}

//------------------------------------------------------------- keyboardCallback
// Implementation notes:
//  Called when any normal keyboard event occurs. One of the functions that is
//  used to process user inputs and apply changes to the state of the game.
//------------------------------------------------------------------------------
void keyboardCallback(
	unsigned char key,
	int32_t x,
	int32_t y)
{
	switch(key)
	{
		// NOTE: assignment specifies the following key functions:
		// 'a': at intersection, turn right; else do nothing
		// 'q': at intersection, turn left; else do nothing
		// 'z': push the robot forward, if possible (bound check), and update the
		// camera
		// since this is confusing as fuck, for now I'm using WASD layout, where 'w'
		// moves forward, 'a' turns left, and 'd' turns right
		// can change back later

		case 'd':
		{ 
			// at an intersection of the streets, turn the robot to the
			// right; if not at intersection, do nothing
			theRobot.attemptRightTurn();
			break;
		}
		case 'a':
		{ 
			// at an intersection of the streets, turn the robot to left;
			// if not at intersection, do nothing
			theRobot.attemptLeftTurn();
			break;
		}
		case 'w':
		{  
			// push the robot forward
			theRobot.attemptMoveForward();
			setViewLookAt();
			break;
		}
		default:
		{
			std::cout << "KP: No action for " << key << std::endl;
			break;
		}
	}
}

//---------------------------------------------------------- specialKeysCallback
// Implementation notes:
//  Called when any special keyboard event occurs. This is one of the functions
//  that is used to process user inputs and apply changes to the state of the
//  game.
//------------------------------------------------------------------------------
void specialKeysCallback(
	int32_t key,
	int32_t x,
	int32_t y)
{
	switch(key)
	{
		case GLUT_KEY_F1:
		{
			break;
		}
		case GLUT_KEY_F2:
		{
			break;
		}
		case GLUT_KEY_F3:
		{
			break;
		}
		case GLUT_KEY_F4:
		{
			break;
		}
		case GLUT_KEY_F5:
		{
			break;
		}
		case GLUT_KEY_F6:
		{
			break;
		}
		case GLUT_KEY_F7:
		{
			break;
		}
		case GLUT_KEY_F8:
		{
			break;
		}
		default:
		{
			std::cout << "SKP: No action for " << key << std::endl;
			break;
		}
	}
}

//---------------------------------------------------------------- mouseCallback
// Implementation notes:
//  Called when any mouse event occurs. This is one of the functions that is
//  used to process user inputs and apply changes to the state of the game.
//------------------------------------------------------------------------------
void mouseCallback(int32_t button, int32_t state, int32_t x, int32_t y)
{
	switch(button)
	{
		case GLUT_LEFT_BUTTON:
		{
			switch(state)
			{
				case GLUT_DOWN:
				{
					break;
				}
				case GLUT_UP:
				{
					break;
				}
				default:
				{
					break;
				}
			}
			break;
		}
		default:
		{
			std::cout << "MBP: No action for " << button << "button in " << state
				<< " state" << std::endl;
			break;
		}
	}
}

//----------------------------------------------------------------- populateGrid
// Implementation notes:
//  Populates the objectGrid with objects to be displayed in the world. nullptr
//  represents empty locations in the grid. The "blocks" within the grid
//  are randomly populated with non-street objects. Streets will always be
//  in the same places, and each block will have the same number of buildings
//  (specified by BUILDINGS_PER_BLOCK), but the types of buildings and their
//  positions will be random.
//------------------------------------------------------------------------------
void populateGrid()
{
	setStreetsAndEmptyLocations();
	populateBlocks();

	// #TODO_AH test function, remove at some point
	printGridToConsole();
}

//-------------------------------------------------- setStreetsAndEmptyLocations
// Implementation notes:
//  Sets the streets in our grid to their expected position, and sets all
//  other locations to nullptr
//------------------------------------------------------------------------------
void setStreetsAndEmptyLocations()
{
	for(uint64_t x = 0; x < GRID_DIMENSIONS; x++)
	{
		for(uint64_t y = 0; y < GRID_DIMENSIONS; y++)
		{
			if(((x % (BLOCK_SIZE + 1)) == 0) || ((y % (BLOCK_SIZE + 1) == 0)))
			{
				objectGrid[x][y] = new Street(Coordinate3D(x, y, 0));
			}
			else
			{
				objectGrid[x][y] = nullptr;
			}
		}
	}
}

//--------------------------------------------------------------- populateBlocks
// Implementation notes:
//  Randomly populates all the blocks with a random assortment of objects.
//  The behavior of this function is somewhat dynamic, since it is controlled
//  by the global variables of NUM_BLOCKS, BLOCK_SIZE, and BUILDINGS_PER_BLOCK.
//  The function will always populate each block with the exact amount of
//  buildings set by BUILDING_PER_BLOCK, but they will be in random locations.
//------------------------------------------------------------------------------
void populateBlocks()
{
	uint64_t xCoordinate = 0;
	uint64_t yCoordinate = 0;

	// Iterate through each "block" in our grid
	for(uint64_t x = 0; x < NUM_BLOCKS; x++)
	{
		for(uint64_t y = 0; y < NUM_BLOCKS; y++)
		{
			uint64_t positionsRemainingWithinBlock = (BLOCK_SIZE * BLOCK_SIZE);
			uint64_t numObjectsPlaced = 0;
			uint64_t selection = 0;

			// Process the "block" we're on
			for(uint64_t i = 1; i <= BLOCK_SIZE; i++)
			{
				for(uint64_t j = 1; j <= BLOCK_SIZE; j++)
				{
					// Determine the current x and y coordinate being
					// viewed within this block relative to the overall grid
					xCoordinate = ((BLOCK_SIZE + 1) * x) + i;
					yCoordinate = ((BLOCK_SIZE + 1) * y) + j;

					// Ensure the space is currently empty
					assert(objectGrid[xCoordinate][yCoordinate] == nullptr);

					// If we've placed the required number of buildings
					if(numObjectsPlaced == BUILDINGS_PER_BLOCK)
					{
						// Exit out of these two innermost loops
						i = BLOCK_SIZE + 1;
						j = BLOCK_SIZE + 1;
						continue;
					}
					else
					{
						// This is to ensure that we place the minimum number
						// of building required without reaching the end of the
						// block and having to double back
						if((BUILDINGS_PER_BLOCK - numObjectsPlaced) >=
							positionsRemainingWithinBlock)
						{
							selection = rand() % 3;
						}
						else
						{
							selection = rand() % 6;
						}

						// if result of rand is less than or equal to 2, a
						// building is placed, otherwise the location is skipped
						// and left as a nullptr
						switch(selection)
						{
							case 0:
							{
								objectGrid[xCoordinate][yCoordinate] =
									new Cylinder(Coordinate3D(xCoordinate, yCoordinate, 0));

								numObjectsPlaced++;
								break;
							}
							case 1:
							{
								objectGrid[xCoordinate][yCoordinate] = new RectangularPrism(
									Coordinate3D(xCoordinate, yCoordinate, 0));
								numObjectsPlaced++;
								break;
							}
							case 2:
							{
								objectGrid[xCoordinate][yCoordinate] = new TriangularPrism(
									Coordinate3D(xCoordinate, yCoordinate, 0));
								numObjectsPlaced++;
								break;
							}
							default:
							{
								// Do nothing
							}
						}

						positionsRemainingWithinBlock--;
					}
				}
			}
		}
	}
}

//----------------------------------------------------------- printGridToConsole
// Implementation notes:
//  Prints a character representing each Object subtype to the console. a "-"
//  represents an empty position. This function existing purely for testing
//  the implementation of the populateGrid function.
//------------------------------------------------------------------------------
void printGridToConsole()
{
	for(uint64_t i = 0; i < GRID_DIMENSIONS; i++)
	{
		for(uint64_t j = 0; j < GRID_DIMENSIONS; j++)
		{
			if(objectGrid[i][j] != nullptr)
			{
				objectGrid[i][j]->print();
			}
			else
			{
				std::cout << "-";
			}
		}
		std::cout << std::endl;
	}
}

//-------------------------------------------------------- populateInRangeVector
// Implementation notes:
//  Prints a character representing each Object subtype to the console. a "-"
//  represents an empty position. This function existing purely for testing
//  the implementation of the populateGrid function.
//------------------------------------------------------------------------------
void populateInRangeVector()
{
	// Clear the pointers currently in the vector
	objectsInRange.clear();

	// Calculate the boundaries of the for loops, which represent the
	// visual range of the robot, and determines what objects will be drawn
	int64_t xMin = std::max(
		static_cast<int64_t>(0),
		static_cast<int64_t>(theRobot.viewCoordinate3D().viewX() - VISUAL_RANGE));

	int64_t yMin = std::max(
		static_cast<int64_t>(0),
		static_cast<int64_t>(theRobot.viewCoordinate3D().viewY() - VISUAL_RANGE));

	int64_t xMax = std::min(
		static_cast<int64_t>(GRID_DIMENSIONS),
		static_cast<int64_t>(theRobot.viewCoordinate3D().viewX() + VISUAL_RANGE));

	int64_t yMax = std::min(
		static_cast<int64_t>(GRID_DIMENSIONS),
		static_cast<int64_t>(theRobot.viewCoordinate3D().viewY() + VISUAL_RANGE));

	// Add all the objects within the boundary
	for(int64_t i = xMin; i < xMax; i++)
	{
		for(int64_t j = yMin; j < yMax; j++)
		{
			// Do not add nullptrs to our objectsInRange container
			if(objectGrid[i][j] != nullptr)
			{
				// Push the object at the grid position
				// to the objectsInRange vector
				objectsInRange.push_back(objectGrid[i][j]);
			}
			else
			{
				// Do nothing
			}
		}
	}

	// #TODO_AH test function, remove at some point
	printObjectsInRangeToConsole();
}

//------------------------------------------------- printObjectsInRangeToConsole
// Implementation notes:
//  Prints only the character representing the objects that are in range, but
//  still prints the whole grid, every tile within the grid that is not in
//  in range will be a "-".
//------------------------------------------------------------------------------
void printObjectsInRangeToConsole()
{
	// Loop through every grid position
	for(uint64_t i = 0; i < GRID_DIMENSIONS; i++)
	{
		for(uint64_t j = 0; j < GRID_DIMENSIONS; j++)
		{
			// If the grid position is not empty
			if(objectGrid[i][j] != nullptr)
			{
				bool found = false;

				// Loop through every object in range
				for(size_t k = 0; k < objectsInRange.size(); k++)
				{
					// If the current object in range has the x,y coordinate
					// matching this grid position
					if((static_cast<uint64_t>(
						objectsInRange[k]->viewCoordinate3D().viewX()) == i) &&
						(static_cast<uint64_t>(
						objectsInRange[k]->viewCoordinate3D().viewY()) == j))
					{
						// Print the character corresponding to the object
						objectsInRange[k]->print();
						// Set found to true so we don't print a "-" later
						found = true;
						break;
					}
					else
					{
						continue;
					}
				}

				// This happens when the grid position being processed is not
				// in range, so we must print a "-"
				if(!found)
				{
					std::cout << "-";
				}
				else
				{
					// Do nothing
				}
			}
			else
			{
				// This happens when the grid position being processed is
				// empty, so we must print a "-"
				std::cout << "-";
			}
		}

		std::cout << std::endl;
	}
}

//---------------------------------------------------------------- setViewLookAt
// Implementation notes:
//  Updates the parameters for the glLookAt function with the correct eye
//  position (calculated via offsets based on the robot's position) and what
//  we're looking at (the robot's current position)
//------------------------------------------------------------------------------
void setViewLookAt()
{
	// set coordinates of what we are looking at
	atX = theRobot.viewCoordinate3D().viewX();
	atY = theRobot.viewCoordinate3D().viewY();
	atZ = theRobot.viewCoordinate3D().viewZ();

	// set coordinates of the eye position, using the robot coordinate3D and the
	// offsets for each component x y z
	eX = theRobot.viewCoordinate3D().viewX() + offX;
	eY = theRobot.viewCoordinate3D().viewY() + offY;
	eZ = theRobot.viewCoordinate3D().viewZ() + offZ;
}