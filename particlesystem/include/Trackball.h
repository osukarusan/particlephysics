//////////////////////////////////////////////////////////////////////
// 
//	File: Trackball.h
// 
//	Graphics and Imaging Lab
//	Dept. of Computer Scinece and Engineering
//	University of Washington
//
// 
//	Created:       Thu Aug 04 13:47 2001 by C. Karen Liu
//	
//	Trackball controls the user interaction 
//////////////////////////////////////////////////////////////////////

#ifndef __TRACKBALL_H__
#define __TRACKBALL_H__

#include "vl/VLd.h"
#ifdef WIN32
#include <windows.h>
#include <GL/glu.h>
#elif CYGWIN
#include <GL/glu.h>
#elif MACOSX
#include <opengl/glu.h>
#endif

//Trackball Routine

class Trackball
{
	public:
		Trackball(Vec3d center, double radius){mCenter = center;mRadius=radius; mCurrQuat = Vec4d(0, 0, 0, 1);mNonCenter=false;}
		void Ball_Place(Vec3d center, double radius){mCenter = center;mRadius=radius;}
		void Ball_ComputeRotationMatrix(Mat4d &);
		void StartBall(double x, double y);
		void UpdateBall(double x, double y);
		void GetCurrentRotation(double *returnRot);
		void GetCurrentRotation(Mat4d & returnRot);
		void GetCurrentRotation(Vec4d & returnQuat);
		void Draw(int, int);
		void SetCenter(Vec3d cent){ mCenter = cent;}
		void SetCurrQuat(Vec4d q){ mCurrQuat = q; }
		double mRadius;
		inline Vec3d& getCenter(){return mCenter;}
		inline void setNoCenter(){mNonCenter=true;}
		
	private:	
		void Qt_ToMatrix(Vec4d q, Mat4d &out);
		Vec3d MouseOnSphere(double mouseX, double mouseY);
		Vec4d Qt_FromBallPoints(Vec3d from, Vec3d to);
		Vec4d Qt_Mul(Vec4d qL, Vec4d qR);
		Vec4d Qt_Conj(Vec4d q);
		
		Vec2d mStartPix;
		bool mNonCenter;

		Vec3d mCenter;
		Vec3d mStartPos;
		Vec4d mCurrQuat;
};

#endif
