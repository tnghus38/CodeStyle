#pragma once
#ifndef __CUSTOMSTR__
#define __CUSTOMSTR__
int custom_strlen(char* str);
char* custom_strcpy(char* _str, const char* strSrc);
int custom_strcmp(const char* s1, const char* s2);
char* custom_strcat(char* _str, const char* strAdd);
char* custom_strchr(const char* str, int c);
char* custom_strstr(const char* _str, const char* _strSearch);
char* custom_strlwr(char* _str);

#endif