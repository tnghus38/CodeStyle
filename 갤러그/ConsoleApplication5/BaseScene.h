#pragma once
#ifndef __BASESCENE__
#define __BASESCENE__
#include "MyDefine.h"

class BaseScene
{
public:
	BaseScene() {};
	virtual ~BaseScene()= default;

	virtual void Enter()=0; 
	virtual void Updata() = 0;
	virtual void Exit() = 0;

protected:
	int curframe;
};

#endif