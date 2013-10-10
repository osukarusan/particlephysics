#include "DataManager.h"

ParticleSystemUI* DataManager::mUI   = NULL;

SceneType DataManager::gCurrentScene = SCENE_GALILEO;
SceneType DataManager::gLastScene    = SCENE_GALILEO;
bool	  DataManager::gReset		 = true;

double DataManager::mTimeStep           = 0.01;
double DataManager::mGravityValue       = 9.81;
double DataManager::mCoeffRestitution   = 0.8;
double DataManager::mTangentialFriction = 0.8;
double DataManager::mCollisionEpsilon   = 0.016;

double DataManager::mInitialHeight = 80.0;

int	   DataManager::mNumParticles   = 50;
int    DataManager::mSnowVolume     = 0;
bool   DataManager::mParticleColl   = false;
bool   DataManager::mColorParticles = false;

int	   DataManager::mFountainParticles = 250;
double DataManager::mFountainHeight    = 3.0f;
Vec3d  DataManager::mBallCenter		   = Vec3d(0, 0.5, 0);

int	   DataManager::mRopeParticles = 30;
double DataManager::mSpringK       = 10000.0f;
double DataManager::mSpringDamp    = 10.0f;
Vec3d  DataManager::mSpringBall	   = Vec3d(0.5, 1.5, 0);

Vec3d  DataManager::mCircleWireCenter = Vec3d(0,0,0);
double DataManager::mCircleWireRadius = 1.0;
Vec3d  DataManager::mMouse3Dpos = Vec3d(0,0,0);
int	   DataManager::mMouseTool  = DataManager::MT_NONE;
std::vector<Vec3d>                DataManager::mInitExtraParticles = std::vector<Vec3d>();
std::vector<std::pair<int, int> > DataManager::mInitFixDistConstraints = std::vector<std::pair<int, int> >();

int	   DataManager::mSelectedParticle = -1;
double DataManager::mDampCoeff  = 0.0;
double DataManager::mMouseCoeff = 10.0;

SceneGalileo*	DataManager::mSceneGalileo = NULL;
SceneSnow*		DataManager::mSceneSnow = NULL;
SceneFountain*	DataManager::mSceneFountain = NULL;
SceneTinkertoy*	DataManager::mSceneTinkertoy = NULL;
SceneRope*		DataManager::mSceneRope = NULL;
SceneCloth*		DataManager::mSceneCloth = NULL;

Vec3d  DataManager::mVolumeCenter = Vec3d(0,0,0);

std::vector<std::vector<Particle> > DataManager::mParticles;
std::vector<Vec3d> DataManager::mCenter;