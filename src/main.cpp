/*
	* Interactive Game
	* CPSC 3710 Final Project
	* Group members: Alex Hochheiden, Cody Barnson, Cody Crawford
*/

#define PROGRAM_TITLE "Interactive Game"

#include <stdlib.h>  // Useful for the following includes.
#include <time.h>
#include <iostream>
#include <cstring>
#include <cassert>

// Switch these includes for Linux and Windows
//#include <GL\glut.h> //Windows version
#include <GL/gl.h>   // OpenGL itself. Linux
#include <GL/glu.h>  // GLU support library. Linux
#include <GL/glut.h> // GLUT support library. Linux

// Project includes
#include "robot.h"
#include "coordinate3d.h"
#include "object.h"
#include "street.h"
#include "cylinder.h"
#include "rectangularPrism.h"
#include "triangularPrism.h"

// Global Variables
int WINDOW_ID;
int WINDOW_WIDTH = 1024;
int WINDOW_HEIGHT = 600;

const uint64_t NUM_BLOCKS = 20;
const uint64_t BLOCK_SIZE = 3;
const uint64_t BUILDINGS_PER_BLOCK = 5;
const uint64_t GRID_DIMENSIONS = (NUM_BLOCKS * (BLOCK_SIZE + 1)) + 1;

Object* objectGrid[GRID_DIMENSIONS][GRID_DIMENSIONS];

Robot robot(Coordinate3D(0, 0, 0));

GLdouble eX, eY, eZ, atX, atY, atZ;

void init(int width, int height);
void renderSceneCallback();
void resizeSceneCallback(int width, int height);
void keyboardCallback(unsigned char key, int x, int y);
void specialKeysCallback(int key, int x, int y);
void mouseCallback(int button, int state, int x, int y);
void populateGrid();
void setStreetsAndEmptyLocations();
void populateBlocks();
void printGridToConsole();

int main(int argc, char** argv)
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
void init(
	int width,
	int height)
{
	srand(time(nullptr));
	populateGrid();

	// Eye at Origin and looking -z axis
	eX = 0; eY = 0; eZ = 0; atX = 0; atY = 0; atZ = -1;

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

	gluLookAt(eX, eY, eZ, atX, atY, atZ, 0.0, 1.0, 0.0);

	// Test Shape
	glTranslatef(0.0f, 0.0f, -10.0f);
	glutSolidSphere(1, 20, 20);

	// Test
	robot.draw();

	glutSwapBuffers();
}

//---------------------------------------------------------- renderSceneCallback
// Implementation notes:
//  Called when the window is resized. Resets various settings and ensures
//  that the window is at least 1 pixel tall at the minimum to ensure a
//  crash doesn't happen.
//------------------------------------------------------------------------------
void resizeSceneCallback(
	int width,
	int height)
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
	int x,
	int y)
{
	switch(key)
	{
		default:
			std::cout << "KP: No action for " << key << std::endl;
			break;
	}
}

//---------------------------------------------------------- specialKeysCallback
// Implementation notes:
//  Called when any special keyboard event occurs. This is one of the functions 
//  that is used to process user inputs and apply changes to the state of the
//  game.
//------------------------------------------------------------------------------
void specialKeysCallback(
	int key,
	int x,
	int y)
{
	switch(key)
	{
		default:
			std::cout << "SKP: No action for " << key << std::endl;
			break;
	}
}

//---------------------------------------------------------------- mouseCallback
// Implementation notes:
//  Called when any mouse event occurs. This is one of the functions that is 
//  used to process user inputs and apply changes to the state of the game.
//------------------------------------------------------------------------------
void mouseCallback(
	int button,
	int state,
	int x,
	int y)
{
	switch(button)
	{
		case GLUT_LEFT_BUTTON:
		{
			switch(state)
			{
				default:
				{
					break;
				}
			}
			break;
		}
		case GLUT_RIGHT_BUTTON:
		{
			switch(state)
			{
				default:
				{
					break;
				}
			}
			break;
		}
		default:
		{
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
	// #TODO_AH remove this at some point
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
						if((BUILDINGS_PER_BLOCK - numObjectsPlaced) >= positionsRemainingWithinBlock)
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
								objectGrid[xCoordinate][yCoordinate] = new Cylinder(Coordinate3D(xCoordinate, yCoordinate, 0));
								numObjectsPlaced++;
								break;
							}
							case 1:
							{
								objectGrid[xCoordinate][yCoordinate] = new RectangularPrism(Coordinate3D(xCoordinate, yCoordinate, 0));
								numObjectsPlaced++;
								break;
							}
							case 2:
							{
								objectGrid[xCoordinate][yCoordinate] = new TriangularPrism(Coordinate3D(xCoordinate, yCoordinate, 0));
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