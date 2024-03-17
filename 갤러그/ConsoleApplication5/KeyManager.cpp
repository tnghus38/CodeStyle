#include"KeyManager.h"
#include <Windows.h>
#include "MyNew.h"

KeyManager* KeyManager::minstance = nullptr;
KeyManager::KeyManager()
{
}

KeyManager::~KeyManager()
{
}

KeyManager* KeyManager::GetInstance()
{
	if (minstance == nullptr)
		minstance = new KeyManager();
	return minstance;
}
void KeyManager::GetKey()
{
	
	int x = 0;
	int y = 0;
	char c = ' ';
	//키조작 
	if (GetAsyncKeyState(VK_LEFT) )
	{
		x = -1;
	}
	if (GetAsyncKeyState(VK_RIGHT) )
	{
		x=1;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		y=1;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		y = -1;
	}
	//탄 발사
	if (GetAsyncKeyState(VK_SPACE))
	{
		c = 's';
	}
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		
			exit(0);//강제 종료  (메모리확인용) 
	}
	if (GetAsyncKeyState(VK_RETURN))
	{
		c = 'r';
	}
	if (x != 0 || y != 0 || c != ' ')
	{
		KeyMessage* data = new KeyMessage;
		data->x = x;
		data->y = y;
		data->c = c;
		EnQueue(data);
	}
}

void KeyManager::EnQueue(KeyMessage* data)
{
	MessageQueue.push_back(data);
}

bool KeyManager::DeQueue(KeyMessage* data)   
{ 
	if (MessageQueue.size() > 0)
	{
		MessageQueue.pop_front();
		CList<KeyMessage*>::iterator tmp = MessageQueue.begin();
		data->x = (*tmp)->x;
		data->y = (*tmp)->y;
		data->c = (*tmp)->c;
		delete (*tmp);
		MessageQueue.erase(tmp);
		return true;
	}
	else
		return false;
}

void KeyManager::Clear()
{
	//MessageQueue.clear();
	for (CList<KeyMessage*>::iterator tmp = MessageQueue.begin(); tmp != MessageQueue.end();)
	{
		delete (*tmp);
		tmp = MessageQueue.erase(tmp);
	}
}