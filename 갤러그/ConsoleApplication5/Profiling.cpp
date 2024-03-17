#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "Profiling.h"
#include "CustomStr.h"
#include "CList.h"


CList<PROFILE_SAMPLE*>* sProFile = new CList<PROFILE_SAMPLE*>();


CProfiling::CProfiling(const char* szName)
{
	ProfileBegin(szName);
	custom_strcpy(_szName, szName);
}

CProfiling::~CProfiling()
{
	ProfileEnd(_szName);
}
// 하나의 함수 Profiling 시작, 끝 함수.
void ProfileBegin(const char* szName )
{
	bool _flag = true;

	for (CList<PROFILE_SAMPLE*>::iterator tmp = sProFile->begin(); tmp != sProFile->end(); ++tmp)
	{
		if (custom_strcmp((*tmp)->szName, szName) == 0)
		{
			QueryPerformanceCounter(&((*tmp)->lStartTime));
			_flag = false;
			break;
		}
	}
	

	if (_flag)
	{
		PROFILE_SAMPLE* _data = new PROFILE_SAMPLE;
		custom_strcpy((char*)_data->szName, (char*)szName);
		_data->iMax[0] = 0;
		_data->iMin[0] = 0;
		_data->iMax[1] = 0;
		_data->iMin[1] = 0;
		_data->iCall = 0;
		_data->iTotalTime = 0;

		QueryPerformanceCounter(&(_data->lStartTime));
		sProFile->push_back(_data);
	}
}
void ProfileEnd(const char* szName)
{
	LARGE_INTEGER End;
	QueryPerformanceCounter(&End);
	for (CList<PROFILE_SAMPLE*>::iterator tmp = sProFile->begin(); tmp != sProFile->end(); ++tmp)
	{
		if (custom_strcmp((*tmp)->szName, szName) == 0)
		{
			__int64 result = (End.QuadPart - (*tmp)->lStartTime.QuadPart);
			(*tmp)->iCall++;
			(*tmp)->iTotalTime += result;

			for (int i = 0; i < 2; i++)
			{
				if ((*tmp)->iMax[i] == 0 || (*tmp)->iMax[i] < result)
				{
					(*tmp)->iMax[i] = result;
				}
			}

			for (int i = 0; i < 2; i++)
			{
				if ((*tmp)->iMin[i] == 0 || (*tmp)->iMin[i] > result)
				{
					(*tmp)->iMin[i] = result;
				}
			}
			break;
		}
	}
}

// Profiling 된 데이타를 Text 파일로 출력한다.
void ProfileDataOutText(const char* szFileName)
{
	FILE* pFile;

	char str[256] ="Name | Average | Min1 | Min2 | Max1 | Max2 | Call | \n";
	pFile = fopen(szFileName, "a");


	fprintf(pFile, str);
	for (CList<PROFILE_SAMPLE*>::iterator tmp = sProFile->begin(); tmp != sProFile->end(); ++tmp)
	{
		if ((*tmp)->iCall > 4)
		{
			float _average = (float)((*tmp)->iTotalTime / ((*tmp)->iCall - 4)) / 10.0f;

			sprintf(str, "%s | %0.3fms | %0.3fms | %0.3fms | %0.3fms | %0.3fms | %I64d | \n", (*tmp)->szName, _average, (float)(*tmp)->iMin[0] / 10.0f, (float)(*tmp)->iMin[1] / 10.0f, (float)(*tmp)->iMax[0] / 10.0f, (float)(*tmp)->iMax[1] / 10.0f, (*tmp)->iCall);

			fprintf(pFile, str);
		}
	}

	fclose(pFile);
	return;
}

// 프로파일링 된 데이터를 모두 초기화 한다.
void ProfileReset(void)
{
	//QueryPerformanceFrequency(&Freq);	// 1초의 진동주기

	for (CList<PROFILE_SAMPLE*>::iterator tmp = sProFile->begin(); tmp != sProFile->end(); ++tmp)
	{
		(*tmp)->iCall = 0;
		(*tmp)->iTotalTime = 0;
		(*tmp)->iMax[0] = 0;
		(*tmp)->iMin[0] = 0;
		(*tmp)->iMax[1] = 0;
		(*tmp)->iMin[1] = 0;
	}
	
}