#pragma once
#ifndef __SCENEMANAGER__
#define __SCENEMANAGER__
#include "BaseScene.h"
#include "MyDefine.h"

class SceneManager
{
private :
	SceneManager();
	~SceneManager();
	static SceneManager* minstance;

public:
	static SceneManager* GetInstance();

	bool Init();

	void UpdataScene();
	void ChangeScene(SceneType::Type sceneType);

	void SetStage(int stage);
	void SetReult(ResultType::Type type);
	StageInfo* GetStageInfo();
	
private:

	StageInfo mStageInfo;

	SceneType::Type mCurSceneType;
	BaseScene* mCurScene;
	BaseScene* mSceneList[SceneType::Max];
};


#endif