#include "ObjectManager.h"
#include "PlayerObj.h"
#include "MobObj.h"
#include "TanObj.h"
#include "CustomStr.h"
#include "Console.h"
#include "SceneManager.h"
#include "MyNew.h"


ObjectManager* ObjectManager::minstance = nullptr;
ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	for (CList<BaseObject*>::iterator tmp = ObjectList.begin(); tmp != ObjectList.end();)
	{
		delete (*tmp);
		tmp = ObjectList.erase(tmp);
	}
}
ObjectManager* ObjectManager::GetInstance()
{
	if (minstance == nullptr)
		minstance = new ObjectManager();
	return minstance;
}
bool ObjectManager::CreateObject(int x, int y, char* id, ObjectType type)
{
	switch (type)
	{
	case ObjectType::Player:
	{
		PlayerObj* tmp = new PlayerObj(x, y, id, type);
		ObjectList.push_back(tmp);
		return true;
	}
		break;
	case ObjectType::Mob:
	{
		MobObj* tmp = new MobObj(x, y, id, type);
		ObjectList.push_back(tmp);
		return true;
	}
		break;
	case ObjectType::Tan:
	{
		TanObj* tmp = new TanObj(x, y, id, type);
		ObjectList.push_back(tmp);
		return true;
	}
		break;
	default:
		break;
	}
	return false;
}
bool ObjectManager::DestroyObject(BaseObject* obj)
{
	for (CList<BaseObject*>::iterator tmp = ObjectList.begin(); tmp != ObjectList.end(); ++tmp)
	{
		if ((*tmp) == obj)
		{
			delete (*tmp);
			ObjectList.erase(tmp);
			return true;
		}
	}
	return false;
}

void ObjectManager::Update(int frame)
{

	//이동 
	for (CList<BaseObject*>::iterator tmp = ObjectList.begin(); tmp != ObjectList.end(); ++tmp)
	{
		(*tmp)->Action(frame);
	}


	// 충돌 처리 
	for (CList<BaseObject*>::iterator tmp = ObjectList.begin(); tmp != ObjectList.end();)
	{
		bool isdelete = false;
		if ((*tmp)->getType() == ObjectType::Tan)
		{
			Collider tmptan = (*tmp)->GetCollider();
			for (CList<BaseObject*>::iterator tmp2 = ObjectList.begin(); tmp2 != ObjectList.end(); ++tmp2)
			{
				              //타겟이 맞고                                                  // 오브젝트의 위치가 같으면 충돌처리
				if ((*tmp)->GetCollider().TargetObj== (*tmp2)->getType() && (*tmp)->GetCollider().posX == (*tmp2)->GetCollider().posX && (*tmp)->GetCollider().posY == (*tmp2)->GetCollider().posY)
				{
					(*tmp2)->OnTrriger((*tmp)->GetCollider());
					isdelete = true;
				}
			}

			// 범위넘어간 탄 오브젝트들 찾아 지움 
			if ((*tmp)->GetCollider().posX >= dfSCREEN_WIDTH - 1 || (*tmp)->GetCollider().posY >= dfSCREEN_HEIGHT - 1 || (*tmp)->GetCollider().posX < 0 || (*tmp)->GetCollider().posY < 0)
			{
				isdelete = true;
			}
		}

		if (isdelete)
		{
			delete (*tmp);
			tmp = ObjectList.erase(tmp);
		}
		else
		{
			++tmp;
		}
		
	}
	int mobcount = 0;
	//결과판정 
	for (CList<BaseObject*>::iterator tmp = ObjectList.begin(); tmp != ObjectList.end(); ++tmp)
	{
		if ((*tmp)->getType() == ObjectType::Player)
		{
			if (((PlayerObj*)(*tmp))->isDead())
			{
				SceneManager::GetInstance()->SetReult(ResultType::Lose);
				SceneManager::GetInstance()->ChangeScene(SceneType::Result);
				return;
			}
		}
		if ((*tmp)->getType() == ObjectType::Mob)
		{
			if (((MobObj*)(*tmp))->isDead())
			{
			}
			else
			{
				mobcount++;
			}
		}

	}
	if (mobcount == 0)
	{
		SceneManager::GetInstance()->SetReult(ResultType::Win);
		SceneManager::GetInstance()->ChangeScene(SceneType::Result);
	}
	

}

void ObjectManager::Render()
{
	for (CList<BaseObject*>::iterator tmp = ObjectList.begin(); tmp != ObjectList.end(); ++tmp)
	{
		(*tmp)->Draw();
	}
}

void ObjectManager::ClearList()
{
	//ObjectList.clear();
	for (CList<BaseObject*>::iterator tmp = ObjectList.begin(); tmp != ObjectList.end();)
	{
			delete (*tmp);
			tmp =ObjectList.erase(tmp);
	}
}