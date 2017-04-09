#include "debug.h"
#include "config.h"

#include <chrono>  // for date and time handling

Debug::Debug() {}

Debug::~Debug() {}

void Debug::draw() {
  glDisable(GL_TEXTURE_2D);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  // output some standard information
  drawDefault();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  glEnable(GL_TEXTURE_2D);
}

// Variant of draw(), which, in addition to drawing some basic information
// (specified by drawDefault()), allows the user to output a formatted string
// containing a variable number of arguments, as well as specify the screen
// coordinates to draw it to.
void Debug::draw(int32_t x, int32_t y, const char* format, ...) {
  glDisable(GL_TEXTURE_2D);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  // output some standard information
  drawDefault();

  glColor3f(1, 1, 1);
  glRasterPos2i(x, y);

  va_list args;
  va_start(args, format);
  printv(args, format);  // output our argument string to the specified location
  va_end(args);

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  glEnable(GL_TEXTURE_2D);
}

// Helper function, called from Debug::draw(...), to output some basic
// information to a fixed position on the screen.  Outputs project title and
// current date and time information to the top-left hand corner of the opengl
// window
void Debug::drawDefault() {
  glColor3f(1, 1, 1);
  glRasterPos2i(30, WINDOW_HEIGHT - 30);
  print("CPSC3710 Project");

  // current date (e.g. Mon Jul 29 08:41:09 2013)
  glRasterPos2i(30, WINDOW_HEIGHT - 50);
  std::chrono::time_point<std::chrono::system_clock> current;
  current = std::chrono::system_clock::now();
  std::time_t currentTime = std::chrono::system_clock::to_time_t(current);
  print(std::ctime(&currentTime));
}

// Helper function, called by print().  Takes the constructed argument list and
// the string they belong to, and outputs to the screen coordinates specified
// (determined by higher level call to glRasterPos2i or equivalent).  For
// convenience, the following are a few alternatives for the font used:
// GLUT_BITMAP_9_BY_15
// GLUT_BITMAP_TIMES_ROMAN_10
// GLUT_BITMAP_TIMES_ROMAN_24
// GLUT_BITMAP_HELVETICA_10
// GLUT_BITMAP_HELVETICA_12
// GLUT_BITMAP_HELVETICA_18
void Debug::printv(va_list args, const char* format) {
  void* font = GLUT_BITMAP_8_BY_13;
  char buffer[256];
  char* ch = buffer;
  vsnprintf(buffer, 256, format, args);
  while (*ch) {
    glutBitmapCharacter(font, *ch++);
  }
}

void Debug::print(const char* format, ...) {
  va_list args;
  va_start(args, format);
  printv(args, format);
  va_end(args);
}
