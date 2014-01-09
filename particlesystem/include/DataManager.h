#ifndef _DATA_MANAGER_
#define _DATA_MANAGER_

#include <vector>
#include <utility>
#include "ParticleSystemUI.h"
#include "SceneGalileo.h"
#include "SceneSnow.h"
#include "SceneFountain.h"
#include "SceneTinkertoy.h"
#include "SceneRope.h"
#include "SceneCloth.h"
#include "SceneFluid.h"


enum SceneType { SCENE_FLUID,	SCENE_CLOTH,	SCENE_ROPE,			SCENE_FOUNTAIN,		
				 SCENE_GALILEO,	SCENE_SNOW,		SCENE_TINKERTOY,	NUM_SCENES };


class DataManager{

public:

	static ParticleSystemUI* mUI;

	static SceneType gCurrentScene;
	static SceneType gLastScene;
	static bool		 gReset;


	// General constants
	static double mTimeStep;
	static double mGravityValue;
	static double mCoeffRestitution;
	static double mTangentialFriction;
	static double mCollisionEpsilon;
	static int	  mFrameSkip;

	// Galileo's experiment
	static double mInitialHeight;

	// Snow cube / ball
	static int	  mNumParticles;
	static int	  mSnowVolume;
	static bool   mParticleColl;
	static bool	  mColorParticles;
	static Vec3d  mVolumeCenter;

	// Fountain
	static int	  mFountainParticles;
	static double mFountainHeight;
	static Vec3d  mBallCenter;

	// Rope and Cloth
	static int    mRopeParticles;
	static double mSpringK;
	static double mSpringDamp;
	static Vec3d  mSpringBall;
	static double mSpringBallRadius;
	static bool	  mBendingCloth;
	static bool   mFixedCloth;

	// Fluid
	static bool	  mFluid3D;
	static double mFluidRestDensity;
	static double mFluidSurfaceTension;
	static double mFluidLinearViscosity;
	static double mFluidQuadraticViscosity;

	// Tinkertoy
	static Vec3d  mCircleWireCenter;
	static double mCircleWireRadius;
	static int	  mSelectedParticle;
	static double mDampCoeff;
	static double mMouseCoeff;
	static Vec3d  mMouse3Dpos;
	static int	  mMouseTool;
	static std::vector<Vec3d>                mInitExtraParticles;
	static std::vector<std::pair<int, int> > mInitFixDistConstraints;

	enum MouseTools { MT_NONE, MT_ADD_PARTICLE, MT_FIXED_DIST };

	
	static SceneGalileo*	mSceneGalileo;
	static SceneSnow*		mSceneSnow;
	static SceneFountain*	mSceneFountain;
	static SceneTinkertoy*	mSceneTinkertoy;
	static SceneRope*		mSceneRope;
	static SceneCloth*		mSceneCloth;
	static SceneFluid*		mSceneFluid;

	static std::vector<std::vector<Particle> > mParticles;
	static std::vector<Vec3d> mCenter;

};

#endif