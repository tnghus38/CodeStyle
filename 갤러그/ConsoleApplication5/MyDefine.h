#pragma once
#define MaxMob 10   //�������� �ְ� ���� ���� 
#define MaxStage 3 //�ִ� ��������


namespace SceneType
{
	enum Type : int
	{
		NoneScene = 0,
		Title,
		Load,
		Game,
		Result,
		Max
	};

	bool IsValid(Type _type);
}

namespace ResultType
{
	enum  Type :int
	{
		None = 0,
		Win,
		Lose
	};
};

struct StageInfo
{
	int curStage = 0;
	ResultType::Type type = ResultType::None;
};