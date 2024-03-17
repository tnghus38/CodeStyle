#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include "Console.h"
#include "CustomStr.h"
#include "CList.h"
#include "DrawManager.h"
#include "TableManager.h"
#include "ObjectManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "MyNew.h"
//#include "Profiling.h"

void main(void)
{
	cs_Initial();
	TableManager::GetInstance()->Init();
	SceneManager::GetInstance()->Init();

	SceneManager::GetInstance()->ChangeScene(SceneType::Title);
	while (1)
	{

		KeyManager::GetInstance()->GetKey();
		SceneManager::GetInstance()->UpdataScene();
		Sleep(100);

	}
}








