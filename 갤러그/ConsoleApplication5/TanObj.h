#pragma once
#ifndef __TANOBJ__
#define __TANOBJ__
#include "BaseObject.h"
class TanObj :public BaseObject
{
public:
	TanObj(int x, int y, char* id, ObjectType type);
	~TanObj();

	virtual void Action(int frame);

	virtual void Draw();

	virtual void OnTrriger(Collider data); //충돌후 처리 
	virtual Collider GetCollider();
private:

	int mMoveSize;
	int mMoveX[10];
	int mMoveY[10];
};



#endif