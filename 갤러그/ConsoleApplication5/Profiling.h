#pragma once
#ifndef __PROFILING__
#define __PROFILING__
#include <Windows.h>
typedef struct
{
	//long			lFlag;				// ���������� ��� ����. (�迭�ÿ���)
	char			szName[64];			// �������� ���� �̸�.

	LARGE_INTEGER	lStartTime;			// �������� ���� ���� �ð�.

	__int64			iTotalTime;			// ��ü ���ð� ī���� Time.	(��½� ȣ��ȸ���� ������ ��� ����)
	__int64			iMin[2];			// �ּ� ���ð� ī���� Time.	(�ʴ����� ����Ͽ� ���� / [0] �����ּ� [1] ���� �ּ� [2])
	__int64			iMax[2];			// �ִ� ���ð� ī���� Time.	(�ʴ����� ����Ͽ� ���� / [0] �����ִ� [1] ���� �ִ� [2])

	__int64			iCall;				// ���� ȣ�� Ƚ��.

} PROFILE_SAMPLE;


// �ϳ��� �Լ� Profiling ����, �� �Լ�.
void ProfileBegin(const char* szName);
void ProfileEnd(const char* szName);

// Profiling �� ����Ÿ�� Text ���Ϸ� ����Ѵ�.
void ProfileDataOutText(const char* szFileName);

// �������ϸ� �� �����͸� ��� �ʱ�ȭ �Ѵ�.
void ProfileReset(void);

class CProfiling
{
public:
	CProfiling(const char* szName);
	~CProfiling();

private:
	char _szName[256];
};

#define Profile(Name) CProfiling profile(Name);
#define ProfileDataSave(Name) ProfileDataOutText(Name);
#define ProfileDataReset ProfileReset();
#endif