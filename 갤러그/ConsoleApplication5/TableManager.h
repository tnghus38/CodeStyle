#pragma once
#ifndef __TABLEMANAGER__
#define __TABLEMANAGER__

#include "MyDefine.h"
#include "HashTable.h"
#include "CList.h"


//���̺� ������ 
struct MoveData //���̳� ź �̵� ���̺� ������ 
{
	char MoveId[2];
	int mX[10];
	int mY[10];
	int MoveSize;
};
struct SpawnData //�������� ��������
{
	char MobID[2];
	int X = 0;
	int Y = 0;
};
struct StageSetData //�������� ������
{
	int StageNum;
	CList<SpawnData*> SpawnList;
};

struct MobData   /// �� ������
{
	char MobID[2]; // Y T M
	int MaxHP;
	int AttDelay;
	char TanType[2];
	int StartDelay;
	char MoveID[2];
};

struct Tandata // �Ѿ� ������ 
{
	char TanID[2]; //ź��� 
	int Damage;//������

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
	//���̺� �ε� 
	bool _MobTableLoad();
	bool _StageTableLoad();
	bool _TanTableLoad();
	bool _MoveTableLoad();

	//���̺�� ������ get���� ������ �ϱ⿡ �׳� public�� ���� 
	HashTable<MobData*> mMobTable; //�������� �������ִ� ���̺� 
	HashTable<MoveData*> mMovetable;
	HashTable<Tandata*> mTanTable;
	HashTable<StageSetData*> mStageTable;
};

#endif