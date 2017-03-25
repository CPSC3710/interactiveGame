/*
	* Interactive Game
	* CPSC 3710 Final Project
	* Group members: Alex Hochheiden, Cody Barnson, Cody Crawford
*/

#define PROGRAM_TITLE "Multiple Rotations"

#include <stdlib.h>  // Useful for the following includes.
#include <iostream>

// Switch these includes for Linux and Windows
//#include <GL\glut.h> //Windows version
#include <GL/gl.h>   // OpenGL itself. Linux
#include <GL/glu.h>  // GLU support library. Linux
#include <GL/glut.h> // GLUT support library. Linux

// Project includes
#include "robot.h"
#include "coordinate3d.h"

// Global Variables
int WINDOW_ID;
int WINDOW_WIDTH = 1024;
int WINDOW_HEIGHT = 600;

Robot robot(Coordinate3D(0, 0, 0));

GLdouble eX, eY, eZ, atX, atY, atZ;

void init(int width, int height);
void renderSceneCallback();
void resizeSceneCallback(int width, int height);
void keyboardCallback(unsigned char key, int x, int y);
void specialKeysCallback(int key, int x, int y);
void mouseCallback(int button, int state, int x, int y);

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