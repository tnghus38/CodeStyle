#pragma once
#ifndef __MYNEW__
#define __MYNEW__


#define _CRT_SECURE_NO_WARNINGS

//new 오버로딩 
void* operator new (size_t size, char* File, int Line); 
void* operator new[](size_t size, char* File, int Line);

// new에 파일정보랑 라인 받는 오버로딩을 하면 저절로 생기는애  new실패하면 저절로 호출되는애라 선언해야함
void operator delete (void* p, char* File, int Line);
void operator delete[](void* p, char* File, int Line);

// 실제로 사용할 delete 오버로딩 
void operator delete (void* p);
void operator delete[](void* p);


//동적할당 로그 데이터 
struct AllocInfo
{
	void* ptr;  //타입은 필요없고 무슨 포인터인지 주소만저장 
	int  size; // 할당 사이즈 
	char* filename;  // __file 로 얻는 파일위치 
	int line; /// __Line 몇번째 줄인지 
	bool isArr;  // 배열 여부 
};



#define new new(const_cast<char*> (__FILE__),__LINE__)







#endif