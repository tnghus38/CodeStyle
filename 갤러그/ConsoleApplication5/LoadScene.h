#pragma once
#ifndef __LOADSCENE__
#define __LOADSCENE__
#include "BaseScene.h"
class LoadScene :public BaseScene
{
public:
	LoadScene();
	~LoadScene();

	virtual void Enter();
	virtual void Updata();
	virtual void Exit();

private:
	void _Show();
	int curStage;
};

#endif