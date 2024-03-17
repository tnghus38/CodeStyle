#pragma once
#ifndef __PLAYEROBJ__
#define __PLAYEROBJ__
#include "BaseObject.h"
class PlayerObj :public BaseObject
{
public:
	PlayerObj(int x, int y, char* id, ObjectType type);
	~PlayerObj();

	virtual void Action(int frame);

	virtual void Draw();

	virtual void OnTrriger(Collider data); //�浹�� ó�� 
	bool isDead();
private:

	int mHP;
};



#endif