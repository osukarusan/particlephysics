#ifndef _GLFUNCS_
#define _GLFUNCS_

#define USEFLTK 1

#include "GL/glut.h"
#if USEFLTK
#include "fltk/glut.h"
#include "fltk/gl.h"
#endif

#ifdef WIN32
#include <windows.h>
#include <GL/glu.h>
#elif CYGWIN
#include <GL/glu.h>
#elif MACOSX
#include <fltk/gl.h>
#include <opengl/glu.h>
#endif
#include <string>
#include "defines.h"

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

bool ScreenShot(int w, int h, char *fname, bool _antialias=false);
void DrawStringOnScreen(float x, float y, void *font, std::string s);
void DrawStringOnScreen2(double x, double y, char *s);

// draw an arrow made up of cylinder and cone
void DrawArrow(Vec3d pt, Vec3d dir, double length, double thickness, double arrowthickness=-1);
// get a ray from viwpoint to the point on screen
void GetMouseRay(double x, double y, Vec3d &pos, Vec3d& dir );
// computes camera center in world coords
Vec3d GetCameraCenterWorld();
// computes eye in world frame
Vec3d GetPointEyeToWorld(Vec3d _pt);

// for rendering with antialiasing
void accFrustum(GLdouble _left, GLdouble _right, GLdouble _bottom, GLdouble _top, GLdouble _near, GLdouble _far, GLdouble _pixdx, GLdouble _pixdy, GLdouble _eyedx, GLdouble _eyedy, GLdouble _focus);
void accPerspective(GLdouble _fovy, GLdouble _aspect, GLdouble _near, GLdouble _far, GLdouble _pixdx, GLdouble _pixdy, GLdouble _eyedx, GLdouble _eyedy, GLdouble _focus);


struct Image {
	unsigned long sizeX;
	unsigned long sizeY;
	unsigned char *pixels;
};

int LoadBMP(char *filename, Image *image);
unsigned int load_texture(char *filename);
#endif