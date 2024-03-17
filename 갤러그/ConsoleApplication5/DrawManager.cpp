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

// ������ ������ ȭ������ ����ִ� �Լ�.
// ����,�Ʊ�,�Ѿ� ���� szScreenBuffer �� �־��ְ�, 
// 1 �������� ������ �������� �� �Լ��� ȣ���Ͽ� ���� -> ȭ�� ���� �׸���.
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
	//���� custom_strcpy�Լ��� ���� \0�� ������ ä�� �༭  ���� ���ο� ������ ���ؼ� ������� \0���İ� �ȳ��ü����� 
	char* target = const_cast<char*>(&szScreenBuffer[row][column]);
	while (*str != '\0')
	{
		*target = *str;
		target++;
		str++;
	}
}

// ȭ�� ���۸� �����ִ� �Լ�
// �� ������ �׸��� �׸��� ������ ���۸� ���� �ش�. 
// �ȱ׷��� ���� �������� �ܻ��� �����ϱ�
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
// ������ Ư�� ��ġ�� ���ϴ� ���ڸ� ���.
//
// �Է� ���� X,Y ��ǥ�� �ƽ�Ű�ڵ� �ϳ��� ����Ѵ�. (���ۿ� �׸�)
//--------------------------------------------------------------------
void DrawManager::Sprite_Draw(int iX, int iY, char chSprite)
{
	if (iX < 0 || iY < 0 || iX >= dfSCREEN_WIDTH - 1 || iY >= dfSCREEN_HEIGHT - 1)
		return;

	szScreenBuffer[iY][iX] = chSprite;
}