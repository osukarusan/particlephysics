#ifndef _WINDOWGLDISPLAY_
#define _WINDOWGLDISPLAY_

#include "Trackball.h"

#include <fltk/run.h>
#include <fltk/GlWindow.h>
#include <fltk/draw.h>
#include <fltk/File_Chooser.h>
#include <fltk/gl.h>
#include <fltk/glut.h>
#ifdef WIN32
#include <windows.h>
#include <GL/glu.h>
#elif CYGWIN
#include <GL/glu.h>
#elif MACOSX
#include <opengl/glu.h>
#endif
#include <stdlib.h>
#include "vl/VLd.h"
#include <vector>

class WindowGLDisplay : public fltk::GlWindow
{
public:
	WindowGLDisplay(int x, int y, int w, int h);

	bool mAntiAlias;
	//virtual functions that replace GlWindow
	void draw();
	void render();
	int handle(int event);
	void refresh();
	void resizeWindow(int width, int height);
	void resize( int x, int y, int w, int h );

	void resetCameraPosition();

	bool mShowConstraints;
	bool mShowModel;
	bool mShowMarker;
	bool mPlayback;

	int mWinWidth, mWinHeight;
	Trackball mTrackball;
	bool mMouseDown;
	// void* mContext;

private:
	void resetCamera();

	int mSelectedMark;
	Vec3d mMouse;
	float mXstart, mYstart, mXangle, mYangle, mZangle, mZoom, mTranslateX, mTranslateY;
	bool mControlState, mShiftState, mAltState, mTabState, mLockState;
	Vec3d mFixedTrans;
	bool mRotatingXY, mZooming, mTranslating, mPicking;
	std::string mCommand;
	int mWhichClick;
	Vec3d mForceDir;

	Vec3d mInitEye;
	Vec3d mInitLookAt;
	Vec3d mInitUp;

	double mScaleGL;	// pixel to coord frame scale for 2D

	// picking stuff
	Trackball *mBodyTrackBall;

	void startPicking();
	void stopPicking();
	void processHits(GLint hits, GLuint buffer[], int sw);

	// gets new 3D position of point in same plane as point "pos"
	Vec3d getNew3DPos(Vec3d pos);
};

#endif
