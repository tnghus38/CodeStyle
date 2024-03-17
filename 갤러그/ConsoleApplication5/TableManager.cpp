#define _CRT_SECURE_NO_WARNINGS
#include "TableManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "CustomStr.h"
#include "MyNew.h"

TableManager* TableManager::minstance = nullptr;

TableManager::TableManager()
{
}

TableManager::~TableManager()
{
}
TableManager* TableManager::GetInstance()
{
	if (minstance == nullptr)
		minstance = new TableManager();
	return minstance;
}

bool TableManager::Init()
{
	if (_MobTableLoad() == false)
	{
		printf("\n MobTable Error \n");
		return false;
	}
	if (_StageTableLoad() == false)
	{
		printf("\n StageTable Error \n");
		return false;
	}
	if (_TanTableLoad() == false)
	{
		printf("\n TanTable Error \n");
		return false;
	}
	if (_MoveTableLoad() == false)
	{
		printf("\n MoveTable Error \n");
		return false;
	}
	return true;
}

MobData* TableManager::GetMobData(char* id)
{
	if (mMobTable.ContainsKey(id) == false)
	{
		return nullptr;
	}

	return mMobTable[id];
}

MoveData* TableManager::GetMovetable(char* id)
{
	if (mMovetable.ContainsKey(id) == false)
	{
		return nullptr;
	}
	return mMovetable[id];
}

Tandata* TableManager::GetTanData(char* id)
{
	if (mTanTable.ContainsKey(id) == false)
	{
		return nullptr;
	}
	return mTanTable[id];
}

StageSetData* TableManager::GetStageSetData(int stage)
{
	char* id = (char*)&stage;
	if (mStageTable.ContainsKey(id) == false)
	{
		return nullptr;
	}
	return mStageTable[id];
}

bool TableManager::_MobTableLoad()
{
	FILE* pFile;

	pFile = fopen("MobTable.txt", "r+b");

	if (pFile == NULL)
	{
		printf("MobTable 파일을 열 수 없습니다");
		return false;
	}

	while (1)
	{
		MobData* mob = new MobData();
		int ret = fscanf(pFile, "MobID:%s TanType:%s AttDelay:%d MaxHP:%d StartDelay:%d MoveID:%s\n", &mob->MobID, &mob->TanType, &mob->AttDelay, &mob->MaxHP, &mob->StartDelay, &mob->MoveID);
		if (ret == EOF)
		{
			delete mob;
			break;
		}
		mMobTable.Add(mob->MobID, mob);

	}

	fclose(pFile);
	return true;
}

bool TableManager::_StageTableLoad()
{
	FILE* pFile;

	pFile = fopen("StageTable.txt", "r+b");

	if (pFile == NULL)
	{
		printf("StageTable 파일을 열 수 없습니다");
		return false;
	}

	while (1)
	{
		int stageNum;
		SpawnData* spawn = new SpawnData;
		int ret = fscanf(pFile, "Stage:%d MobID:%s StartX:%d StartY:%d\n", &stageNum, &spawn->MobID, &spawn->X, &spawn->Y );
		if (ret == EOF)
		{
			delete spawn;
			break;
		}

		char* key = (char*)&stageNum;
		if (mStageTable.ContainsKey(key) == false)
		{
			StageSetData* tmp = new StageSetData();
			mStageTable.Add(key, tmp);
		}

		mStageTable[key]->StageNum = stageNum;
		mStageTable[key]->SpawnList.push_back(spawn);
	}

	fclose(pFile);
	return true;
}

bool TableManager::_TanTableLoad()
{
	FILE* pFile;

	pFile = fopen("TanTable.txt", "r+b");

	if (pFile == NULL)
	{
		printf("TanTable 파일을 열 수 없습니다");
		return false;
	}

	while (1)
	{
		Tandata* tan = new Tandata();
		int ret = fscanf(pFile, "TanID:%s MoveType:%s Damage:%d\n", &tan->TanID, &tan->MoveType, &tan->Damage);
		if (ret == EOF)
		{
			delete tan;
			break;
		}
		mTanTable.Add(tan->TanID, tan);
	}
	fclose(pFile);
	return true;

}
bool TableManager::_MoveTableLoad()
{
	FILE* pFile;

	pFile = fopen("MoveTable.txt", "r+b");

	if (pFile == NULL)
	{
		printf("MoveTable 파일을 열 수 없습니다");
		return false;
	}

	while (1)
	{
		MoveData* move = new MoveData();
		int ret = fscanf(pFile, "MoveID:%s MoveSize%d\n", &move->MoveId, &move->MoveSize);
		if (ret == EOF)
		{
			delete move;
			break;
		}
		for (int i = 0; i < 10; i++)
		{
			int ret = fscanf(pFile, "X:%d Y:%d\n", &move->mX[i], &move->mY[i]);
			if (ret == EOF)
				return false;
		}
		mMovetable.Add(move->MoveId, move);
	}

	fclose(pFile);
	return true;
}