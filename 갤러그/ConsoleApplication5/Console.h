#pragma once
// Windows �� �ܼ� ȭ�鿡�� Ŀ�� ����
#ifndef __CONSOLE__
#define __CONSOLE__

#define dfSCREEN_WIDTH		81		// �ܼ� ���� 80ĭ + NULL
#define dfSCREEN_HEIGHT		24		// �ܼ� ���� 24ĭ

//�ʱ�ȭ
void cs_Initial(void);


//Ŀ���̵�
void cs_MoveCursor(int iPosX, int iPosY);

//Ŭ����
void cs_ClearScreen(void);


#endif

