// generated by Fast Light User Interface Designer (fluid) version 2.1000

#ifndef ControlPanel_h
#define ControlPanel_h
#include <fltk/DoubleBufferWindow.h>
#include <fltk/ValueSlider.h>
#include <fltk/Button.h>
#include <fltk/ValueInput.h>
#include <fltk/CheckButton.h>
#include <fltk/RadioButton.h>
#include "DataManager.h"


class ControlPanel  {
public:
  void setRange(int _maxFrame);
  ControlPanel();
  fltk::DoubleBufferWindow *mControlWindow;

public:
	fltk::ValueInput *mGravity_in;
private:
	inline void cb_mGravity_in_i(fltk::ValueInput*,void*);
	static void cb_mGravity_in(fltk::ValueInput*,void*);

public:
	fltk::ValueInput *mStep_in;
private:
	inline void cb_mStep_in_i(fltk::ValueInput*,void*);
	static void cb_mStep_in(fltk::ValueInput*,void*);

public:
	fltk::ValueSlider *mHeight_sli;
private:
	inline void cb_mHeight_sli_i(fltk::ValueSlider*,void*);
	static void cb_mHeight_sli(fltk::ValueSlider*,void*);

public:
	fltk::ValueSlider *mFountainHeight_sli;
private:
	inline void cb_mFountainHeight_sli_i(fltk::ValueSlider*,void*);
	static void cb_mFountainHeight_sli(fltk::ValueSlider*,void*);

public:
	fltk::ValueSlider *mParticles_sli;
private:
	inline void cb_mParticles_sli_i(fltk::ValueSlider*,void*);
	static void cb_mParticles_sli(fltk::ValueSlider*,void*);
	
public:
	fltk::ValueSlider *mFountainParticles_sli;
private:
	inline void cb_mFountainParticles_sli_i(fltk::ValueSlider*,void*);
	static void cb_mFountainParticles_sli(fltk::ValueSlider*,void*);

public:
	fltk::ValueSlider *mRopeParticles_sli;
private:
	inline void cb_mRopeParticles_sli_i(fltk::ValueSlider*,void*);
	static void cb_mRopeParticles_sli(fltk::ValueSlider*,void*);

public:
	fltk::CheckButton *mPartCollision_check;
private:
	inline void cb_mPartCollision_check_i(fltk::CheckButton*,void*);
	static void cb_mPartCollision_check(fltk::CheckButton*,void*);

public:
	fltk::RadioButton *mCube_radio, *mBall_radio;
private:
	inline void cb_mCube_radio_i(fltk::RadioButton*,void*);
	static void cb_mCube_radio(fltk::RadioButton*,void*);
	inline void cb_mBall_radio_i(fltk::RadioButton*,void*);
	static void cb_mBall_radio(fltk::RadioButton*,void*);

public:
	fltk::ValueInput *mRestitution_in;
private:
	inline void cb_mRestitution_in_i(fltk::ValueInput*,void*);
	static void cb_mRestitution_in(fltk::ValueInput*,void*);

public:
	fltk::ValueInput *mParticleRad_in;
private:
	inline void cb_mParticleRad_in_i(fltk::ValueInput*,void*);
	static void cb_mParticleRad_in(fltk::ValueInput*,void*);

public:
	fltk::Button *mColor_but;
private:
    inline void cb_mColor_but_i(fltk::Button*, void*);
    static void cb_mColor_but(fltk::Button*, void*);

public:
	fltk::Button *mFixedCloth_but;
private:
    inline void cb_mFixedCloth_but_i(fltk::Button*, void*);
    static void cb_mFixedCloth_but(fltk::Button*, void*);

public:
	fltk::Button *mBending_but;
private:
    inline void cb_mBending_but_i(fltk::Button*, void*);
    static void cb_mBending_but(fltk::Button*, void*);

public:
	fltk::ValueInput *mDamp_in;
private:
	inline void cb_mDamp_in_i(fltk::ValueInput*,void*);
	static void cb_mDamp_in(fltk::ValueInput*,void*);

public:
	fltk::ValueInput *mSpringK_in;
private:
	inline void cb_mSpringK_in_i(fltk::ValueInput*,void*);
	static void cb_mSpringK_in(fltk::ValueInput*,void*);

public:
	fltk::ValueInput *mSpringDamp_in;
private:
	inline void cb_mSpringDamp_in_i(fltk::ValueInput*,void*);
	static void cb_mSpringDamp_in(fltk::ValueInput*,void*);

public:
	fltk::ValueInput *mSpringBallRad_in;
private:
	inline void cb_mSpringBallRad_in_i(fltk::ValueInput*,void*);
	static void cb_mSpringBallRad_in(fltk::ValueInput*,void*);

public:
	fltk::Button *mAddParticle_but;
private:
    inline void cb_mAddParticle_but_i(fltk::Button*, void*);
    static void cb_mAddParticle_but(fltk::Button*, void*);

public:
	fltk::Button *mAddFixedDist_but;
private:
    inline void cb_mAddFixedDist_but_i(fltk::Button*, void*);
    static void cb_mAddFixedDist_but(fltk::Button*, void*);


public:
    fltk::ValueSlider *mFrame_sli;
private:
    inline void cb_mFrame_sli_i(fltk::ValueSlider*, void*);
    static void cb_mFrame_sli(fltk::ValueSlider*, void*);
public:
    fltk::ValueSlider *mBegin_sli;
private:
    inline void cb_mBegin_sli_i(fltk::ValueSlider*, void*);
    static void cb_mBegin_sli(fltk::ValueSlider*, void*);
public:
    fltk::ValueSlider *mEnd_sli;
private:
    inline void cb_mEnd_sli_i(fltk::ValueSlider*, void*);
    static void cb_mEnd_sli(fltk::ValueSlider*, void*);
public:
    fltk::Button *mLoop_but;
    fltk::Button *mPlay_but;
private:
    inline void cb_mPlay_but_i(fltk::Button*, void*);
    static void cb_mPlay_but(fltk::Button*, void*);
public:
    fltk::ValueInput *mFrameStep_inp;
private:
    inline void cb_mFrameStep_inp_i(fltk::ValueInput*, void*);
    static void cb_mFrameStep_inp(fltk::ValueInput*, void*);
public:
    fltk::Button *mForward_but;
private:
    inline void cb_mForward_but_i(fltk::Button*, void*);
    static void cb_mForward_but(fltk::Button*, void*);
public:
    fltk::Button *mBackward_but;
private:
    inline void cb_mBackward_but_i(fltk::Button*, void*);
    static void cb_mBackward_but(fltk::Button*, void*);
public:
    fltk::ValueSlider *mSpeed_rol;
  void advanceFrame(int _step=1);
  void decrementFrame(int _step=1);
  int getCurrentFrame();
  void setCurrentFrame(int _f);
  int getMaxFrame();
  int getBegin();
  int getEnd();
  double getSpeed();
  bool isLooping();
  bool isPlaying();
  void setScene(SceneType scene);
private:
  bool mPlaying;
};
#endif
