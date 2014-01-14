// generated by Fast Light User Interface Designer (fluid) version 2.1000

#include "ControlPanel.h"
#include "DataManager.h"


void ControlPanel::hideAll() {
	this->mHeight_sli->hide();
	this->mParticles_sli->hide();
	this->mCube_radio->hide();
	this->mBall_radio->hide();
	this->mPartCollision_check->hide();
	this->mRestitution_in->hide();
	this->mParticleRad_in->hide();
	this->mColor_but->hide();
	this->mDamp_in->hide();
	this->mAddParticle_but->hide();
	this->mAddFixedDist_but->hide();
	this->mFountainParticles_sli->hide();
	this->mFountainHeight_sli->hide();
	this->mRopeParticles_sli->hide();
	this->mSpringK_in->hide();
	this->mSpringDamp_in->hide();
	this->mSpringBallRad_in->hide();
	this->mFixedCloth_but->hide();
	this->mBending_but->hide();
	this->mFluid2D_radio->hide();
	this->mFluid3D_radio->hide();
	this->mFluidDensity_in->hide();
	this->mFluidSurface_in->hide();
	this->mFluidViscosity_in->hide();
	this->mFluidViscosity2_in->hide();
}

void ControlPanel::setScene(SceneType scene) {

	hideAll();

	switch (scene) {
		case SCENE_GALILEO:
			this->mHeight_sli->set_visible();
			break;
		case SCENE_SNOW:
			this->mParticles_sli->set_visible();
			this->mCube_radio->set_visible();
			this->mBall_radio->set_visible();
			this->mPartCollision_check->set_visible();
			this->mRestitution_in->set_visible();	
			this->mParticleRad_in->set_visible();
			this->mColor_but->set_visible();
			this->mRestitution_in->value(0.8);
			DataManager::mCoeffRestitution = 0.8;
			break;
		case SCENE_FOUNTAIN:
			this->mPartCollision_check->hide();
			this->mRestitution_in->set_visible();	
			this->mParticleRad_in->set_visible();
			this->mFountainParticles_sli->set_visible();
			this->mFountainHeight_sli->set_visible();
			this->mRestitution_in->value(0.25);
			DataManager::mCoeffRestitution = 0.25;
			break;
		case SCENE_TINKERTOY:
			this->mDamp_in->set_visible();
			this->mAddParticle_but->set_visible();
			this->mAddFixedDist_but->set_visible();
			break;
		case SCENE_ROPE:
		case SCENE_CLOTH:
			this->mRestitution_in->set_visible();	
			this->mParticleRad_in->set_visible();
			this->mRopeParticles_sli->set_visible();
			this->mSpringK_in->set_visible();
			this->mSpringDamp_in->set_visible();
			this->mSpringBallRad_in->set_visible();
			if (scene == SCENE_CLOTH) {
				this->mFixedCloth_but->set_visible();
				this->mBending_but->set_visible();
			}
			this->mRestitution_in->value(0.1);
			DataManager::mCoeffRestitution = 0.1;
			break;
		case SCENE_FLUID:
			this->mFluid2D_radio->set_visible();
			this->mFluid3D_radio->set_visible();
			this->mFluidDensity_in->set_visible();
			this->mFluidSurface_in->set_visible();
			this->mFluidViscosity_in->set_visible();
			this->mFluidViscosity2_in->set_visible();
			break;
		default: 
			break;
	}
	mControlWindow->redraw();
}


inline void ControlPanel::cb_mGravity_in_i(fltk::ValueInput* o, void*) {  double current = (double)o->value();
  if (current < o->minimum()) current = o->minimum();
  else if (current > o->maximum()) current = o->maximum();
  o->value (current);
  DataManager::mGravityValue = current;
  DataManager::gReset = true;
}
void ControlPanel::cb_mGravity_in(fltk::ValueInput* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mGravity_in_i(o,v);
}

inline void ControlPanel::cb_mStep_in_i(fltk::ValueInput* o, void*) {
  double current = (double)o->value();
  if (current < o->minimum()) current = o->minimum();
  else if (current > o->maximum()) current = o->maximum();
  o->value (current);
  DataManager::mTimeStep = current;
  DataManager::gReset = true;
}
void ControlPanel::cb_mStep_in(fltk::ValueInput* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mStep_in_i(o,v);
}

inline void ControlPanel::cb_mHeight_sli_i(fltk::ValueSlider* o, void*) {
  double current = (double)o->value();
  if (current < o->minimum()) current = o->minimum();
  else if (current > o->maximum()) current = o->maximum();
  o->value (current);
  DataManager::mInitialHeight = current;
  DataManager::gReset = true;
}
void ControlPanel::cb_mHeight_sli(fltk::ValueSlider* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mHeight_sli_i(o,v);
}

inline void ControlPanel::cb_mFountainHeight_sli_i(fltk::ValueSlider* o, void*) {
  double current = (double)o->value();
  if (current < o->minimum()) current = o->minimum();
  else if (current > o->maximum()) current = o->maximum();
  o->value (current);
  DataManager::mFountainHeight = current;
  DataManager::gReset = true;
}
void ControlPanel::cb_mFountainHeight_sli(fltk::ValueSlider* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mFountainHeight_sli_i(o,v);
}

inline void ControlPanel::cb_mParticles_sli_i(fltk::ValueSlider* o, void*) {
  double current = (double)o->value();
  if (current < o->minimum()) current = o->minimum();
  else if (current > o->maximum()) current = o->maximum();
  o->value (current);
  DataManager::mNumParticles = current;
  DataManager::gReset = true;
}
void ControlPanel::cb_mParticles_sli(fltk::ValueSlider* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mParticles_sli_i(o,v);
}

inline void ControlPanel::cb_mFountainParticles_sli_i(fltk::ValueSlider* o, void*) {
  double current = (double)o->value();
  if (current < o->minimum()) current = o->minimum();
  else if (current > o->maximum()) current = o->maximum();
  o->value (current);
  DataManager::mFountainParticles = current;
  DataManager::gReset = true;
}
void ControlPanel::cb_mFountainParticles_sli(fltk::ValueSlider* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mFountainParticles_sli_i(o,v);
}

inline void ControlPanel::cb_mRopeParticles_sli_i(fltk::ValueSlider* o, void*) {
  double current = (double)o->value();
  if (current < o->minimum()) current = o->minimum();
  else if (current > o->maximum()) current = o->maximum();
  o->value (current);
  DataManager::mRopeParticles = current;
  DataManager::gReset = true;
}
void ControlPanel::cb_mRopeParticles_sli(fltk::ValueSlider* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mRopeParticles_sli_i(o,v);
}


inline void ControlPanel::cb_mFluidSurface_in_i(fltk::ValueInput* o, void*) {  double current = (double)o->value();
  if (current < o->minimum()) current = o->minimum();
  else if (current > o->maximum()) current = o->maximum();
  o->value (current);
  DataManager::mFluidSurfaceTension = current;
  DataManager::gReset = true;
}
void ControlPanel::cb_mFluidSurface_in(fltk::ValueInput* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mFluidSurface_in_i(o,v);
}

inline void ControlPanel::cb_mFluidViscosity_in_i(fltk::ValueInput* o, void*) {  double current = (double)o->value();
  if (current < o->minimum()) current = o->minimum();
  else if (current > o->maximum()) current = o->maximum();
  o->value (current);
  DataManager::mFluidLinearViscosity = current;
  DataManager::gReset = true;
}
void ControlPanel::cb_mFluidViscosity_in(fltk::ValueInput* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mFluidViscosity_in_i(o,v);
}

inline void ControlPanel::cb_mFluidViscosity2_in_i(fltk::ValueInput* o, void*) {  double current = (double)o->value();
  if (current < o->minimum()) current = o->minimum();
  else if (current > o->maximum()) current = o->maximum();
  o->value (current);
  DataManager::mFluidQuadraticViscosity = current;
  DataManager::gReset = true;
}
void ControlPanel::cb_mFluidViscosity2_in(fltk::ValueInput* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mFluidViscosity2_in_i(o,v);
}

inline void ControlPanel::cb_mFluidDensity_in_i(fltk::ValueInput* o, void*) {  double current = (double)o->value();
  if (current < o->minimum()) current = o->minimum();
  else if (current > o->maximum()) current = o->maximum();
  o->value (current);
  DataManager::mFluidRestDensity = current;
  DataManager::gReset = true;
}
void ControlPanel::cb_mFluidDensity_in(fltk::ValueInput* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mFluidDensity_in_i(o,v);
}


inline void ControlPanel::cb_mFluid2D_radio_i(fltk::RadioButton* o, void*) {
  DataManager::mFluid3D = false;
  DataManager::gReset = true;
}
void ControlPanel::cb_mFluid2D_radio(fltk::RadioButton* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mFluid2D_radio_i(o,v);
}

inline void ControlPanel::cb_mFluid3D_radio_i(fltk::RadioButton* o, void*) {
  DataManager::mFluid3D = true;
  DataManager::gReset = true;
}
void ControlPanel::cb_mFluid3D_radio(fltk::RadioButton* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mFluid3D_radio_i(o,v);
}



inline void ControlPanel::cb_mPartCollision_check_i(fltk::CheckButton* o, void*) {
  DataManager::mParticleColl = o->value();
  DataManager::gReset = true;
}
void ControlPanel::cb_mPartCollision_check(fltk::CheckButton* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mPartCollision_check_i(o,v);
}

inline void ControlPanel::cb_mCube_radio_i(fltk::RadioButton* o, void*) {
  DataManager::mSnowVolume = 0;
  DataManager::gReset = true;
}
void ControlPanel::cb_mCube_radio(fltk::RadioButton* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mCube_radio_i(o,v);
}

inline void ControlPanel::cb_mBall_radio_i(fltk::RadioButton* o, void*) {
  DataManager::mSnowVolume = 1;
  DataManager::gReset = true;
}
void ControlPanel::cb_mBall_radio(fltk::RadioButton* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mBall_radio_i(o,v);
}

inline void ControlPanel::cb_mRestitution_in_i(fltk::ValueInput* o, void*) {
  double current = (double)o->value();
  if (current < o->minimum()) current = o->minimum();
  else if (current > o->maximum()) current = o->maximum();
  o->value (current);
  DataManager::mCoeffRestitution = current;
  DataManager::gReset = true;
}
void ControlPanel::cb_mRestitution_in(fltk::ValueInput* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mRestitution_in_i(o,v);
}

inline void ControlPanel::cb_mParticleRad_in_i(fltk::ValueInput* o, void*) {
  double current = (double)o->value();
  if (current < o->minimum()) current = o->minimum();
  else if (current > o->maximum()) current = o->maximum();
  o->value (current);
  DataManager::mCollisionEpsilon = current;
  DataManager::gReset = true;
}
void ControlPanel::cb_mParticleRad_in(fltk::ValueInput* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mParticleRad_in_i(o,v);
}

inline void ControlPanel::cb_mColor_but_i(fltk::Button*, void*) {
	DataManager::mColorParticles = !DataManager::mColorParticles;
}
void ControlPanel::cb_mColor_but(fltk::Button* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mColor_but_i(o,v);
}

inline void ControlPanel::cb_mFixedCloth_but_i(fltk::Button*, void*) {
	DataManager::mFixedCloth = !DataManager::mFixedCloth;
    DataManager::gReset = true;
}
void ControlPanel::cb_mFixedCloth_but(fltk::Button* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mFixedCloth_but_i(o,v);
}

inline void ControlPanel::cb_mBending_but_i(fltk::Button*, void*) {
	DataManager::mBendingCloth = !DataManager::mBendingCloth;
    DataManager::gReset = true;
}
void ControlPanel::cb_mBending_but(fltk::Button* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mBending_but_i(o,v);
}

inline void ControlPanel::cb_mDamp_in_i(fltk::ValueInput* o, void*) {
  double current = (double)o->value();
  if (current < o->minimum()) current = o->minimum();
  else if (current > o->maximum()) current = o->maximum();
  o->value (current);
  DataManager::mDampCoeff = current;
  DataManager::gReset = true;
}
void ControlPanel::cb_mDamp_in(fltk::ValueInput* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mDamp_in_i(o,v);
}


inline void ControlPanel::cb_mSpringK_in_i(fltk::ValueInput* o, void*) {
  double current = (double)o->value();
  if (current < o->minimum()) current = o->minimum();
  else if (current > o->maximum()) current = o->maximum();
  o->value (current);
  DataManager::mSpringK = current;
  DataManager::gReset = true;
}
void ControlPanel::cb_mSpringK_in(fltk::ValueInput* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mSpringK_in_i(o,v);
}


inline void ControlPanel::cb_mSpringDamp_in_i(fltk::ValueInput* o, void*) {
  double current = (double)o->value();
  if (current < o->minimum()) current = o->minimum();
  else if (current > o->maximum()) current = o->maximum();
  o->value (current);
  DataManager::mSpringDamp = current;
  DataManager::gReset = true;
}
void ControlPanel::cb_mSpringDamp_in(fltk::ValueInput* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mSpringDamp_in_i(o,v);
}


inline void ControlPanel::cb_mSpringBallRad_in_i(fltk::ValueInput* o, void*) {
  double current = (double)o->value();
  if (current < o->minimum()) current = o->minimum();
  else if (current > o->maximum()) current = o->maximum();
  o->value (current);
  DataManager::mSpringBallRadius = current;
  DataManager::gReset = true;
}
void ControlPanel::cb_mSpringBallRad_in(fltk::ValueInput* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mSpringBallRad_in_i(o,v);
}

inline void ControlPanel::cb_mAddParticle_but_i(fltk::Button*, void*) {
	if (this->mAddParticle_but->value()) {
		DataManager::mMouseTool = DataManager::MT_ADD_PARTICLE;
		mAddFixedDist_but->value(false);
	} 
	else 
		DataManager::mMouseTool = DataManager::MT_NONE;

}
void ControlPanel::cb_mAddParticle_but(fltk::Button* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mAddParticle_but_i(o,v);
}

inline void ControlPanel::cb_mAddFixedDist_but_i(fltk::Button*, void*) {
	if (this->mAddFixedDist_but->value()) {
		DataManager::mMouseTool = DataManager::MT_FIXED_DIST;
		mAddParticle_but->value(false);
	}
	else {
		DataManager::mMouseTool = DataManager::MT_NONE;
		DataManager::mSelectedParticle = -1;
	}
}
void ControlPanel::cb_mAddFixedDist_but(fltk::Button* o, void* v) {
	((ControlPanel*)(o->parent()->user_data()))->cb_mAddFixedDist_but_i(o,v);
}




inline void ControlPanel::cb_mFrame_sli_i(fltk::ValueSlider* o, void*) {
  int current = (int)o->value();
  if( current > getEnd() )
  	current = getEnd();
  if( current < getBegin() )
  	current = getBegin();
  o->value( current );
  o->selection_color(15);
  o->textcolor(15);
  o->labelcolor(15);
}
void ControlPanel::cb_mFrame_sli(fltk::ValueSlider* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mFrame_sli_i(o,v);
}

inline void ControlPanel::cb_mBegin_sli_i(fltk::ValueSlider* o, void*) {
  int val = (int)o->value();
  if( val > getEnd() ){
  	val = getEnd();
  }
  else if ( val > getCurrentFrame() ){
  	mFrame_sli->value(val);
  	mFrame_sli->selection_color(15);
  	mFrame_sli->textcolor(15);
  	mFrame_sli->labelcolor(15);
  }
  o->value(val);
}
void ControlPanel::cb_mBegin_sli(fltk::ValueSlider* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mBegin_sli_i(o,v);
}

inline void ControlPanel::cb_mEnd_sli_i(fltk::ValueSlider* o, void*) {
  int val = (int)o->value();
  if( val < getBegin() ){
  	val = getBegin();
  }
  else if( val < getCurrentFrame() ){
  	mFrame_sli->value(val);		
  	mFrame_sli->selection_color(15);
  	mFrame_sli->textcolor(15);
  	mFrame_sli->labelcolor(15);
  }
  o->value(val);
}
void ControlPanel::cb_mEnd_sli(fltk::ValueSlider* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mEnd_sli_i(o,v);
}

inline void ControlPanel::cb_mPlay_but_i(fltk::Button*, void*) {
  mPlaying = !mPlaying;
  if(mPlaying)
  	mPlay_but->label("@||");
  else
  	mPlay_but->label("@>");
}
void ControlPanel::cb_mPlay_but(fltk::Button* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mPlay_but_i(o,v);
}

inline void ControlPanel::cb_mFrameStep_inp_i(fltk::ValueInput* o, void*) {
  int current = (int)o->value();
  if (current < o->minimum()) current = o->minimum();
  else if (current > o->maximum()) current = o->maximum();
  o->value (current);
  DataManager::mFrameSkip = current;
}
void ControlPanel::cb_mFrameStep_inp(fltk::ValueInput* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mFrameStep_inp_i(o,v);
}

inline void ControlPanel::cb_mForward_but_i(fltk::Button*, void*) {
  advanceFrame((int)mFrameStep_inp->value());
}
void ControlPanel::cb_mForward_but(fltk::Button* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mForward_but_i(o,v);
}

inline void ControlPanel::cb_mBackward_but_i(fltk::Button*, void*) {
  decrementFrame((int)mFrameStep_inp->value());
}
void ControlPanel::cb_mBackward_but(fltk::Button* o, void* v) {
  ((ControlPanel*)(o->parent()->user_data()))->cb_mBackward_but_i(o,v);
}

void ControlPanel::setRange(int _maxFrame) {
  mFrame_sli->range(0, _maxFrame);
  mBegin_sli->range(0, _maxFrame);
  mBegin_sli->value(0);
  mEnd_sli->range(0, _maxFrame);
  mEnd_sli->value(_maxFrame);
  //mFrameCounter_inp->maximum(_maxFrame);
  if(mFrame_sli->value()>_maxFrame){
  	mFrame_sli->value(_maxFrame);
  	//mFrameCounter_cou->value(_maxFrame);
  }
  mControlWindow->redraw();
}

ControlPanel::ControlPanel() {
  fltk::DoubleBufferWindow* w;
   {fltk::DoubleBufferWindow* o = mControlWindow = new fltk::DoubleBufferWindow(706, 582, 640, 145);
    w = o;
    o->type(241);
    o->shortcut(0xff1b);
    o->user_data((void*)(this));
    o->begin();
	
	{fltk::ValueInput* o = mGravity_in = new fltk::ValueInput(47, 25, 80, 18, "Gravity");
      o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
	  o->range(0,20);
      o->step(0.01);
	  o->value(9.81);
      o->callback((fltk::Callback*)cb_mGravity_in);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
	{fltk::ValueInput* o = mStep_in = new fltk::ValueInput(47, 5, 80, 18, "t step");
      o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
      o->range(0.0001, 1.00);
      o->step(0.005);
	  o->value(0.007);
      o->callback((fltk::Callback*)cb_mStep_in);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
	{fltk::ValueSlider* o = mHeight_sli = new fltk::ValueSlider(190, 5, 317, 18, "Height");
      o->type(fltk::ValueSlider::TICK_ABOVE);
	  o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
      o->range(80, 200);
      o->step(1);
	  o->value(80);
      o->callback((fltk::Callback*)cb_mHeight_sli);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
	{fltk::ValueSlider* o = mParticles_sli = new fltk::ValueSlider(200, 5, 307, 18, "Particles");
      o->type(fltk::ValueSlider::TICK_ABOVE);
	  o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
      o->range(50, 500);
      o->step(1);
	  o->value(50);
      o->callback((fltk::Callback*)cb_mParticles_sli);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }

	{fltk::ValueInput* o = mFluidDensity_in = new fltk::ValueInput(380, 5, 65, 18, "Rest Density");
      o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
	  o->range(0,1000);
      o->step(10);
	  o->value(100);
	  o->callback((fltk::Callback*)cb_mFluidDensity_in);
      o->align(fltk::ALIGN_LEFT);
	  o->when(fltk::WHEN_CHANGED);
    }
	{fltk::ValueInput* o = mFluidSurface_in = new fltk::ValueInput(225, 25, 65, 18, "Surf. Tension");
      o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
	  o->range(0,1);
      o->step(0.0001);
	  o->value(0.0005);
      o->callback((fltk::Callback*)cb_mFluidSurface_in);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
	{fltk::ValueInput* o = mFluidViscosity_in = new fltk::ValueInput(380, 25, 65, 18, "Lin. Viscos.");
      o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
	  o->range(0,10);
      o->step(0.1);
	  o->value(0.5);
      o->callback((fltk::Callback*)cb_mFluidViscosity_in);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
	{fltk::ValueInput* o = mFluidViscosity2_in = new fltk::ValueInput(560, 25, 65, 18, "Quad. Viscos.");
      o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
	  o->range(0,10);
      o->step(0.1);
	  o->value(1.0);
      o->callback((fltk::Callback*)cb_mFluidViscosity2_in);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
	
	{fltk::RadioButton* o = mFluid2D_radio = new fltk::RadioButton(160, 5, 32, 18, "2D");
	  o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
	  o->value(true);
	  o->callback((fltk::Callback*)cb_mFluid2D_radio);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
	{fltk::RadioButton* o = mFluid3D_radio = new fltk::RadioButton(200, 5, 32, 18, "3D");
	  o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
	  o->callback((fltk::Callback*)cb_mFluid3D_radio);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }



	{fltk::ValueSlider* o = mFountainHeight_sli = new fltk::ValueSlider(200, 5, 307, 18, "F. Height");
      o->type(fltk::ValueSlider::TICK_ABOVE);
	  o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
      o->range(2, 5);
      o->step(1);
	  o->value(3);
      o->callback((fltk::Callback*)cb_mFountainHeight_sli);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
	{fltk::ValueSlider* o = mFountainParticles_sli = new fltk::ValueSlider(200, 30, 307, 18, "Particles");
      o->type(fltk::ValueSlider::TICK_ABOVE);
	  o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
      o->range(200, 1000);
      o->step(1);
	  o->value(250);
      o->callback((fltk::Callback*)cb_mFountainParticles_sli);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
	{fltk::ValueSlider* o = mRopeParticles_sli = new fltk::ValueSlider(200, 30, 100, 18, "Particles");
      o->type(fltk::ValueSlider::TICK_ABOVE);
	  o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
      o->range(10, 50);
      o->step(10);
	  o->value(30);
      o->callback((fltk::Callback*)cb_mRopeParticles_sli);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }

	{fltk::ValueInput* o = mSpringK_in = new fltk::ValueInput(155, 5, 70, 18, "K");
      o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
	  o->range(0.0,100000.0);
      o->step(1000);
	  o->value(DataManager::mSpringK);
      o->callback((fltk::Callback*)cb_mSpringK_in);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
	{fltk::ValueInput* o = mSpringDamp_in = new fltk::ValueInput(290, 5, 70, 18, "K_d");
      o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
	  o->range(0.0,100000.0);
      o->step(1000);
	  o->value(DataManager::mSpringDamp);
      o->callback((fltk::Callback*)cb_mSpringDamp_in);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
	{fltk::ValueInput* o = mSpringBallRad_in = new fltk::ValueInput(430, 5, 70, 18, "Rad");
      o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
	  o->range(0.0,1);
      o->step(0.05);
	  o->value(DataManager::mSpringBallRadius);
      o->callback((fltk::Callback*)cb_mSpringBallRad_in);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }

	{fltk::RadioButton* o = mCube_radio = new fltk::RadioButton(177, 30, 32, 18, "Cube");
	  o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
	  o->value(true);
	  o->callback((fltk::Callback*)cb_mCube_radio);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
	{fltk::RadioButton* o = mBall_radio = new fltk::RadioButton(260, 30, 32, 18, "Sphere");
	  o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
	  o->callback((fltk::Callback*)cb_mBall_radio);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
	{fltk::CheckButton* o = mPartCollision_check = new fltk::CheckButton(485, 30, 24, 18, "Particle coll.");
	  o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
	  o->callback((fltk::Callback*)cb_mPartCollision_check);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
	{fltk::ValueInput* o = mRestitution_in = new fltk::ValueInput(540, 5, 80, 18, "kr");
      o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
	  o->range(0,2.0);
      o->step(0.01);
	  o->value(0.80);
      o->callback((fltk::Callback*)cb_mRestitution_in);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
	{fltk::ValueInput* o = mParticleRad_in = new fltk::ValueInput(540, 30, 80, 18, "eps");
      o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
	  o->range(0.005,0.05);
      o->step(0.001);
	  o->value(0.016);
      o->callback((fltk::Callback*)cb_mParticleRad_in);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
	{fltk::Button* o = mColor_but = new fltk::Button(300, 25, 64, 25, "Color");
      o->type(fltk::Button::TOGGLE);
      o->box(fltk::PLASTIC_UP_BOX);
      o->buttonbox(fltk::PLASTIC_UP_BOX);
      o->labelfont(fltk::HELVETICA_BOLD);
      o->color((fltk::Color)0xece9d800);
      o->selection_color((fltk::Color)0x8099ff00);
      o->selection_textcolor((fltk::Color)56);
      o->highlight_color((fltk::Color)0xece9d800);
      o->callback((fltk::Callback*)cb_mColor_but);
      o->tooltip("Snow/Color particle style");
    }
	{fltk::Button* o = mFixedCloth_but = new fltk::Button(320, 30, 64, 25, "Fixed");
      o->type(fltk::Button::TOGGLE);
      o->box(fltk::PLASTIC_UP_BOX);
      o->buttonbox(fltk::PLASTIC_UP_BOX);
      o->labelfont(fltk::HELVETICA_BOLD);
      o->color((fltk::Color)0xece9d800);
      o->selection_color((fltk::Color)0x8099ff00);
      o->selection_textcolor((fltk::Color)56);
      o->highlight_color((fltk::Color)0xece9d800);
      o->callback((fltk::Callback*)cb_mFixedCloth_but);
	  o->value(true);
      o->tooltip("Fix cloth on top");
    }
	{fltk::Button* o = mBending_but = new fltk::Button(400, 30, 64, 25, "Bending");
      o->type(fltk::Button::TOGGLE);
      o->box(fltk::PLASTIC_UP_BOX);
      o->buttonbox(fltk::PLASTIC_UP_BOX);
      o->labelfont(fltk::HELVETICA_BOLD);
      o->color((fltk::Color)0xece9d800);
      o->selection_color((fltk::Color)0x8099ff00);
      o->selection_textcolor((fltk::Color)56);
      o->highlight_color((fltk::Color)0xece9d800);
      o->callback((fltk::Callback*)cb_mBending_but);
	  o->value(true);
      o->tooltip("Use Provot's bending forces");
    }
	{fltk::ValueInput* o = mDamp_in = new fltk::ValueInput(190, 5, 80, 18, "kDamp");
      o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
	  o->range(0.0,10.0);
      o->step(0.1);
	  o->value(0.0);
      o->callback((fltk::Callback*)cb_mDamp_in);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
	{fltk::Button* o = mAddParticle_but = new fltk::Button(190, 25, 96, 25, "Add Particle");
      o->type(fltk::Button::TOGGLE);
      o->box(fltk::PLASTIC_UP_BOX);
      o->buttonbox(fltk::PLASTIC_UP_BOX);
      o->labelfont(fltk::HELVETICA_BOLD);
      o->color((fltk::Color)0xece9d800);
      o->selection_color((fltk::Color)0x8099ff00);
      o->selection_textcolor((fltk::Color)56);
      o->highlight_color((fltk::Color)0xece9d800);
      o->callback((fltk::Callback*)cb_mAddParticle_but);
      o->tooltip("Click to add particles");
    }
	{fltk::Button* o = mAddFixedDist_but = new fltk::Button(300, 25, 96, 25, "Fix distance");
      o->type(fltk::Button::TOGGLE);
      o->box(fltk::PLASTIC_UP_BOX);
      o->buttonbox(fltk::PLASTIC_UP_BOX);
      o->labelfont(fltk::HELVETICA_BOLD);
      o->color((fltk::Color)0xece9d800);
      o->selection_color((fltk::Color)0x8099ff00);
      o->selection_textcolor((fltk::Color)56);
      o->highlight_color((fltk::Color)0xece9d800);
	  o->callback((fltk::Callback*)cb_mAddFixedDist_but);
      o->tooltip("Click two particles to fix their distance");
    }



     {fltk::ValueSlider* o = mFrame_sli = new fltk::ValueSlider(47, 55, 460, 18, "Frame");
      o->type(fltk::ValueSlider::TICK_ABOVE);
      o->labelfont(fltk::HELVETICA_BOLD);
      o->labelsize(13);
      o->maximum(0);
      o->step(1);
      o->callback((fltk::Callback*)cb_mFrame_sli);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
     {fltk::ValueSlider* o = mBegin_sli = new fltk::ValueSlider(47, 75, 455, 18, "Begin");
      o->box(fltk::PLASTIC_UP_BOX);
      o->buttonbox(fltk::PLASTIC_UP_BOX);
      o->labelfont(fltk::HELVETICA_BOLD);
      o->color((fltk::Color)0xff6c5b00);
      o->labelsize(13);
      o->textsize(9);
      o->maximum(0);
      o->step(1);
      o->callback((fltk::Callback*)cb_mBegin_sli);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
     {fltk::ValueSlider* o = mEnd_sli = new fltk::ValueSlider(47, 95, 455, 18, "End");
      o->box(fltk::PLASTIC_UP_BOX);
      o->buttonbox(fltk::PLASTIC_UP_BOX);
      o->labelfont(fltk::HELVETICA_BOLD);
      o->color((fltk::Color)0x79ff8800);
      o->labelsize(13);
      o->textsize(9);
      o->maximum(0);
      o->step(1);
      o->callback((fltk::Callback*)cb_mEnd_sli);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
    }
     {fltk::Button* o = mLoop_but = new fltk::Button(509, 101, 55, 40, "LOOP");
      o->type(fltk::Button::TOGGLE);
      o->box(fltk::PLASTIC_UP_BOX);
      o->buttonbox(fltk::PLASTIC_UP_BOX);
      o->labelfont(fltk::HELVETICA_BOLD);
      o->color((fltk::Color)0xece9d800);
      o->selection_color((fltk::Color)0x8099ff00);
      o->selection_textcolor((fltk::Color)56);
      o->highlight_color((fltk::Color)0xece9d800);
      o->tooltip("Loop the playback");
    }
     {fltk::Button* o = mPlay_but = new fltk::Button(570, 101, 50, 40, "@>");
      o->type(fltk::Button::TOGGLE);
      o->box(fltk::PLASTIC_UP_BOX);
      o->buttonbox(fltk::PLASTIC_UP_BOX);
      o->labelfont(fltk::HELVETICA_BOLD);
      o->color((fltk::Color)0xece9d800);
      o->selection_color((fltk::Color)0xece9d800);
      o->selection_textcolor((fltk::Color)56);
      o->labelsize(20);
      o->callback((fltk::Callback*)cb_mPlay_but);
      o->tooltip("Play/Pause");
    }
     {fltk::ValueInput* o = mFrameStep_inp = new fltk::ValueInput(581, 71, 40, 28, "Step");
      o->box(fltk::PLASTIC_UP_BOX);
      o->buttonbox(fltk::PLASTIC_UP_BOX);
      o->minimum(1);
      o->maximum(100);
      o->step(1);
      o->value(1);
      o->when(fltk::WHEN_CHANGED);
	  o->callback((fltk::Callback*)cb_mFrameStep_inp);
      o->value(1);
    }
     {fltk::Button* o = mForward_but = new fltk::Button(590, 50, 30, 16, "@>");
      o->box(fltk::PLASTIC_UP_BOX);
      o->buttonbox(fltk::PLASTIC_UP_BOX);
      o->callback((fltk::Callback*)cb_mForward_but);
    }
     {fltk::Button* o = mBackward_but = new fltk::Button(558, 50, 31, 16, "@<");
      o->box(fltk::PLASTIC_UP_BOX);
      o->buttonbox(fltk::PLASTIC_UP_BOX);
      o->callback((fltk::Callback*)cb_mBackward_but);
    }
     {fltk::ValueSlider* o = mSpeed_rol = new fltk::ValueSlider(47, 115, 455, 18, "FPS");
      o->box(fltk::PLASTIC_UP_BOX);
      o->buttonbox(fltk::PLASTIC_UP_BOX);
      o->labelfont(fltk::HELVETICA_BOLD);
      o->color((fltk::Color)0x8099ff00);
      o->labelsize(13);
      o->minimum(5);
      o->maximum(150);
      o->step(1);
      o->value(120);
      o->align(fltk::ALIGN_LEFT);
      o->when(fltk::WHEN_CHANGED);
      o->tooltip("Adjust playback speed");
    }
    o->end();
    o->clear_border();
    o->resizable(o);
  }
  mPlaying=false;
}

void ControlPanel::advanceFrame(int _step) {
  int val = (int)mFrame_sli->value()+ _step;// (int)mFrameStep_inp->value();
  if( val >getEnd() ){
  	val = getBegin();
  	if( !isLooping() ){
  		mPlaying = false;
  		mPlay_but->label("@>");
  	}
  }
  mFrame_sli->value( val );
  //mFrameCounter_inp->value( val );
}

void ControlPanel::decrementFrame(int _step) {
  int val = (int)mFrame_sli->value() - _step;//(int)mFrameStep_inp->value();
  if( val < getBegin() ){
  	val = getBegin();
  	if( !isLooping() ){
  		mPlaying = false;
  		mPlay_but->label("@>");
  	}
  }
  mFrame_sli->value( val );
  //mFrameCounter_inp->value( val );
}

int ControlPanel::getCurrentFrame() {
  return (int)mFrame_sli->value();
}

void ControlPanel::setCurrentFrame(int _f) {
  if( _f>getEnd() ){
  		_f = getBegin();
  		if( !isLooping() ){
  			mPlaying = false;
  			mPlay_but->label("@>");
  		}
  	}
  	mFrame_sli->value( _f );
  	//mFrameCounter_inp->value( val );
}

int ControlPanel::getMaxFrame() {
  return (int)mFrame_sli->maximum();
}

int ControlPanel::getBegin() {
  return (int)mBegin_sli->value();
}

int ControlPanel::getEnd() {
  return (int)mEnd_sli->value();
}

double ControlPanel::getSpeed() {
  return (double)1.0/mSpeed_rol->value();
}

bool ControlPanel::isLooping() {
  if((int)mLoop_but->value()==1) return true; 
  else return false;
}

bool ControlPanel::isPlaying() {
  return mPlaying;
}
