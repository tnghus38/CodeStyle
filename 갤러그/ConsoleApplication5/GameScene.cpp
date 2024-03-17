#include "GameScene.h"
#include "DrawManager.h"
#include "ObjectManager.h"
GameScene::GameScene()
{
	curframe = 0;
}

GameScene::~GameScene()
{

}

void GameScene::Enter()
{
}

void GameScene::Updata()
{
	// 스크린 버퍼를 지움
	DrawManager::GetInstance()->Buffer_Clear();


	ObjectManager::GetInstance()->Update(curframe);
	ObjectManager::GetInstance()->Render();


	DrawManager::GetInstance()->Buffer_Flip();
	curframe++;
}

void GameScene::Exit()
{
}
