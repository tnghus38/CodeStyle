#pragma once
#ifndef __OBJECTMANAGER__
#define __OBJECTMANAGER__
#include "CList.h"
#include "BaseObject.h"
class ObjectManager
{
private:

	ObjectManager();
	~ObjectManager();
	static ObjectManager* minstance;

public:
	static ObjectManager* GetInstance();
	bool CreateObject(int x, int y, char* id, ObjectType type);
	bool DestroyObject(BaseObject* obj);
	void Update(int frame);
	void Render();
	void ClearList();
private:
	CList<BaseObject*> ObjectList; //화면 출력될 애들 
	 
};

#endif