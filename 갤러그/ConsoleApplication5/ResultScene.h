#pragma once
#ifndef __RESULTSCENE__
#define __RESULTSCENE__
#include "BaseScene.h"
class ResultScene :public BaseScene
{
public:
	ResultScene();
	~ResultScene();

	virtual void Enter();
	virtual void Updata();
	virtual void Exit();

private:
	int ResultCursor;
	int curStage;
	ResultType::Type result;
};

#endif