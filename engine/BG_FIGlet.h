#ifndef BG_FIGLET_H
#define BG_FIGLET_H

/****************************************************************************
Copyright (C) 1991, 1993, 1994 Glenn Chappell and Ian Chai
Copyright (C) 1996, 1997, 1998, 1999, 2000, 2001 John Cowan
Copyright (C) 2002 Christiaan Keet
Copyright (C) 2011 Claudio Matsuoka
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. Neither the name of the copyright holders nor the names of their
   contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
****************************************************************************/

/****************************************************************************
* MODIFIED VERSION OF FIGLET see https://github.com/cmatsuoka/figlet/blob/master/LICENSE
* for licensing. and check http://www.figlet.org/figlet-man.html for detailed manual  page.
* [+] Added new methods FIG_DrawFont(),FIG_SetAttribs() for setting font attributes and drawing fonts.
* [+] Converted application from command line to argument based.
* [+] Added sufix 'FIG' to all methods to avoid name collision.
* [-] Removed unnecessary methods like readcontrol,readnum,suffixcmp etc
* [-] Removed support for UTF-8 and TOIlet fonts.
* [-] Removed charsets like German (ISO  646-DE)  character  set.
* [-] Removed support for German characters and characters mapping in controls.
****************************************************************************/

/*FIGLET Skip methods.*/
void FIG_SkipToEOL(FILE *);
void FIG_SkipWS(FILE *);

/*FIGLET Read methods.*/
char *FIG_Fgets(char *,int,FILE *);
void FIG_ReadMagic(FILE *,char *);
FILE *FIG_Fopen(char *,char *);
void FIG_ReadFontChar(FILE *,in_char);
void FIG_ReadFont();
void FIG_GetLetter(in_char);

/*FIGLET Line methods.*/
void FIG_ClearLine();
void FIG_LineAlloc();
void FIG_PrintLine();
void FIG_SplitLine();

/*FIGLET Smush methods.*/
out_char FIG_SmushEm(out_char,out_char);
int FIG_SmushAmt();

/*FIGLET Char methods.*/
int FIG_AddChar(in_char);
in_char FIG_GetChar();
in_char FIG_UngetChar(in_char);

/*FIGLET Print methods.*/
void FIG_PutString(out_char *);
void FIG_DrawFont(const char *);

/*FIGLET Attributes methods.*/
void FIG_SetAttribs(char *,int,int,int,int,int,int,int,int);

/*FIGLET Misc methods.*/
in_char FIG_ISO2022();
int FIG_HasDirSeparator(char *str);
#endif // BG_FIGLET
