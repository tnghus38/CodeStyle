#include "TitleScene.h"
#include "DrawManager.h"
#include "KeyManager.h"
#include "TableManager.h"
#include "SceneManager.h"
TitleScene::TitleScene()
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::Enter()
{
	curframe = 0;
	curStage = 0;
}

void TitleScene::Updata()
{
	// 스크린 버퍼를 지움
	DrawManager::GetInstance()->Buffer_Clear();

	KeyMessage keyData;
	if (KeyManager::GetInstance()->DeQueue(&keyData))
	{
		if(curStage+keyData.y >=0 && curStage + keyData.y <MaxStage)
			curStage += keyData.y;
		
		if (keyData.c == 'r')
		{
			// 씬전환
			SceneManager::GetInstance()->ChangeScene(SceneType::Load);
		}

	}
	
	int cursor = curStage * 2;
	DrawManager::GetInstance()->Buffer_LineSet(10 + cursor, 26, ">>> ");
	DrawManager::GetInstance()->Buffer_LineSet(10, 30, "1_stage");
	DrawManager::GetInstance()->Buffer_LineSet(12, 30, "2_stage");
	DrawManager::GetInstance()->Buffer_LineSet(14, 30, "3_stage");

	// 스크린 버퍼를 화면으로 출력
	DrawManager::GetInstance()->Buffer_Flip();
	curframe++;
}

void TitleScene::Exit()
{
	SceneManager::GetInstance()->SetReult(ResultType::None);
	SceneManager::GetInstance()->SetStage(curStage);
}
