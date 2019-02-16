#ifndef BG_FONT_H
#define BG_FONT_H

#define USE_MISC_MODULE
#include "BG_Misc.h"
#include "BG_FIGlet.h"
#include "BG_FIGlet.c"

void DrawFont(char *,char *,int,int,bool,bool,bool,bool,bool,bool);
void BG_DrawFontVargsEx(char *,int,char * ,...);
#endif // BG_FONT_H
