#ifndef DEBUG_H
#define DEBUG_H

#include <stdarg.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <GL/gl.h>    // OpenGL itself. Linux
#include <GL/glu.h>   // GLU support library. Linux
#include <GL/glut.h>  // GLUT support library. Linux

class Debug {
 public:
  Debug();
  ~Debug();

  void draw();

  // Variant of draw(), which, in addition to drawing some basic information
  // (specified by drawDefault()), allows the user to output a formatted string
  // containing a variable number of arguments, as well as specify the screen
  // coordinates to draw it to.
  void draw(int32_t x, int32_t y, const char* format, ...);

 private:
  void print(const char* format, ...);
  void printv(va_list args, const char* format);

  // Helper function, called from Debug::draw(...), to output some basic
  // information to a fixed position on the screen.  Outputs project title and
  // current date and time information to the top-left hand corner of the opengl
  // window
  void drawDefault();
};

#endif