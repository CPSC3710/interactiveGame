#ifndef CONFIG_H
#define CONFIG_H

// linux
#ifdef __linux__

#include <GL/gl.h>    // OpenGL itself. Linux
#include <GL/glu.h>   // GLU support library. Linux
#include <GL/glut.h>  // GLUT support library. Linux

// windows
#else

#include <GL\glut.h> // Windows version

#endif

#include <cstdint>

// Global Variables
const uint64_t NUM_BLOCKS = 20;
const uint64_t BLOCK_SIZE = 3;
const uint64_t BUILDINGS_PER_BLOCK = 5;
const uint64_t VISUAL_RANGE = 20;

// the maximum dimensions for the "city" or grid that the robot will be moving
// on, coordinates x and y that are greater than or equal to the grid max are
// deemed invalid locations and boundary checks shall be done to prevent such
// moves
const uint64_t GRID_DIMENSIONS = (NUM_BLOCKS * (BLOCK_SIZE + 1)) + 1;

// the change in angle, about the robots head's as the axis of rotation, for
// which the antenna will turn each update while the game is not paused.
// Positive values will yield a clockwise rotation, negative a counter clockwise
// rotation.
const float ROBOT_ANTENNA_ROTATE_DELTA = 30.0;

extern int32_t WINDOW_ID;
extern int32_t WINDOW_WIDTH;
extern int32_t WINDOW_HEIGHT;

/* Picking API */
extern void selectionFunc(void (*f)(void));  /* Selection-mode draw function */
extern void pickFunc(void (*f)(GLint name)); /* Pick event handling function */

#endif
