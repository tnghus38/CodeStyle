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

	virtual void OnTrriger(Collider data) = 0; //�浹�� ó�� 
	bool CheckCollider(Collider data); //�浹 üũ�� �Լ�  

	virtual Collider GetCollider();//�浹ó���� ������     tan(bullet) ��ü���� �ڽ��� ��ġ�� id�� ���� collider����ü�� �����ؼ� �������ٰ���   Ȥ�� ź�̿��� ��ü ���� �浹ó�� ���ϵ� �������𸣴� �θ� ������Ʈ�� ���� 
	ObjectType getType();
protected:
	int mX;
	int mY;
	char mID[2];
	ObjectType mType;
};



#endif