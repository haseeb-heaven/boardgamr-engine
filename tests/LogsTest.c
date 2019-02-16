#define USE_MISC_MODULE
#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
#include "..\engine\BoardGamr.h"
#else
#include "../engine/BoardGamr.h"
#endif

int main(void)
{
    int x = 10;
    float f = 3.5f;
    char c = 'x';
    char *str = "My string";

    BG_EnableLogs(TRUE);
    SetPrivateAccess(TRUE);
    AddLog("Error : x : %d\tf : %f\tchar  %c\tStr : %s\n",x,f,c,str);
    AddLog("Logs added success");
    return 0;
}
