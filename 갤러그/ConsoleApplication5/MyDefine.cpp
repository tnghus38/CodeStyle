#include "MyDefine.h"

bool SceneType::IsValid(Type _type)
{
	switch (_type)
	{
	case SceneType::Title:
	case SceneType::Load:
	case SceneType::Game:
	case SceneType::Result:
		return true;
	case SceneType::Max:
	case SceneType::NoneScene:
	default:
		return false;
	}
}
