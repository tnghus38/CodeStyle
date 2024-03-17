#pragma once
#ifndef __MOBOBJ__
#define __MOBOBJ__
#include "BaseObject.h"
struct MobData;
struct MoveData;
class MobObj :public BaseObject
{
public:
	MobObj(int x, int y, char* id, ObjectType type);
	~MobObj();

	virtual void Action(int frame);

	virtual void Draw();

	virtual void OnTrriger(Collider data); //충돌후 처리 
	bool isDead();
private:
	int mHP;
	int mMoveSize;
	int mMoveX[10];
	int mMoveY[10];

	MobData* mMobTable = nullptr;
	MoveData* mMoveTable = nullptr;
};



#endif