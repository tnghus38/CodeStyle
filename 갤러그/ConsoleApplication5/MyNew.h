#pragma once
#ifndef __MYNEW__
#define __MYNEW__


#define _CRT_SECURE_NO_WARNINGS

//new �����ε� 
void* operator new (size_t size, char* File, int Line); 
void* operator new[](size_t size, char* File, int Line);

// new�� ���������� ���� �޴� �����ε��� �ϸ� ������ ����¾�  new�����ϸ� ������ ȣ��Ǵ¾ֶ� �����ؾ���
void operator delete (void* p, char* File, int Line);
void operator delete[](void* p, char* File, int Line);

// ������ ����� delete �����ε� 
void operator delete (void* p);
void operator delete[](void* p);


//�����Ҵ� �α� ������ 
struct AllocInfo
{
	void* ptr;  //Ÿ���� �ʿ���� ���� ���������� �ּҸ����� 
	int  size; // �Ҵ� ������ 
	char* filename;  // __file �� ��� ������ġ 
	int line; /// __Line ���° ������ 
	bool isArr;  // �迭 ���� 
};



#define new new(const_cast<char*> (__FILE__),__LINE__)







#endif