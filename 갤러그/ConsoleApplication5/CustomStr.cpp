#include "CustomStr.h"

int custom_strlen(char* str)
{
    int len = 0;
    while (*str != '\0')
    {
        len++;
    }
    return len;
}

char* custom_strcpy(char* _str, const char* strSrc)
{
    char* src = const_cast<char*>(strSrc);
    char* str = _str;
    while (*src != '\0')
    {
        *str = *src;
        str++;
        src++;
    }
    *str = '\0';
    return _str;
}


int custom_strcmp(const char* s1, const char* s2)
{
    char* str1 = const_cast<char*>(s1);
    char* str2 = const_cast<char*>(s2);

    while (*str1 != '\0')
    {
        if (*str1 != *str2)
            break;
        str1++;
        str2++;
    }
    if (*str1 - *str2 > 0)
        return 1;
    else if (*str1 - *str2 < 0)
        return -1;
    else
        return 0;

}

char* custom_strcat(char* _str, const char* strAdd)
{
    char* str = _str;
    while (*str != '\0')
    {
        str++;
    }
    while (1)
    {
        *str = *strAdd;
        if (*strAdd == '\0')
            break;
        strAdd++;
        str++;
    }
    return _str;
}

char* custom_strchr(const char* str, int c)
{
    char* ptr = const_cast<char*>(str);
    while (*ptr != '\0')
    {
        if (*ptr == c)
            return ptr;

        ptr++;
    }
    return nullptr;
}

char* custom_strstr(const char* _str, const char* _strSearch)
{
    char* str = const_cast<char*>(_str);
    char* strSearch = const_cast<char*>(_strSearch);
    while (*str != '\0')
    {
        if (*str == *strSearch)
        {

            char* str2 = str;
            bool flag = true;
            while (*strSearch != '\0')
            {
                if (*str2 != *strSearch)
                {
                    flag = false;
                    break;
                }
                str2++;
                strSearch++;
            }
            if (flag)
                return str;
            strSearch = const_cast<char*>(_strSearch);
        }

        str++;
    }
    return nullptr;
}

char* custom_strlwr(char* _str)
{
    char* str = _str;
    while (*str != '\0')
    {
        if (*str >= 'A' && *str <= 'Z')
            *str += 'a' - 'A';
        str++;
    }
    return _str;
}
