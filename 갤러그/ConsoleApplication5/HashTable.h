#pragma once
#ifndef __HASHTABLE__
#define __HASHTABLE__

#define tableSize  401
#include "CustomStr.h"
#include <stdlib.h>
template <typename NodeData>
struct HashListNode
{
    char Key[100];          //key
    NodeData data;          //������ 
    HashListNode* Next = nullptr; //������� ������ 
};


template <typename ListData>
class Custom_Hash_List
{
public:
    Custom_Hash_List() {};
    ~Custom_Hash_List() { Clear(); };
    void Clear();                                 // ����Ʈ Ŭ���� 
    void DeleteFirst();                           // ��� ������ ����� 
    bool IsEmpty();                               // �� ����Ʈ  üũ

    ListData GetHead();                           //����� �������� 
    bool Insert(const char* key, ListData Newdata);     //��� �߰� (�ߺ�key������)
    ListData GetData(const char* key);                  // �ش�key �� ��� �˻� 
    bool ContainsKey(const char* key);                  // �ش�key �ߺ� Ȯ��
    bool Remove(const char* key);                       //�ش� key ��� ����� 

private:

    HashListNode<ListData>* pHead = nullptr;          //����Ʈ ù ��� 
};


template <typename ListData>
void Custom_Hash_List<ListData>::Clear()
{
    while (!IsEmpty())
        DeleteFirst();
}

template <typename ListData>
void Custom_Hash_List<ListData>::DeleteFirst()
{
    if (pHead != nullptr)
    {
        HashListNode<ListData>* pTemp = pHead->Next;
        free(pHead);
        pHead = pTemp;
    }
}

template <typename ListData>
bool Custom_Hash_List<ListData>::IsEmpty()
{
    return pHead == nullptr;
}

template <typename ListData>
ListData Custom_Hash_List<ListData>::GetHead()
{
    return pHead->data;
}

template <typename ListData>
bool Custom_Hash_List<ListData>::Insert(const char* _key, ListData Newdata)
{

    char* key = const_cast<char*>(_key);
    HashListNode<ListData>* pdata = (HashListNode<ListData> *) malloc(sizeof(HashListNode<ListData>));

    custom_strcpy(pdata->Key, key);
    pdata->data = Newdata;
    pdata->Next = nullptr;
    if (pHead == nullptr)
    {
        pHead = pdata;
        return true;
    }

    HashListNode<ListData>* tmp = pHead;

    while (tmp != nullptr)
    {
        if (custom_strcmp(tmp->Key, key) == 0)
        {
            return false;
        }
        if (tmp->Next == nullptr)
            break;
        tmp = tmp->Next;
    }
    tmp->Next = pdata;

    return true;
}

template <typename ListData>
ListData Custom_Hash_List<ListData>::GetData(const char* _key)
{
    char* key = const_cast<char*>(_key);
    HashListNode<ListData>* tmp = pHead;

    if (custom_strcmp(tmp->Key, key) == 0)
    {
        return tmp->data;
    }

    while (tmp != nullptr)
    {
        if (custom_strcmp(tmp->Key, key) == 0)
        {

            return tmp->data;
        }

        tmp = tmp->Next;
    }

    return tmp->data;
}


template <typename ListData>
bool Custom_Hash_List<ListData>::ContainsKey(const char* _key)
{
    char* key = const_cast<char*>(_key);
    if (pHead == nullptr)
    {
        return false;
    }

    HashListNode<ListData>* tmp = pHead;

    while (tmp != nullptr)
    {
        if (custom_strcmp(tmp->Key, key) == 0)
        {
            return true;
        }
        if (tmp->Next == nullptr)
            break;
        tmp = tmp->Next;
    }

    return false;
}

template <typename ListData>
bool Custom_Hash_List<ListData>::Remove(const char* _key)
{
    char* key = const_cast<char*>(_key);
    if (pHead == nullptr)
    {
        return false;
    }

    HashListNode<ListData>* tmp = pHead;

    if (custom_strcmp(tmp->Key, key) == 0)
    {
        pHead = pHead->Next;
        free(tmp);
        return true;
    }

    while (tmp->Next != nullptr)
    {
        if (custom_strcmp(tmp->Next->Key, key) == 0)
        {
            HashListNode<ListData>* tmp2 = tmp->Next;

            tmp->Next = tmp->Next->Next;
            free(tmp2);

            return true;
        }
        if (tmp->Next->Next == nullptr)
            break;
        tmp = tmp->Next;
    }
    return false;
}

template <typename HashData>
class HashTable
{
public:
    HashTable() {};
    ~HashTable() {};

    bool Add(const char* key, HashData data);    // ���̺� ������ �߰� 
    bool ContainsKey(const char* key);           // �ߺ�key Ȯ�� 
    bool Remove(const char* key);                // �ش�key ������ ���� 

    HashData operator[] (const char* key);       // key�� �����͸� ������ 

private:
    int GetHashKey(char* Key);                   // �ؽ��Լ�  key���� index�� �ٲ۴� 
    Custom_Hash_List<HashData> HTable[tableSize];    // �����Ͱ� �� ���̺�� tableSize��(401 �ϴ� �۰� ����) �Ҽ��� �غ��Ѵ� 
};

template <typename HashData>
bool HashTable<HashData>::Add(const char* key, HashData data)
{

    char* str = const_cast<char*>(key);
    int index = GetHashKey(str);
    return  HTable[index].Insert(str, data);
}

template <typename HashData>
bool HashTable<HashData>::ContainsKey(const char* key)
{
    char* str = const_cast<char*>(key);
    int index = GetHashKey(str);
    return HTable[index].ContainsKey(str);
}

template <typename HashData>
bool HashTable<HashData>::Remove(const char* key)
{
    char* str = const_cast<char*>(key);
    int index = GetHashKey(str);
    return HTable[index].Remove(str);
}

template <typename HashData>
HashData HashTable<HashData>::operator[] (const char* key)
{

    char* str = const_cast<char*>(key);
    int index = GetHashKey(str);
    return HTable[index].GetData(str);
}

template <typename HashData>
int HashTable<HashData>::GetHashKey(char* Key)
{
    char* mKey = Key;
    int tmp = 1;

    while (*mKey != 0)
    {

        tmp += *mKey;
        mKey++;
    }
    if (tmp < 0)
        tmp *= -1;
    return tmp % tableSize;
}
#endif