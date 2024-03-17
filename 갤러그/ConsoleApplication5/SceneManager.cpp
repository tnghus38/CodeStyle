#include"SceneManager.h"
#include "TitleScene.h"
#include "LoadScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "KeyManager.h"
#include "ObjectManager.h"
#include "MyNew.h"

SceneManager* SceneManager::minstance = nullptr;
SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{

}

SceneManager* SceneManager::GetInstance()
{
	if (minstance == nullptr)
		minstance = new SceneManager();
	return minstance;
}

bool SceneManager::Init()
{
	mSceneList[SceneType::Title] = new TitleScene();
	mSceneList[SceneType::Load] = new LoadScene();
	mSceneList[SceneType::Game] = new GameScene();
	mSceneList[SceneType::Result] = new ResultScene();
	mSceneList[SceneType::NoneScene] = nullptr;

	mCurScene = mSceneList[SceneType::Title];
	mCurSceneType = SceneType::Title;
	return true;
}

void SceneManager::UpdataScene()
{
	if (mCurScene != nullptr)
	{
		mCurScene->Updata();
	}
}

void SceneManager::ChangeScene(SceneType::Type sceneType)
{
	if (SceneType::IsValid(sceneType) == false)
		return;

	int Result = 0;

	if (mCurScene != nullptr)
		mCurScene->Exit();

	mCurScene = mSceneList[sceneType];

	if(mCurScene !=nullptr)
		mCurScene->Enter();

	mCurSceneType = sceneType;
}

void SceneManager::SetStage(int stage)
{
	mStageInfo.curStage = stage;
}

void SceneManager::SetReult(ResultType::Type type)
{
	mStageInfo.type = type;
}

StageInfo* SceneManager::GetStageInfo()
{
	return &mStageInfo;
}
