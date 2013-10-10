#include "ControlPanel.h"
#include "WindowGLDisplay.h"
#include "vl/VLd.h"
#include "glFuncs.h"
#include "DataManager.h"

#define BUFSIZE 1024
GLuint selectBuf[BUFSIZE];
GLint hits;
bool  choosingParticles = false;

void LightInit()
{
	static float ambient[]             = {0.2, 0.2, 0.2, 1.0};
	static float diffuse[]             = {0.6, 0.6, 0.6, 1.0};
	static float front_mat_shininess[] = {60.0};
	static float front_mat_specular[]  = {0.2, 0.2,  0.2,  1.0};
	static float front_mat_diffuse[]   = {0.5, 0.28, 0.38, 1.0};
	static float lmodel_ambient[]      = {0.2, 0.2,  0.2,  1.0};
	static float lmodel_twoside[]      = {GL_FALSE};

	GLfloat position[] = {1.0,0.0,0.0,0.0};
	GLfloat position1[] = {-1.0,0.0,0.0,0.0};
	GLfloat position2[] = {0.0,0.0,1.0,0.0};
	GLfloat position3[] = {0.0,0.0,-1.0,0.0};

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,  lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);

	glEnable( GL_LIGHT1);
	glLightfv(GL_LIGHT1,GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1,GL_POSITION, position2);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, front_mat_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  front_mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   front_mat_diffuse);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);
}

void inits(void){
	glClearAccum(0.0,0.0,0.0,0.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);
	LightInit();
}

WindowGLDisplay::WindowGLDisplay(int x, int y, int w, int h): GlWindow(x,y,w,h,NULL),mTrackball(Vec3d(0,0,0), h/2.5)
{
	mWinWidth = w;
	mWinHeight = h;
	resetCameraPosition();	
}

void WindowGLDisplay::resetCameraPosition() {
	
	mSelectedMark = -1;
	mTrackball = Trackball(Vec3d(0,0,0), mWinHeight/2.5);

	mZoom = mZangle = mTranslateX = mTranslateY = 0;

	mXangle = mXstart = 0;
	mYangle = mYstart = 180;
	mControlState = mShiftState = mAltState = mLockState = mTabState = false;
	mPicking = mRotatingXY = mZooming = mTranslating = false;
	mFixedTrans = vl_0;
	mMouseDown = false;

	mShowConstraints = true;
	mShowModel =  true;
	mShowMarker = false;
	mPlayback = false;

	mForceDir = vl_0;

	mInitEye = Vec3d(0,0,3.0);
	mInitLookAt = Vec3d(0, 0, -100.0) ;
	mInitUp = Vec3d(0, 1, 0) ;

	mScaleGL = 0.012;

	mBodyTrackBall=NULL;
	mAntiAlias = false;
}

void WindowGLDisplay::draw(){
	inits();
	resetCamera();
	render();
}

void WindowGLDisplay::render()
{
	if (DataManager::gCurrentScene == SCENE_GALILEO) glClearColor(0.55f, 0.55f, 0.7f, 1.0f);
	else											 glClearColor(0.35f, 0.35f, 0.6f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	double *rotationMat = new double[16];
	mTrackball.GetCurrentRotation(rotationMat);
	glMultMatrixd( rotationMat );

	glDisable( GL_LIGHTING );
	if(mRotatingXY || mZooming || mTranslating){
		glColor3f( 1.0f, 0.0f, 0.0f );
		DrawArrow(vl_0, Vec3d(1,0,0), 0.4, 0.01);

		glColor3f( 0.0f, 1.0f, 0.0f );
		DrawArrow(vl_0, Vec3d(0,1,0), 0.4, 0.01);

		glColor3f( 0.0f, 0.0f, 1.0f );
		DrawArrow(vl_0, Vec3d(0,0,1), 0.4, 0.01);
	}
	glEnable( GL_LIGHTING );

	glTranslatef(mFixedTrans[0] / 30.0, mFixedTrans[1] / 30, mFixedTrans[2] / 10);

	if (DataManager::gCurrentScene == SCENE_GALILEO) {
		glTranslatef(0.0f, -0.5f*DataManager::mInitialHeight, -DataManager::mInitialHeight);
	}
	else if (DataManager::gCurrentScene == SCENE_FOUNTAIN) {
		glTranslatef(0.0f, -0.5f*DataManager::mFountainHeight, -DataManager::mFountainHeight);
	}
	else if (DataManager::gCurrentScene == SCENE_ROPE) {
		glTranslatef(0, -1.5, 0);
	}

	// curr frame to be displayed
	int currFrame = DataManager::mUI->mControl->getCurrentFrame();

	// ------------------------------ your drawing code starts here  --------------------------------
	
	std::vector<Particle>& particles = DataManager::mParticles[DataManager::mParticles.size()-1];
	Vec3d center(0,0,0);

	if (DataManager::mUI->mSim_but->value()) {				     // during simulation
		particles = DataManager::mParticles[DataManager::mParticles.size()-1];
		if (DataManager::gCurrentScene == SCENE_SNOW)	  center = DataManager::mVolumeCenter;
		if (DataManager::gCurrentScene == SCENE_FOUNTAIN) center = DataManager::mBallCenter;
	} else if (currFrame < DataManager::mParticles.size()) {	// during playback
		particles = DataManager::mParticles[currFrame];
		if (DataManager::gCurrentScene == SCENE_SNOW)     center = DataManager::mCenter[currFrame];
		if (DataManager::gCurrentScene == SCENE_FOUNTAIN) center = DataManager::mCenter[currFrame];
	}
	
	// draw particles
	double prad;
	switch (DataManager::gCurrentScene) {
		case SCENE_GALILEO:   prad = 0.5;  break;
		case SCENE_SNOW:      prad = DataManager::mCollisionEpsilon; break;
		case SCENE_FOUNTAIN:  prad = DataManager::mCollisionEpsilon; break;
		case SCENE_TINKERTOY: prad = 0.075;  break;
		case SCENE_ROPE:      prad = DataManager::mCollisionEpsilon; break;
	}
	for (int i = 0; i < particles.size(); i++) {
		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(particles[i].pos[0], particles[i].pos[1], particles[i].pos[2]);
		
		if (DataManager::gCurrentScene == SCENE_TINKERTOY && i == DataManager::mSelectedParticle) {
			glColor3f(1.0f, 1.0f, 0.0f);
		}
		else if (DataManager::gCurrentScene != SCENE_SNOW || DataManager::mColorParticles)
			glColor3f(particles[i].color[0], particles[i].color[1], particles[i].color[2]);
		else
			glColor3f(1.0f, 1.0f, 1.0f);

		glutSolidSphere(prad, 8, 8);
		glPopMatrix();
	}

	// draw extras 
	if (DataManager::gCurrentScene == SCENE_GALILEO) 
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
			glVertex3f(-8.0f, 0.0f, -8.0f);
			glVertex3f(-8.0f, 0.0f,  8.0f);
			glVertex3f( 8.0f, 0.0f,  8.0f);
			glVertex3f( 8.0f, 0.0f, -8.0f);
		glEnd();
	}
	else if (DataManager::gCurrentScene == SCENE_SNOW)
	{
		glDisable(GL_LIGHTING);
		glLineWidth(1.0);
		if (mPicking == true)	glColor3f(1.0, 1.0, 0.0);
		else					glColor3f(1.0, 0.0, 0.0);
		glTranslatef(center[0], center[1], center[2]);
		if (DataManager::mSnowVolume == 0) {
			glutWireCube(2);
		}
		else {
			glRotatef(90, 1, 0, 0);
			glutWireSphere(1, 16, 16);
			glRotatef(-90, 1, 0, 0);
		}
		glEnable(GL_LIGHTING);
	}
	else if (DataManager::gCurrentScene == SCENE_FOUNTAIN) 
	{
		glDisable(GL_LIGHTING);
		glLineWidth(1.0);
		glColor3f(1, 0, 0);

		glPushMatrix();
		glTranslatef(center[0], center[1], center[2]);
		glRotatef(90, 1, 0, 0);
		glutWireSphere(0.25, 16, 16);
		glPopMatrix();

		glColor3f(1, 1, 0);
		glBegin(GL_QUADS);
			glVertex3f(-4.0f, 0.0f, -4.0f);
			glVertex3f(-4.0f, 0.0f,  4.0f);
			glVertex3f( 4.0f, 0.0f,  4.0f);
			glVertex3f( 4.0f, 0.0f, -4.0f);
		glEnd();

		glEnable(GL_LIGHTING);
	}
	else if (DataManager::gCurrentScene == SCENE_ROPE) {
		glDisable(GL_LIGHTING);
		
		glLineWidth(1.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		for (unsigned int i = 1; i < particles.size(); i++) {
			glVertex3f(particles[i-1].pos[0], particles[i-1].pos[1], particles[i-1].pos[2]);
			glVertex3f(particles[i  ].pos[0], particles[i  ].pos[1], particles[i  ].pos[2]);
		}
		glEnd();
		glLineWidth(1.0f);
		
		glColor3f(1, 0, 0);
		glPushMatrix();
		Vec3d sbc = DataManager::mSpringBall;
		glTranslatef(sbc[0], sbc[1], sbc[2]);
		glRotatef(90, 1, 0, 0);
		glutWireSphere(0.25, 16, 16);
		glPopMatrix();

		glColor3f(1, 1, 0);
		glBegin(GL_QUADS);
			glVertex3f(-4.0f, 0.0f, -4.0f);
			glVertex3f(-4.0f, 0.0f,  4.0f);
			glVertex3f( 4.0f, 0.0f,  4.0f);
			glVertex3f( 4.0f, 0.0f, -4.0f);
		glEnd();

		glEnable(GL_LIGHTING);
	}
    else if (DataManager::gCurrentScene == SCENE_TINKERTOY)
    {
		float r = DataManager::mCircleWireRadius;
		Vec3d c = DataManager::mCircleWireCenter;
        const float PI = 3.14159265;
        float delta_theta = 0.1;

		glColor3f(1, 0, 0);
		glDisable(GL_LIGHTING);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
		glBegin( GL_LINE_LOOP ); // OR GL_LINE_LOOP
        for( float angle = 0; angle < 2*PI; angle += delta_theta )
            glVertex3f( c[0] + r*cos(angle), c[1] + r*sin(angle), c[2] );
        glEnd();
        
		int sel = DataManager::mSelectedParticle;
		if (sel >= 0 && mPicking) {
			glColor3f(0.0f, 1.0f, 0.0f);
			glLineWidth(2.0f);
			glBegin(GL_LINES);
				glVertex3f(particles[sel].pos[0], particles[sel].pos[1], particles[sel].pos[2]);
				glVertex3f(DataManager::mMouse3Dpos[0], DataManager::mMouse3Dpos[1], 
						   DataManager::mMouse3Dpos[2]);
			glEnd();
			glLineWidth(1.0f);
		}

		glColor3f(0,0,0);
		glBegin(GL_LINES);
		for (int i = 0; i < DataManager::mInitFixDistConstraints.size(); i++) {
			std::pair<int, int>& parts = DataManager::mInitFixDistConstraints[i];
			Particle &p1 = particles[parts.first];
			Particle &p2 = particles[parts.second];
			glVertex3f(p1.pos[0], p1.pos[1], p1.pos[2]);
			glVertex3f(p2.pos[0], p2.pos[1], p2.pos[2]);
		}
		glEnd();
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_LIGHTING);
	}


	// -------------------------------your drawing code end here  -----------------------------------

	// draw the editing ball
	if(mBodyTrackBall) {
		mBodyTrackBall->Draw(mWinWidth, mWinHeight);
	}

	// Draw the globe
	if(mRotatingXY){
		glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport( 0, 0, mWinWidth, mWinHeight );
		gluOrtho2D(0.0, (GLdouble)mWinWidth, 0.0, (GLdouble)mWinHeight);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable( GL_LIGHTING );
		glLineWidth(2.0);
		glColor3f( 1.0f, 1.0f, 0.0f );
		double r = mTrackball.mRadius;
		glBegin( GL_LINE_LOOP);		
		for(int i = 0; i < 360; i+=4){
			double theta = i / 180.0 * M_PI;
			double x = r * cos(theta);
			double y = r * sin(theta);
			glVertex2d( (GLdouble)((mWinWidth >> 1) + x), (GLdouble)((mWinHeight >> 1) + y));
		}
		glEnd();
		glPopMatrix();
		glEnable( GL_LIGHTING );
	}
	delete [] rotationMat;

	glFlush();
}



int WindowGLDisplay::handle(int event)
{  
	Vec3d tempPos;
	float xtrans, ytrans;
	std::string lastPress;

	mMouse[0] = fltk::event_x() - (mWinWidth >> 1);
	mMouse[1] = (mWinHeight >> 1) - fltk::event_y();

	int nValidHandle = 0;
	switch(event){

		case fltk::KEY:
			break;

		case fltk::PUSH:
			mMouse[0] = fltk::event_x() - (mWinWidth >> 1);
			mMouse[1] = (mWinHeight >> 1) - fltk::event_y();

			mMouseDown = true;
			mWhichClick = -1; // Oscar: patch to prevent mouse button locks

			mTrackball.StartBall(mMouse[0],mMouse[1]);

			if( fltk::get_key_state(fltk::LeftShiftKey) || fltk::get_key_state(fltk::RightShiftKey) )
				mShiftState = true;
			else
				mShiftState = false;

			if( fltk::get_key_state(fltk::LeftCtrlKey) || fltk::get_key_state(fltk::RightCtrlKey) )
				mControlState = true;
			else
				mControlState = false;

			if( fltk::get_key_state(fltk::LeftAltKey) || fltk::get_key_state(fltk::RightAltKey) )
				mAltState = true;
			else
				mAltState = false;

			if( fltk::get_key_state(fltk::TabKey)  )
				mTabState = true;
			else
				mTabState = false;

			if( fltk::get_key_state('l') || fltk::get_key_state('L') ){
				mLockState = true;
			}else
				mLockState = false;

			if(fltk::event_button() == 1){
				if(fltk::get_key_state(fltk::LeftCtrlKey))
					mWhichClick = 1;
				else if(fltk::get_key_state(fltk::LeftAltKey))
					mWhichClick = 2;
				else 
					mWhichClick = 0;
			}

			if (mWhichClick == 0){	
				if(mShiftState)
					mRotatingXY = true;

				mXstart = mMouse[0];
				mYstart = mMouse[1];

			}else if(fltk::event_button() == 2 || mWhichClick == 1){
				if(mShiftState){
					mTranslating = true;
				}
				else {
					// temp code
					mPicking=true;
					draw();
					mPicking=false;
				}
				mXstart = mMouse[0];
				mYstart = mMouse[1];
			}else if(fltk::event_button() == 3 || mWhichClick == 2){
				if(mShiftState){
					mZooming = true; 
				}
				else {
					// temp code
					mPicking = DataManager::gCurrentScene == SCENE_SNOW;
					draw();
				}
				mXstart = mMouse[0];
				mYstart = mMouse[1]; 
			}

			if (DataManager::gCurrentScene == SCENE_TINKERTOY && mRotatingXY) {
				mRotatingXY = false;
				mPicking    = true;

				GLdouble modelMatrix[16];
				GLdouble projMatrix[16];
				GLint    viewport[4];
				glGetDoublev (GL_MODELVIEW_MATRIX,  modelMatrix);
				glGetDoublev (GL_PROJECTION_MATRIX, projMatrix);
				glGetIntegerv(GL_VIEWPORT,          viewport); 

				std::vector<Particle>& parts = DataManager::mParticles.back();
				double minDist  = 1e32;
				double zDist;
				int    nearPart = -1;
				double winx, winy, winz;
				for (int i = 0; i < parts.size(); i++) {
					gluProject(parts[i].pos[0], parts[i].pos[1], parts[i].pos[2],
							   modelMatrix, projMatrix, viewport,
							   &winx, &winy, &winz);
					double dx = winx - (mMouse[0] + 0.5*mWinWidth);
					double dy = winy - (mMouse[1] + 0.5*mWinHeight);
					double dist = dx*dx + dy*dy;
					if (dist < minDist) {
						minDist  = dist;
						nearPart = i;
						zDist = winz;
					}
				}

				double mouseX, mouseY, mouseZ;
				gluUnProject(mMouse[0] + 0.5*mWinWidth, mMouse[1] + 0.5*mWinHeight, zDist, 
							 modelMatrix, projMatrix, viewport,
							 &mouseX, &mouseY, &mouseZ);
				DataManager::mMouse3Dpos = Vec3d(mouseX, mouseY, parts[nearPart].pos[2]);
				DataManager::mSelectedParticle = nearPart;
			}
			else if (DataManager::gCurrentScene == SCENE_TINKERTOY && fltk::event_button() == 1 && mWhichClick == 0 &&
				     !DataManager::mUI->mSim_but->value() &&
					  DataManager::mUI->mControl->getCurrentFrame() == 0)
			{
				GLdouble modelMatrix[16];
				GLdouble projMatrix[16];
				GLint    viewport[4];
				double winx, winy, winz;
				glGetDoublev(GL_MODELVIEW_MATRIX,  modelMatrix);
				glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
				glGetIntegerv(GL_VIEWPORT,         viewport); 
				Particle& part = DataManager::mParticles.back()[0];
				gluProject(part.pos[0], part.pos[1], part.pos[2],
						   modelMatrix, projMatrix, viewport,
						   &winx, &winy, &winz);
				double mouseX, mouseY, mouseZ;
				gluUnProject(mMouse[0] + 0.5*mWinWidth, mMouse[1] + 0.5*mWinHeight, winz, 
							 modelMatrix, projMatrix, viewport,
							 &mouseX, &mouseY, &mouseZ);
				Vec3d mousePoint(mouseX, mouseY, part.pos[2]);
				
				if (DataManager::mMouseTool == DataManager::MT_ADD_PARTICLE) {
					DataManager::mInitExtraParticles.push_back(mousePoint);
					DataManager::gReset = true;
					
				}
				else if (DataManager::mMouseTool == DataManager::MT_FIXED_DIST) {

					std::vector<Particle>& parts = DataManager::mParticles.back();
					double minDist  = 10;
					int    nearPart = -1;
					for (int i = 0; i < parts.size(); i++) {
						double dist = sqrlen(parts[i].pos - mousePoint);
						if (dist < minDist) {
							minDist  = dist;
							nearPart = i;
						}
					}

					if (DataManager::mSelectedParticle < 0) {
						DataManager::mSelectedParticle = nearPart;
						choosingParticles = true;
					}
					else if (nearPart >= 0) {
						if (nearPart != DataManager::mSelectedParticle) {
							DataManager::mInitFixDistConstraints.push_back(
								std::pair<int, int>(nearPart, DataManager::mSelectedParticle));
							DataManager::gReset = true;
						}
						DataManager::mSelectedParticle = -1;
						choosingParticles = false;
					}
				}
			}
			

			break;

		case fltk::DRAG:
			if(mRotatingXY) {	
				mYangle += (mMouse[0] - mXstart);
				mXangle += (mMouse[1] - mYstart);
				if(mYangle > 360)
					mYangle -= 360;
				else if(mYangle < 0)
					mYangle += 360;
				if(mXangle > 360)
					mXangle -= 360;
				else if(mXangle < 0)
					mXangle +=360;
				mXstart = mMouse[0];
				mYstart = mMouse[1];

				redraw();

				mTrackball.UpdateBall(mMouse[0],mMouse[1]);

			}else if (mZooming){	
				float xVal = mMouse[0] - mXstart;
				float yVal = mMouse[1] - mYstart;
				double shift;

				if(xVal!=0)
					shift = sqrt(xVal * xVal + yVal * yVal) * (xVal / fabs(xVal));
				else
					shift = sqrt(xVal * xVal + yVal * yVal);

				mZoom += shift;
				Mat4d tempRot;
				mTrackball.GetCurrentRotation(tempRot);
				tempRot = inv(tempRot);
				Vec4d tempTrans = tempRot * Vec4d(0, 0, shift, 1);
				mFixedTrans[0] += tempTrans[0];
				mFixedTrans[1] += tempTrans[1];
				mFixedTrans[2] += tempTrans[2];

				mXstart = mMouse[0];
				mYstart = mMouse[1];
				redraw();

			}else if (mTranslating) {
				mTranslateX += (mMouse[0] - mXstart);
				mTranslateY += (mMouse[1] - mYstart);
				Mat4d tempRot;
				mTrackball.GetCurrentRotation(tempRot);
				tempRot = inv(tempRot);
				Vec4d tempTrans = tempRot * Vec4d(mMouse[0] - mXstart, mMouse[1] - mYstart, 0, 1);
				mFixedTrans[0] += tempTrans[0];
				mFixedTrans[1] += tempTrans[1];
				mFixedTrans[2] += tempTrans[2];
				mXstart = mMouse[0];
				mYstart = mMouse[1];
				redraw();
			}
			else if (mPicking && DataManager::gCurrentScene == SCENE_SNOW) {
				mTranslateX += (mMouse[0] - mXstart);
				mTranslateY += (mMouse[1] - mYstart);
				Mat4d tempRot;
				mTrackball.GetCurrentRotation(tempRot);
				tempRot = inv(tempRot);
				Vec4d tempTrans = tempRot * Vec4d(mMouse[0] - mXstart, mMouse[1] - mYstart, 0, 1);
				DataManager::mSceneSnow->shakeVolume(0.05*Vec3d(tempTrans[0], tempTrans[1], tempTrans[2]));
				mXstart = mMouse[0];
				mYstart = mMouse[1];
				redraw();
			}
			else if (mPicking && DataManager::gCurrentScene == SCENE_TINKERTOY) {
				GLdouble modelMatrix[16];
				GLdouble projMatrix[16];
				GLint    viewport[4];
				double winx, winy, winz;
				glGetDoublev(GL_MODELVIEW_MATRIX,  modelMatrix);
				glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
				glGetIntegerv(GL_VIEWPORT,         viewport); 
				Particle& part = DataManager::mParticles.back()[DataManager::mSelectedParticle];
				gluProject(part.pos[0], part.pos[1], part.pos[2],
						   modelMatrix, projMatrix, viewport,
						   &winx, &winy, &winz);

				double mouseX, mouseY, mouseZ;
				gluUnProject(mMouse[0] + 0.5*mWinWidth, mMouse[1] + 0.5*mWinHeight, winz, 
							 modelMatrix, projMatrix, viewport,
							 &mouseX, &mouseY, &mouseZ);
				DataManager::mMouse3Dpos = Vec3d(mouseX, mouseY, part.pos[2]);
			}


			else if (mSelectedMark >= 0 && mSelectedMark < nValidHandle){
				xtrans = (mMouse[0] - mXstart)/100.0;
				ytrans = (mMouse[1] - mYstart)/100.0;
				Mat4d tempRot;
				Mat4d yRot = vl_I;
				yRot[0][0] = cos(-M_PI / 2);
				yRot[0][2] = sin(-M_PI / 2);
				yRot[2][0] = -sin(-M_PI / 2);
				yRot[2][2] = cos(-M_PI / 2);

				mTrackball.GetCurrentRotation(tempRot);
				tempRot *= yRot;
				tempRot = inv(tempRot);
				Vec4d tempTrans = tempRot * Vec4d(xtrans, ytrans, 0, 1);
			}
			else if((fltk::event_button() == 2 || mWhichClick == 1)){
			}
			mMouse[0] = fltk::event_x() - (mWinWidth >> 1);
			mMouse[1] = (mWinHeight >> 1) - fltk::event_y();

			redraw();
			break;

		case fltk::RELEASE:
			mMouseDown = false;
			mMouse[0] = fltk::event_x() - (mWinWidth >> 1);
			mMouse[1] = (mWinHeight >> 1) - fltk::event_y();

			mPicking = mRotatingXY = mZooming = mTranslating = false;

			if(mBodyTrackBall){
				delete mBodyTrackBall;
				mBodyTrackBall = NULL;
			}

			if (!choosingParticles)
				DataManager::mSelectedParticle = -1;

			redraw();
			break;

		default:
			return 0;
	}

	return 1;
}

void WindowGLDisplay::refresh()
{
	redraw();
}

void WindowGLDisplay::resizeWindow(int width, int height)
{
	resize(x(), y(), width, height);
}

void WindowGLDisplay::resize(int x, int y, int w, int h)
{
	mWinWidth = w;
	mWinHeight = h;
	resetCamera();
	GlWindow::resize(x, y, w, h);
}

void WindowGLDisplay::resetCamera()
{
	glViewport(0, 0, mWinWidth, mWinHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,mWinWidth/float(mWinHeight),.5,600.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable( GL_DEPTH_TEST );
	gluLookAt(mInitEye[0], mInitEye[1], mInitEye[2], mInitLookAt[0], mInitLookAt[1], mInitLookAt[2], mInitUp[0], mInitUp[1], mInitUp[2]);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

Vec3d WindowGLDisplay::getNew3DPos(Vec3d pos){
	Vec3d eye = GetPointEyeToWorld(mInitEye);
	Vec3d lookAt = GetPointEyeToWorld(mInitLookAt);

	Vec3d temp, newdir;
	GetMouseRay(fltk::event_x(), (mWinHeight-fltk::event_y()), temp, newdir);
	Vec3d newpos;
	newpos = eye + newdir*dot(pos-eye, lookAt-eye)/dot(newdir, lookAt-eye);
	return newpos;
}
