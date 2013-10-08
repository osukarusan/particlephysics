#include "UICallback.h"
#include "ControlPanel.h"
#include "WindowGLDisplay.h"
#include "glFuncs.h"
#include "DataManager.h"
#include "ParticleSystemUI.h"

#include <vector>
#include <fltk/file_chooser.h>

using namespace std;

void Exit_cb(fltk::Widget *o, void *v)
{
	exit(0);
}

void StillShot_cb(fltk::Widget *o, void *v)
{
	// take a still shot
	static int count=0;
	char fileBase[32]="ScreenShot";
	char fileName[64];
	sprintf(fileName, "%s%.4d.tga", fileBase, count++); 
	ScreenShot(DataManager::mUI->mGLWindow->w(), DataManager::mUI->mGLWindow->h(), fileName);
}

void recordFrames(){
	// saving the dofs
	if(DataManager::mUI->mSim_but->value()){

	}

	// saving the images
	if(DataManager::mUI->mRecordMotion_but->value() && (DataManager::mUI->mSim_but->value() || DataManager::mUI->mControl->isPlaying())){
		static int count=0;
		char fileBase[32]="Capture";
		char fileName[64];
		sprintf(fileName, "%s%.4d.tga", fileBase, count++); 
		ScreenShot(DataManager::mUI->mGLWindow->w(), DataManager::mUI->mGLWindow->h(), fileName, DataManager::mUI->mGLWindow->mAntiAlias);
	}
}

void Sim_cb(fltk::Widget *o, void *v){
	if(DataManager::mUI->mSim_but->value()){
		DataManager::mUI->mControlGrp->deactivate();
	}
	else {
		DataManager::mUI->mControlGrp->activate();
		int numFrames = DataManager::mParticles.size();
		DataManager::mUI->mControl->setRange(numFrames-1);
	}
}

void Switch_cb(fltk::Widget *o, void *v){
	DataManager::gCurrentScene = SceneType((int(DataManager::gCurrentScene) + 1)%NUM_SCENES);
	DataManager::gReset = true;
}
