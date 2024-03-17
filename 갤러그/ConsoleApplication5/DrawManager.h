#pragma once
#ifndef __DRAWMANAGER__
#define __DRAWMANAGER__

#include <stdio.h>
#include "Console.h"
class DrawManager
{
private:
	DrawManager();
	~DrawManager();
	static DrawManager* minstance;
public:
	static DrawManager* GetInstance();
	void Buffer_Flip(void);
	void Buffer_Clear(void);
	void Buffer_LineSet(int row, int column, const char* str);
	void Sprite_Draw(int iX, int iY, char chSprite);
private:
	char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
};


#endif