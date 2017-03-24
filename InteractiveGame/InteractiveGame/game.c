/*
	* Interactive Game
	* CPSC 3710 Final Project
	* Group members: Alex Hochheiden, Cody Barnson, Cody Crawford
	*/

#define PROGRAM_TITLE "Multiple Rotations"

#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>    

	// Switch these includes for Linux and Windows
//#include <GL\glut.h> //Windows version
#include <GL/gl.h>   // OpenGL itself. Linux
#include <GL/glu.h>  // GLU support library. Linux
#include <GL/glut.h> // GLUT support library. Linux

// Window info
int WINDOW_ID;
int WINDOW_WIDTH = 1024;
int WINDOW_HEIGHT = 600;

GLdouble eX, eY, eZ, atX, atY, atZ;

void CallBackRenderScene(void) {
	// Clear the color and depth buffers.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eX, eY, eZ, atX, atY, atZ, 0.0, 1.0, 0.0);

	// Test Shape
	glTranslatef(0.0f, 0.0f, -10.0f);
	glutSolidSphere(1, 20, 20);

	glutSwapBuffers();
}

void CallBackResizeScene(int width, int height) {
	// Stop core dump
	if (height == 0) height = 1;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);

	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
}

void CBKey(unsigned char key, int x, int y) {
	switch (key) {
	default:
		printf("KP: No action for %d.\n", key);
		break;
	}
}

void SpecialKeys(int key, int x, int y) {
	switch (key) {

	default:
		printf("SKP: No action for %d.\n", key);
		break;
	}
}

void MouseFunc(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
	{
		switch (state) {
		default: break;
		}
	case GLUT_RIGHT_BUTTON:
	{
		switch (state) {
		default: break;
		}

	}
	default: break;
	}
	}
}

void Init(int width, int height) {
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
	CallBackResizeScene(width, height);


}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// Window creation
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	WINDOW_ID = glutCreateWindow(PROGRAM_TITLE);

	// Register and install draw function
	glutDisplayFunc(&CallBackRenderScene);

	// Idle Function
	glutIdleFunc(&CallBackRenderScene);

	// Window resize calculation
	glutReshapeFunc(&CallBackResizeScene);

	// register and install functions for keyboard and mouse input
	glutKeyboardFunc(&CBKey);
	glutSpecialFunc(&SpecialKeys);
	glutMouseFunc(&MouseFunc);

	// My init
	Init(WINDOW_WIDTH, WINDOW_HEIGHT);

	// OpenGl takes control
	glutMainLoop();

}