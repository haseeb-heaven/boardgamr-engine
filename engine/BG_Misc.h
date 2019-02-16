#ifndef BG_MISC_H
#define BG_MISC_H

#include "BG_Const.h"

/*Misc related methods.*/
void BG_FillArray(void*,uint,size_t,void*,int);
void* BG_ConvertArray(void *,void *,uint);
uint BG_RandGenerator(uint,uint);
void BG_ClearScreen();
bool BG_EnableLogs();
bool BG_DisableLogs();

/*Private methods not recommended to use directly.*/
void AppendRootPath(char *);
void CopyError(const char *, ...);
void ShowError(const char *,...);
void SetErrorCode(int);
int GetErrorCode();
void AddLog(const char *, ...);
bool FileExist(const char *);
bool IsLogEnabled();
bool IsPrivateMethod(const char*, int);
void SetPrivateAccess(bool);
char *GetBoolAlpha(bool);
#endif // BG_MISC_H
