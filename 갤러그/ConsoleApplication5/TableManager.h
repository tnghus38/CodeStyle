#pragma once
#ifndef __TABLEMANAGER__
#define __TABLEMANAGER__

#include "MyDefine.h"
#include "HashTable.h"
#include "CList.h"


//테이블 데이터 
struct MoveData //몹이나 탄 이동 테이블 데이터 
{
	char MoveId[2];
	int mX[10];
	int mY[10];
	int MoveSize;
};
struct SpawnData //스테이지 스폰정보
{
	char MobID[2];
	int X = 0;
	int Y = 0;
};
struct StageSetData //스테이지 데이터
{
	int StageNum;
	CList<SpawnData*> SpawnList;
};

struct MobData   /// 몹 데이터
{
	char MobID[2]; // Y T M
	int MaxHP;
	int AttDelay;
	char TanType[2];
	int StartDelay;
	char MoveID[2];
};

struct Tandata // 총알 데이터 
{
	char TanID[2]; //탄모양 
	int Damage;//데미지

	char MoveType[2];
};



class TableManager
{
private:
	TableManager();
	~TableManager();
	static TableManager* minstance;

public:
	static TableManager* GetInstance();
	bool Init();

	MobData* GetMobData(char* id);
	MoveData* GetMovetable(char* id);
	Tandata* GetTanData(char* id);
	StageSetData* GetStageSetData(int stage);

private:
	//테이블 로드 
	bool _MobTableLoad();
	bool _StageTableLoad();
	bool _TanTableLoad();
	bool _MoveTableLoad();

	//테이블들 어차피 get으로 꺼내야 하기에 그냥 public에 선언 
	HashTable<MobData*> mMobTable; //몹정보를 가지고있는 테이블 
	HashTable<MoveData*> mMovetable;
	HashTable<Tandata*> mTanTable;
	HashTable<StageSetData*> mStageTable;
};

#endif