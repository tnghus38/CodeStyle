#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "MyNew.h"
#include <time.h>
#include "CustomStr.h"
#include "CList.h"

#undef new


//동적할당 로그남길 클래스 
class NewLogManager
{
public:
    NewLogManager(const char* szName);
    ~NewLogManager();
private:
    void MemoryAlloc(void* Ptr, int Size, const char* Filename, int Line, bool isArr);
    bool MemoryRelease(void* t, bool isArr);
   // void ErrorLog(newErrorType errorType, AllocInfo infodata);
    bool SaveFile();

    friend void* operator new (size_t size, char* File, int Line);
    friend void* operator new[](size_t size, char* File, int Line);
    friend void operator delete (void* p);
    friend void operator delete[](void* p);
private:
    CList<AllocInfo*> _InfoList; 
    char _FileName[64];
};

static NewLogManager newLogManager("testAlloc_");

void* operator new (size_t size, char* File, int Line)
{
    void* ptr = (void*)malloc(size);
    newLogManager.MemoryAlloc(ptr, size, File, Line ,false);
    return ptr;
}

void* operator new[](size_t size, char* File, int Line)
{
    void* ptr = malloc(size);
    newLogManager.MemoryAlloc(ptr, size, File, Line, true);
    return ptr;
}


void operator delete (void* p, char* File, int Line)
{
}
void operator delete[](void* p, char* File, int Line)
{
}

void operator delete (void* p)
{
    if (newLogManager.MemoryRelease(p,false))
    {
        free(p);
    }
}
void operator delete[](void* p)
{  
    if (newLogManager.MemoryRelease(p, true))
    {
        free(p);
    }
}

NewLogManager::NewLogManager(const char* szName)
{
    _InfoList.clear();


    char strTime[20];

    time_t curtime;
    tm Localdata;
    time(&curtime);
    localtime_s(&Localdata, &curtime);
    sprintf(strTime, " %04d%02d%02d_%02d%02d%02d", Localdata.tm_year + 1900, Localdata.tm_mon + 1, Localdata.tm_mday, Localdata.tm_hour, Localdata.tm_min, Localdata.tm_sec);
    custom_strcpy(_FileName, szName);
    custom_strcat(_FileName, strTime);
    custom_strcat(_FileName, ".txt");
    
}

NewLogManager::~NewLogManager()
{

    SaveFile();
    _InfoList.clear();
}

void NewLogManager::MemoryAlloc(void* Ptr, int Size, const char* Filename, int Line, bool isArr)
{
    AllocInfo* info = (AllocInfo*)malloc(sizeof(AllocInfo));
	info->ptr = Ptr;
    info->size = Size;
    info->filename = const_cast<char*> (Filename);
    info->line = Line;
    info->isArr = isArr;
    _InfoList.push_back(info);
}


bool NewLogManager::MemoryRelease(void* t, bool isArr)
{
    FILE* pFile;
    for (CList<AllocInfo*>::iterator tmp = _InfoList.begin(); tmp != _InfoList.end();++tmp)
    {
        if ((*tmp)->ptr == t)
        {
            if ((*tmp)->isArr == isArr)
            {
                free(*tmp);
                _InfoList.erase(tmp);
                return true;
            }
            else
            {


                errno_t err = fopen_s(&pFile, _FileName, "a");
                if (err != 0) return false;

                fprintf(pFile, "ARRAY [%p] [%d] %s:%d\n", (*tmp)->ptr, (*tmp)->size, (*tmp)->filename, (*tmp)->line);
                
                fclose(pFile);

                free(*tmp);
                _InfoList.erase(tmp); //해제 안된에 로그찍을때 또찍히지않도록
                return false;
            }
        }
    }

    errno_t err = fopen_s(&pFile, _FileName, "a");
    if (err != 0) return false;

    fprintf(pFile, "NOALLOC [%p]\n", t);
  
    fclose(pFile);

    return false;
}
bool NewLogManager::SaveFile()
{
    FILE* pFile; 
   
    errno_t err  = fopen_s(&pFile,_FileName, "a");
    if (err != 0) return false;

    for (CList<AllocInfo*>::iterator tmp = _InfoList.begin(); tmp != _InfoList.end();)
    {

        fprintf(pFile, "LEAK [%p] [%d] %s:%d\n", (*tmp)->ptr, (*tmp)->size, (*tmp)->filename, (*tmp)->line);
        tmp=_InfoList.erase(tmp);

    }
    fclose(pFile);
}
