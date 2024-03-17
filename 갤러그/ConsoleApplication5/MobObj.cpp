#include "MobObj.h"
#include "DrawManager.h"
#include "TableManager.h"
#include "CustomStr.h"
#include "ObjectManager.h"
MobObj::MobObj(int x, int y, char* id, ObjectType type)
{
	mX = x;
	mY = y;
	custom_strcpy(mID, id);
	mType = type;

	mMobTable = TableManager::GetInstance()->GetMobData(mID);

	if(mMobTable!=nullptr)
	{
		mHP = mMobTable->MaxHP;
		char* MoveID = mMobTable->MoveID;
		mMoveTable = TableManager::GetInstance()->GetMovetable(MoveID);

		if(mMoveTable !=nullptr)
		{
			mMoveSize = mMoveTable->MoveSize;

			for (int i = 0; i < mMoveSize; i++)
			{
				mMoveX[i] = mMoveTable->mX[i];
				mMoveY[i] = mMoveTable->mY[i];
			}
		}
	
	}
}

MobObj::~MobObj()
{

}

void MobObj::Action(int frame)
{
	if (mHP > 0)
	{
		int movecount = frame % mMoveSize;
		mX += mMoveX[movecount];
		mY += mMoveY[movecount];

		if (0 == frame % mMobTable->AttDelay && frame > mMobTable->StartDelay) //현재 프레임으로 쿨타임계산 + 게임시작시 최초 딜레이 계산 
		{
			ObjectManager::GetInstance()->CreateObject(mX, mY + 1, mMobTable->TanType, ObjectType::Tan);
			if (custom_strcmp(mMobTable->TanType, "q") == 0)
			{
				ObjectManager::GetInstance()->CreateObject(mX, mY + 1, const_cast<char*>("p"), ObjectType::Tan);
			}
			else if (custom_strcmp(mMobTable->TanType, "u") == 0)
			{
				ObjectManager::GetInstance()->CreateObject(mX, mY + 1, const_cast<char*>("U"), ObjectType::Tan);
			}
		}
	}
	else
	{
		mX = -1;
		mY = -1;
	}
}

void MobObj::Draw()
{
	if (mHP > 0)
	{
		DrawManager::GetInstance()->Sprite_Draw(mX, mY, mID[0]);
	}
}

void MobObj::OnTrriger(Collider data)
{
	auto pTan = TableManager::GetInstance()->GetTanData(data.ObjID);

	if (pTan!=nullptr)
	{
		mHP -= pTan->Damage;
		
	}
}

bool MobObj::isDead()
{
	return mHP <= 0;
}