#include "PlayerObj.h"
#include "DrawManager.h"
#include "CustomStr.h"
#include "TableManager.h"
#include "KeyManager.h"
#include "Console.h"
#include "ObjectManager.h"
PlayerObj::PlayerObj(int x, int y, char* id, ObjectType type)
{
	mX = x;
	mY = y;
	custom_strcpy(mID, id);
	mType = type;
	mHP = 1;//테스트용 1
}
PlayerObj::~PlayerObj()
{

}

void PlayerObj::Action(int frame)
{
	KeyMessage keyData;
	if (KeyManager::GetInstance()->DeQueue(&keyData))
	{
		if (mX + keyData.x < dfSCREEN_WIDTH - 1 && mX + keyData.x > 0)
		{
			mX += keyData.x;
		}
		if (mY + keyData.y < dfSCREEN_HEIGHT - 1 && mY + keyData.y > 15)
		{
			mY += keyData.y;
		}
		if (keyData.c == 's')
		{
			ObjectManager::GetInstance()->CreateObject(mX, mY - 1, const_cast<char*>("I"), ObjectType::Tan);
		}
		

	}
	

}

void PlayerObj::Draw()
{

	DrawManager::GetInstance()->Sprite_Draw(mX, mY, mID[0]);
}

void PlayerObj::OnTrriger(Collider data)
{
	auto pTan = TableManager::GetInstance()->GetTanData(data.ObjID);

	if (pTan != nullptr)
	{
		mHP -= pTan->Damage;

	}
}
bool PlayerObj::isDead()
{
	return mHP <= 0;
}