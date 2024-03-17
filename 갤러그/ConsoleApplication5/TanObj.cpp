#include "TanObj.h"
#include "DrawManager.h"
#include "CustomStr.h"
#include "TableManager.h"
#include "ObjectManager.h"
TanObj::TanObj(int x, int y, char* id, ObjectType type)
{
	mX = x;
	mY = y;
	custom_strcpy(mID, id);
	mType = type;

	auto pTan = TableManager::GetInstance()->GetTanData(mID);

	if (pTan != nullptr)
	{
		auto pMove = TableManager::GetInstance()->GetMovetable(pTan->MoveType);
		if (pMove != nullptr)
		{
			mMoveSize = pMove->MoveSize;

			for (int i = 0; i < mMoveSize; i++)
			{
				mMoveX[i] = pMove->mX[i];
				mMoveY[i] = pMove->mY[i];
			}
		}
	}
}

TanObj::~TanObj()
{

}

Collider TanObj::GetCollider()
{
	Collider data;
	data.posX = mX;
	data.posY = mY;
	if (mMoveY[0] > 0)
		data.TargetObj = ObjectType::Player;
	else 
		data.TargetObj = ObjectType::Mob;
	custom_strcpy(data.ObjID, mID);

	return data;
}
void TanObj::Action(int frame)
{
	//Åº¸· ÀÌµ¿
	int movecount = frame % mMoveSize;
	mX += mMoveX[movecount];
	mY += mMoveY[movecount];
	
}

void TanObj::Draw()
{

	DrawManager::GetInstance()->Sprite_Draw(mX, mY, mID[0]);
}

void TanObj::OnTrriger(Collider data)
{
	//effect
	//sound 
}

