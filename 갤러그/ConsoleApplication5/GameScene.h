#pragma once
#ifndef __GAMESCENE__
#define __GAMESCENE__
#include "BaseScene.h"
class GameScene :public BaseScene
{
public:
	GameScene();
	~GameScene();

	virtual void Enter();
	virtual void Updata();
	virtual void Exit();
private:

};

#endif