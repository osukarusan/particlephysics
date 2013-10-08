#ifdef WIN32
#include <windows.h>
#endif
#include <string>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <fltk/visual.h>

#include "WindowGLDisplay.h"
#include "ControlPanel.h"
#include "DataManager.h"

using namespace std;


void onTimer(void *){

	double howFast=0.07;

	if( DataManager::mUI->mControl->isPlaying()){
		recordFrames();
		DataManager::mUI->mControl->advanceFrame();
	}

	if (DataManager::gReset == true)
	{
		DataManager::mUI->mControl->setScene(DataManager::gCurrentScene);
		if (DataManager::gLastScene != DataManager::gCurrentScene) {
			DataManager::mUI->mGLWindow->resetCameraPosition();
			DataManager::mInitExtraParticles.clear();
			DataManager::mInitFixDistConstraints.clear();
			DataManager::gLastScene = DataManager::gCurrentScene;
		}
		DataManager::mParticles.clear();
		DataManager::mCenter.clear();
		DataManager::mUI->mControl->setRange(0);
		switch (DataManager::gCurrentScene) {
			case SCENE_GALILEO:
				DataManager::mSceneGalileo->init();  
				break;
			case SCENE_SNOW: 
				DataManager::mSceneSnow->init(DataManager::mNumParticles,  
					                          DataManager::mSnowVolume == 0); 
				break;
			case SCENE_FOUNTAIN:
				DataManager::mSceneFountain->init(DataManager::mFountainParticles);
				break;
			case SCENE_TINKERTOY:
				DataManager::mSceneTinkertoy->init();
				break;
			default: break;
		}
		DataManager::gReset = false;
		DataManager::mUI->Show();
	}

	if(DataManager::mUI->mSim_but->value()){
		// ---------  begin simulation code-------------------
		switch (DataManager::gCurrentScene)
		{
		case SCENE_GALILEO:		DataManager::mSceneGalileo->update();	break;
		case SCENE_SNOW:		DataManager::mSceneSnow->update();		break;
		case SCENE_FOUNTAIN:	DataManager::mSceneFountain->update();	break;
		case SCENE_TINKERTOY:	DataManager::mSceneTinkertoy->update(); break;
		}
		// ---------  end simulation code-------------------
	}

	howFast = DataManager::mUI->mControl->getSpeed();
	DataManager::mUI->mGLWindow->refresh();
	fltk::add_timeout( howFast, onTimer );
}

int main(int argc, char ** argv){
	// inits
	// ---------------------------------------------
	DataManager::mUI = new ParticleSystemUI;
	DataManager::mSceneGalileo = new SceneGalileo();
	DataManager::mSceneSnow = new SceneSnow();
	DataManager::mSceneFountain = new SceneFountain();
	DataManager::mSceneTinkertoy = new SceneTinkertoy();
	// ---------------------------------------------

	DataManager::mSceneGalileo->init();
	DataManager::mUI->mControl->setScene(SCENE_GALILEO);
	
	// show UI
	fltk::visual(fltk::DOUBLE_BUFFER|fltk::INDEXED_COLOR);
	DataManager::mUI->Show();
	fltk::add_timeout( 0.07, onTimer );
	return fltk::run();
}
