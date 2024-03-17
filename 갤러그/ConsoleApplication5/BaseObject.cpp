#include "BaseObject.h"
#include "CustomStr.h"
BaseObject::BaseObject(int x, int y, char* id, ObjectType type) 
{
	mX = x;
	mY = y;
	custom_strcpy(mID, id);
	mType = type;
}
BaseObject::BaseObject()
{

}
BaseObject::~BaseObject()
{

}

ObjectType BaseObject::getType()
{
	return mType;
}

bool BaseObject::CheckCollider(Collider data)
{
	if (mX == data.posX && mY == data.posY)
	{
		return true;
	}
	else
		return false;
}

Collider BaseObject::GetCollider()
{
	Collider data;
	data.posX = mX;
	data.posY = mY;

	custom_strcpy(data.ObjID, mID);

	return data;
}