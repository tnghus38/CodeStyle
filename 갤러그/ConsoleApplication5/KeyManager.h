#pragma once
#ifndef __KEYMANAGER__
#define __KEYMANAGER__
#include "CList.h"
struct KeyMessage
{
	int x=0;
	int y=0;
	char c=' ';
};

class KeyManager
{
private:
	KeyManager();
	~KeyManager();
	static KeyManager* minstance;
public:

	static KeyManager* GetInstance();
	void GetKey();
	void EnQueue(KeyMessage* data);
	bool DeQueue(KeyMessage* data);
	void Clear();
private:
	CList<KeyMessage*> MessageQueue;

};


#endif