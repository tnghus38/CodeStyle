#include "LoadScene.h"
#include "DrawManager.h"
#include "TableManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
LoadScene::LoadScene()
{
	
}

LoadScene::~LoadScene()
{

}

void LoadScene::Enter()
{
	curframe = 0;

	auto pStageInfo = SceneManager::GetInstance()->GetStageInfo();
	if (pStageInfo != nullptr)
	{
		curStage = pStageInfo->curStage;
	}
}

void LoadScene::Updata()
{

	//그냥 연출 
	_Show();

	//실제 브젝트 생성 
	if (curframe > 25)
	{
		ObjectManager::GetInstance()->ClearList();
		ObjectManager::GetInstance()->CreateObject(40, 20, const_cast<char*>("A"), ObjectType::Player);

		auto pStageTable = TableManager::GetInstance()->GetStageSetData(curStage);
		if (pStageTable != nullptr)
		{
			for (CList<SpawnData*>::iterator tmp = pStageTable->SpawnList.begin(); tmp != pStageTable->SpawnList.end(); ++tmp)
			{
				ObjectManager::GetInstance()->CreateObject((*tmp)->X, (*tmp)->Y, (*tmp)->MobID, ObjectType::Mob);
			}

		}

		//씬전환
		SceneManager::GetInstance()->ChangeScene(SceneType::Game);
	}


	curframe++;
}

void LoadScene::Exit()
{
}

void LoadScene::_Show()
{
	// 스크린 버퍼를 지움
	DrawManager::GetInstance()->Buffer_Clear();
	if (curframe < 5)
	{
		DrawManager::GetInstance()->Buffer_LineSet(8, 33, "TanTable   Load....");
		DrawManager::GetInstance()->Buffer_LineSet(10, 33, "StageTable   Load....");
		DrawManager::GetInstance()->Buffer_LineSet(12, 33, "MobTable   Load....");
		DrawManager::GetInstance()->Buffer_LineSet(14, 33, "MoveTable   Load....");
	}
	else if (curframe < 10)
	{

		DrawManager::GetInstance()->Buffer_LineSet(8, 33, "TanTable   Success!");
		DrawManager::GetInstance()->Buffer_LineSet(10, 33, "StageTable   Load....");
		DrawManager::GetInstance()->Buffer_LineSet(12, 33, "MobTable   Load....");
		DrawManager::GetInstance()->Buffer_LineSet(14, 33, "MoveTable   Load....");
	}
	else if (curframe < 15)
	{

		DrawManager::GetInstance()->Buffer_LineSet(8, 33, "TanTable   Success!");
		DrawManager::GetInstance()->Buffer_LineSet(10, 33, "StageTable   Success!");
		DrawManager::GetInstance()->Buffer_LineSet(12, 33, "MobTable   Load....");
		DrawManager::GetInstance()->Buffer_LineSet(14, 33, "MoveTable   Load....");
	}
	else if (curframe < 20)
	{

		DrawManager::GetInstance()->Buffer_LineSet(8, 33, "TanTable   Success!");
		DrawManager::GetInstance()->Buffer_LineSet(10, 33, "StageTable   Success!");
		DrawManager::GetInstance()->Buffer_LineSet(12, 33, "MobTable   Success!");
		DrawManager::GetInstance()->Buffer_LineSet(14, 33, "MoveTable   Load....");
	}
	else
	{
		DrawManager::GetInstance()->Buffer_LineSet(8, 33, "TanTable   Success!");
		DrawManager::GetInstance()->Buffer_LineSet(10, 33, "StageTable   Success!");
		DrawManager::GetInstance()->Buffer_LineSet(12, 33, "MobTable   Success!");
		DrawManager::GetInstance()->Buffer_LineSet(14, 33, "MoveTable   Success!");
	}

	if (curframe > 20)
		DrawManager::GetInstance()->Buffer_LineSet(16, 33, "MapSetting...");

	// 스크린 버퍼를 화면으로 출력
	DrawManager::GetInstance()->Buffer_Flip();
}
