#pragma once
// Windows 의 콘솔 화면에서 커서 제어
#ifndef __CONSOLE__
#define __CONSOLE__

#define dfSCREEN_WIDTH		81		// 콘솔 가로 80칸 + NULL
#define dfSCREEN_HEIGHT		24		// 콘솔 세로 24칸

//초기화
void cs_Initial(void);


//커서이동
void cs_MoveCursor(int iPosX, int iPosY);

//클리어
void cs_ClearScreen(void);


#endif

