#pragma once
#ifndef __TITLESCENE__
#define __TITLESCENE__
#include "BaseScene.h"
class TitleScene :public BaseScene
{
public:
	TitleScene();
	~TitleScene();

	virtual void Enter();
	virtual void Updata();
	virtual void Exit();

private:
	int curStage;
};

#endif