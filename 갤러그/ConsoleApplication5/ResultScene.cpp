#include "ResultScene.h"
#include "DrawManager.h"
#include "CustomStr.h"
#include "TableManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
ResultScene::ResultScene()
{
	
}


ResultScene::~ResultScene()
{

}

void ResultScene::Enter()
{
	curframe = 0;
	ResultCursor = 0;
	auto pStageInfo = SceneManager::GetInstance()->GetStageInfo();
	if (pStageInfo != nullptr)
	{
		curStage = pStageInfo->curStage;
		result = pStageInfo->type;
	}

}

void ResultScene::Updata()
{
	char str[20];
	//실패하면 재도전을 성공하면 다음스테이지를 하게해줌 
	if (result == ResultType::Lose)
	{
		custom_strcpy(str, "Try Again");
	}
	else
	{
		if (curStage == MaxStage - 1)
			custom_strcpy(str, "Try Again");   //최대 스테이지면 이겨도 다음스테이지가아니라  재도전
		else
			custom_strcpy(str, "Next Stage");
	}

	KeyMessage keyData;
	//최대 스테이지면 다음스테이지 못고르게함 
	if (KeyManager::GetInstance()->DeQueue(&keyData))
	{

		if (ResultCursor + keyData.y >= 0 && ResultCursor + keyData.y <= 1)
			ResultCursor += keyData.y;
		if (keyData.c == 'r')
		{
			// 씬전환
			if (ResultCursor == 0)
			{
				SceneManager::GetInstance()->ChangeScene(SceneType::Title);

				return;
			}
			if (result == ResultType::Win)
			{
				curStage++;
				if (curStage >= MaxStage)
					curStage = MaxStage - 1;
			}
			SceneManager::GetInstance()->ChangeScene(SceneType::Load);
			return;
		}

	}

	
	int cursor = ResultCursor * 2;
	// 스크린 버퍼를 지움
	DrawManager::GetInstance()->Buffer_Clear();
	DrawManager::GetInstance()->Buffer_LineSet(10 + cursor, 26, ">>>");
	DrawManager::GetInstance()->Buffer_LineSet(10, 30, "Go Title");
	DrawManager::GetInstance()->Buffer_LineSet(12, 30, str);

	// 스크린 버퍼를 화면으로 출력
	DrawManager::GetInstance()->Buffer_Flip();
	curframe++;
}

void ResultScene::Exit()
{
	SceneManager::GetInstance()->SetStage(curStage);
	SceneManager::GetInstance()->SetReult(ResultType::None);
}
