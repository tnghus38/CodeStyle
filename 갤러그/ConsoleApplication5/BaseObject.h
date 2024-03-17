#pragma once
#ifndef __BASEOBJECT__
#define __BASEOBJECT__
enum ObjectType
{
	Player=0,Tan,Mob
};

struct Collider
{
	char ObjID[2];
	int posX;
	int posY;
	ObjectType TargetObj;
};

class BaseObject
{
public:
	BaseObject(int x, int y, char* id, ObjectType type);
	BaseObject();
	virtual ~BaseObject();

	virtual void Action(int frame) = 0;
	virtual void Draw() = 0;

	virtual void OnTrriger(Collider data) = 0; //충돌후 처리 
	bool CheckCollider(Collider data); //충돌 체크용 함수  

	virtual Collider GetCollider();//충돌처리시 줄정보     tan(bullet) 객체에서 자신의 위치와 id를 빼서 collider구조체로 포장해서 전달해줄거임   혹시 탄이외의 객체 끼리 충돌처리 할일도 있을지모르니 부모 오브젝트에 밖음 
	ObjectType getType();
protected:
	int mX;
	int mY;
	char mID[2];
	ObjectType mType;
};



#endif