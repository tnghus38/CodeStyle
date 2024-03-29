#include "DrawManager.h"
#include "CustomStr.h"
#include <memory.h>
#include "MyNew.h"

DrawManager* DrawManager::minstance = nullptr;
DrawManager::DrawManager()
{
}

DrawManager::~DrawManager()
{
}

DrawManager* DrawManager::GetInstance()
{
	if (minstance == nullptr)
		minstance = new DrawManager();
	return minstance;
}

// 버퍼의 내용을 화면으로 찍어주는 함수.
// 적군,아군,총알 등을 szScreenBuffer 에 넣어주고, 
// 1 프레임이 끝나는 마지막에 본 함수를 호출하여 버퍼 -> 화면 으로 그린다.
void DrawManager::Buffer_Flip(void)
{
	int iCnt;
	for (iCnt = 0; iCnt < dfSCREEN_HEIGHT; iCnt++)
	{
		cs_MoveCursor(0, iCnt);
		printf(szScreenBuffer[iCnt]);
	}
}

void DrawManager::Buffer_LineSet(int row, int column,const char* str)
{
	if (row >= dfSCREEN_HEIGHT,column>= dfSCREEN_WIDTH)
	{
		return;
	}
	//custom_strcpy(&szScreenBuffer[row][column], str);
	//만든 custom_strcpy함수는 끝에 \0을 무조건 채워 줘서  같은 라인에 여러번 콜해서 넣을경우 \0이후가 안나올수있음 
	char* target = const_cast<char*>(&szScreenBuffer[row][column]);
	while (*str != '\0')
	{
		*target = *str;
		target++;
		str++;
	}
}

// 화면 버퍼를 지워주는 함수
// 매 프레임 그림을 그리기 직전에 버퍼를 지워 준다. 
// 안그러면 이전 프레임의 잔상이 남으니까
void DrawManager::Buffer_Clear(void)
{
	int iCnt;
	memset(szScreenBuffer, ' ', dfSCREEN_WIDTH * dfSCREEN_HEIGHT);

	for (iCnt = 0; iCnt < dfSCREEN_HEIGHT; iCnt++)
	{
		szScreenBuffer[iCnt][dfSCREEN_WIDTH - 1] = '\0';
	}

}

//--------------------------------------------------------------------
// 버퍼의 특정 위치에 원하는 문자를 출력.
//
// 입력 받은 X,Y 좌표에 아스키코드 하나를 출력한다. (버퍼에 그림)
//--------------------------------------------------------------------
void DrawManager::Sprite_Draw(int iX, int iY, char chSprite)
{
	if (iX < 0 || iY < 0 || iX >= dfSCREEN_WIDTH - 1 || iY >= dfSCREEN_HEIGHT - 1)
		return;

	szScreenBuffer[iY][iX] = chSprite;
}