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
* [+] Added suffix 'FIG' to all methods to avoid name collision.
* [-] Removed unnecessary methods like readcontrol(),readnum(),suffixcmp() etc
* [-] Removed support for UTF-8 and TOIlet fonts.
* [-] Removed support for German (ISO  646-DE)  character  set and characters mapping in controls.
****************************************************************************/

#include "BG_FIGlet.h"

/****************************************************************************
  FIG_HasDirSeparator

  Returns true if s1 contains a DIRSEP1 or DIRSEP2 character.
****************************************************************************/

int FIG_HasDirSeparator(char *str)
{
    if (strchr(str, DIRSEP1))
        return 1;
    else if (strchr(str, DIRSEP2))
        return 1;
    else
        return 0;
}

/****************************************************************************
  FIG_SkipToEOL

  Skips to the end of a line, given a stream.  Handles \r, \n, or \r\n.
****************************************************************************/

void FIG_SkipToEOL(FILE *fp)
{
    int dummy;

    while (dummy=getc(fp),dummy!=EOF)
    {
        if (dummy == '\n')
            return;
        if (dummy == '\r')
        {
            dummy = getc(fp);
            if (dummy != EOF && dummy != '\n')
                ungetc(dummy,fp);
            return;
        }
    }
}


/****************************************************************************
  FIG_Fgets

  Local version of fgets.  Handles \r, \n, and \r\n terminators.
****************************************************************************/

char *FIG_Fgets(char *line,int max_len,FILE *fp)
{
    int c1 = 0;
    char *p;

    p = line;
    while((c1=getc(fp))!=EOF&&max_len)
    {
        *p++ = c1;
        max_len--;
        if (c1=='\n')
            break;
        if (c1=='\r')
        {
            c1 = getc(fp);
            if (c1 != EOF && c1 != '\n')
                ungetc(c1,fp);
            *(p-1) = '\n';
            break;
        }
    }
    *p = 0;
    return (c1==EOF) ? NULL : line;
}

/****************************************************************************
  FIG_ReadMagic

  Reads a four-character magic string from a stream.
****************************************************************************/
void FIG_ReadMagic(FILE *fp,char *magic)
{
    int i;

    for (i=0; i<4; i++)
    {
        magic[i] = getc(fp);
    }
    magic[4] = 0;
}

/****************************************************************************
  FIG_SkipWS

  Skips whitespace characters from a stream.
****************************************************************************/
void FIG_SkipWS(FILE *fp)
{
    int c1;
    while (c1=getc(fp),isascii(c1)&&isspace(c1)) ;
    ungetc(c1,fp);
}

/****************************************************************************
  FIG_Fopen

  Given a FIGlet font or control file name and suffix, return the file
  or NULL if not found
****************************************************************************/

FILE *FIG_Fopen(char *file_name,char *suffix)
{
    char *font_path;
    FILE *font_file;
    int name_len;

    name_len = FIG_STRLEN(font_dir_name);
    font_path = (char*)alloca(sizeof(char)*
                              (name_len+FIG_STRLEN(file_name)+FIG_STRLEN(suffix)+2));
    font_file = NULL;
    if (!FIG_HasDirSeparator(file_name))    /* not a full path name */
    {
        strcpy(font_path,font_dir_name);
        font_path[name_len] = DIRSEP1;
        font_path[name_len+1] = '\0';
        strcat(font_path,file_name);
        strcat(font_path,suffix);
    }
    else {
    /* just append suffix */
    strcpy(font_path,file_name);
    strcat(font_path,suffix);
    }
    font_file = fopen(font_path,"rb");
    return font_file;
}

/****************************************************************************
  FIG_SetAttribs

  Set all the attributes needed for fonts..
****************************************************************************/

void FIG_SetAttribs(char *text_font_name,int text_width,int text_kern,int text_smush,int text_allign,int text_overlap,int text_full_width,int text_paragraph,int text_r2l)
{
    file_name = BG_FILE;
    strcpy(font_dir_name,DEFAULTFONTDIR);
    AppendRootPath(font_dir_name);
    output_width = text_width;
    font_name = text_font_name;
    justification = text_allign;
    right2left = text_r2l;
    paragraph_flag = text_paragraph;
    smush_mode = (text_full_width) ? 0 : (text_smush || text_overlap) ? SM_SMUSH : SM_KERN;
    smush_override = (text_full_width || text_overlap || text_kern) ? SMO_YES : (text_smush) ? SMO_FORCE : SMO_NO;

    gn[1] = 0x80;
    gr = 1;
    out_line_len_limit = output_width-1;
}

/****************************************************************************
  FIG_ClearLine

  Clears both the input (in_char_line) and output (output_line) storage.
****************************************************************************/

void FIG_ClearLine()
{
    int i;

    for (i=0; i<char_height; i++)
    {
        output_line[i][0] = '\0';
    }
    out_line_len = 0;
    in_char_line_len = 0;
}


/****************************************************************************
  FIG_ReadFontChar

  Reads a font character from the font file, and places it in a
  newly-allocated entry in the list.
****************************************************************************/

void FIG_ReadFontChar(FILE *fp,in_char the_ord)
{
    int row,k;
    char temp_line[MAXLEN+1];
    out_char endchar, out_line[MAXLEN+1];
    fchar_node *fclsave;

    fclsave = fchar_list;
    fchar_list = (fchar_node*)malloc(sizeof(fchar_node));
    fchar_list->ord = the_ord;
    fchar_list->the_char = (out_char**)malloc(sizeof(out_char*)*char_height);
    fchar_list->next = fclsave;

    for (row=0; row<char_height; row++)
    {
        if (FIG_Fgets(temp_line,MAXLEN,fp)==NULL)
        {
            temp_line[0] = '\0';
        }
        strcpy(out_line,temp_line);
        k = FIG_STRLEN(out_line)-1;
        while (k>=0 && isspace(out_line[k]))    /* remove trailing spaces */
        {
            k--;
        }
        if (k>=0)
        {
            endchar = out_line[k];  /* remove endmarks */
            while (k>=0 && out_line[k]==endchar)
            {
                k--;
            }
        }
        out_line[k+1] = '\0';
        fchar_list->the_char[row] = (out_char*)malloc(sizeof(out_char)*(FIG_STRLEN(out_line)+1));
        strcpy(fchar_list->the_char[row],out_line);
    }
}


/****************************************************************************
  FIG_ReadFont

  Allocates memory, initializes variables, and reads in the font.
  Called near beginning of FIG_DrawFont().
****************************************************************************/

void FIG_ReadFont()
{
    int i,row,numsread;
    in_char the_ord;
    int max_len,cmtlines,ffright2left;
    int smush,smush2;
    char fileline[MAXLEN+1],magicnum[5];
    FILE *font_file;
    font_file = FIG_Fopen(font_name,FONTFILESUFFIX);

    if (font_file==NULL)
    {
        fprintf(stderr,"%s: %s: Unable to open font file\n",file_name,font_name);
        exit(1);
    }

    FIG_ReadMagic(font_file,magicnum);
    if (FIG_Fgets(fileline,MAXLEN,font_file)==NULL)
    {
        fileline[0] = '\0';
    }
    if (FIG_STRLEN(fileline)>0 ? fileline[FIG_STRLEN(fileline)-1]!='\n' : 0)
    {
        FIG_SkipToEOL(font_file);
    }
    numsread = sscanf(fileline,"%*c%c %d %*d %d %d %d %d %d",
                      &hard_blank,&char_height,&max_len,&smush,&cmtlines,
                      &ffright2left,&smush2);

    if (max_len > MAXLEN)
    {
        fprintf(stderr,"%s: %s: character is too wide\n",file_name,font_name);
        exit(1);
    }
    if (strcmp(magicnum,FONTFILEMAGICNUMBER) || numsread<5)
    {
        fprintf(stderr,"%s: %s: Not a FIGlet 2 font file\n",file_name,font_name);
        exit(1);
    }
    for (i=1; i<=cmtlines; i++)
    {
        FIG_SkipToEOL(font_file);
    }

    if (numsread<6)
    {
        ffright2left = 0;
    }

    if (numsread<7)   /* if no smush2, decode smush into smush2 */
    {
        if (smush == 0)
            smush2 = SM_KERN;
        else if (smush < 0)
            smush2 = 0;
        else
            smush2 = (smush & 31) | SM_SMUSH;
    }

    if (char_height<1)
    {
        char_height = 1;
    }

    if (max_len<1)
    {
        max_len = 1;
    }

    max_len += 100; /* Give ourselves some extra room */

    if (smush_override == SMO_NO)
        smush_mode = smush2;
    else if (smush_override == SMO_FORCE)
        smush_mode |= smush2;

    if (right2left<0)
    {
        right2left = ffright2left;
    }

    if (justification<0)
    {
        justification = 2*right2left;
    }

    /* Allocate "missing" character */
    fchar_list = (fchar_node*)malloc(sizeof(fchar_node));
    fchar_list->ord = 0;
    fchar_list->the_char = (out_char**)malloc(sizeof(out_char*)*char_height);
    fchar_list->next = NULL;
    for (row=0; row<char_height; row++)
    {
        fchar_list->the_char[row] = (out_char*)malloc(sizeof(out_char));
        fchar_list->the_char[row][0] = '\0';
    }
    for (the_ord=' '; the_ord<='~'; the_ord++)
    {
        FIG_ReadFontChar(font_file,the_ord);
    }
    while (FIG_Fgets(fileline,max_len+1,font_file)==NULL?0:
            sscanf(fileline,"%li",&the_ord)==1)
    {
        FIG_ReadFontChar(font_file,the_ord);
    }
    fclose(font_file);
}


/****************************************************************************
  FIG_LineAlloc

  Allocates & clears output_line, in_char_line. Sets in_char_line_len_limit.
  Called near beginning of FIG_DrawFont().
****************************************************************************/

void FIG_LineAlloc()
{
    int row;

    output_line = (out_char**)malloc(sizeof(out_char*)*char_height);
    for (row=0; row<char_height; row++)
    {
        output_line[row] = (out_char*)malloc(sizeof(out_char)*(out_line_len_limit+1));
    }
    in_char_line_len_limit = output_width*4+100;
    in_char_line = (in_char*)malloc(sizeof(in_char)*(in_char_line_len_limit+1));
    FIG_ClearLine();
}


/****************************************************************************
  FIG_GetLetter

  Sets curr_char to point to the font entry for the given character.
  Sets curr_char_width to the width of this character.
****************************************************************************/

void FIG_GetLetter(in_char c1)
{
    fchar_node *char_ptr;

    for (char_ptr=fchar_list; char_ptr==NULL?0:char_ptr->ord!=c1;
            char_ptr=char_ptr->next) ;
    if (char_ptr!=NULL)
    {
        curr_char = char_ptr->the_char;
    }
    else
    {
        for (char_ptr=fchar_list; char_ptr==NULL?0:char_ptr->ord!=0;
                char_ptr=char_ptr->next) ;
        curr_char = char_ptr->the_char;
    }
    previous_char_width = curr_char_width;
    curr_char_width = FIG_STRLEN(curr_char[0]);
}


/****************************************************************************
  SmushEm

  Given 2 characters, attempts to smush them into 1, according to
  smush_mode.  Returns smushed character or '\FIG_SmushEm' if no smushing can be
  done.
****************************************************************************/

out_char FIG_SmushEm(out_char lch,out_char rch)
{
    if (lch==' ')
        return rch;
    if (rch==' ')
        return lch;

    if (previous_char_width<2 || curr_char_width<2)
        return '\0';
    /* Disallows overlapping if the previous character */
    /* or the current character has a width of 1 or zero. */

    if ((smush_mode & SM_SMUSH) == 0)
        return '\0';  /* kerning */

    if ((smush_mode & 63) == 0)
    {
        /* This is smushing by universal overlapping. */
        if (lch==' ')
            return rch;
        if (rch==' ')
            return lch;
        if (lch==hard_blank)
            return rch;
        if (rch==hard_blank)
            return lch;
        /* Above four lines ensure overlapping preference to */
        /* visible characters. */
        if (right2left==1)
            return lch;
        /* Above line ensures that the dominant (foreground) */
        /* fig-character for overlapping is the latter in the */
        /* user's text, not necessarily the rightmost character. */
        return rch;
        /* Occurs in the absence of above exceptions. */
    }

    if (smush_mode & SM_hard_blank)
    {
        if (lch==hard_blank && rch==hard_blank)
            return lch;
    }

    if (lch==hard_blank || rch==hard_blank)
        return '\0';

    if (smush_mode & SM_EQUAL)
    {
        if (lch==rch)
            return lch;
    }

    if (smush_mode & SM_LOWLINE)
    {
        if (lch=='_' && strchr("|/\\[]{}()<>",rch))
            return rch;
        if (rch=='_' && strchr("|/\\[]{}()<>",lch))
            return lch;
    }

    if (smush_mode & SM_HIERARCHY)
    {
        if (lch=='|' && strchr("/\\[]{}()<>",rch))
            return rch;
        if (rch=='|' && strchr("/\\[]{}()<>",lch))
            return lch;
        if (strchr("/\\",lch) && strchr("[]{}()<>",rch))
            return rch;
        if (strchr("/\\",rch) && strchr("[]{}()<>",lch))
            return lch;
        if (strchr("[]",lch) && strchr("{}()<>",rch))
            return rch;
        if (strchr("[]",rch) && strchr("{}()<>",lch))
            return lch;
        if (strchr("{}",lch) && strchr("()<>",rch))
            return rch;
        if (strchr("{}",rch) && strchr("()<>",lch))
            return lch;
        if (strchr("()",lch) && strchr("<>",rch))
            return rch;
        if (strchr("()",rch) && strchr("<>",lch))
            return lch;
    }

    if (smush_mode & SM_PAIR)
    {
        if (lch=='[' && rch==']')
            return '|';
        if (rch=='[' && lch==']')
            return '|';
        if (lch=='{' && rch=='}')
            return '|';
        if (rch=='{' && lch=='}')
            return '|';
        if (lch=='(' && rch==')')
            return '|';
        if (rch=='(' && lch==')')
            return '|';
    }

    if (smush_mode & SM_BIGX)
    {
        if (lch=='/' && rch=='\\')
            return '|';
        if (rch=='/' && lch=='\\')
            return 'Y';
        if (lch=='>' && rch=='<')
            return 'X';
        /* Don't want the reverse of above to give 'X'. */
    }

    return '\0';
}


/****************************************************************************
  FIG_SmushAmt

  Returns the maximum amount that the current character can be smushed
  into the current line.
****************************************************************************/

int FIG_SmushAmt()
{
    int maxsmush,amt;
    int row,linebd,charbd;
    out_char ch1,ch2;

    if ((smush_mode & (SM_SMUSH | SM_KERN)) == 0)
    {
        return 0;
    }
    maxsmush = curr_char_width;
    for (row=0; row<char_height; row++)
    {
        if (right2left)
        {
            for (charbd=FIG_STRLEN(curr_char[row]);
                    ch1=curr_char[row][charbd],(charbd>0&&(!ch1||ch1==' ')); charbd--) ;
            for (linebd=0; ch2=output_line[row][linebd],ch2==' '; linebd++) ;
            amt = linebd+curr_char_width-1-charbd;
        }
        else
        {
            for (linebd=FIG_STRLEN(output_line[row]);
                    ch1 = output_line[row][linebd],(linebd>0&&(!ch1||ch1==' ')); linebd--) ;
            for (charbd=0; ch2=curr_char[row][charbd],ch2==' '; charbd++) ;
            amt = charbd+out_line_len-1-linebd;
        }
        if (!ch1||ch1==' ')
        {
            amt++;
        }
        else if (ch2)
        {
            if (FIG_SmushEm(ch1,ch2)!='\0')
            {
                amt++;
            }
        }
        if (amt<maxsmush)
        {
            maxsmush = amt;
        }
    }
    return maxsmush;
}


/****************************************************************************
  FIG_AddChar

  Attempts to add the given character onto the end of the current line.
  Returns 1 if this can be done, 0 otherwise.
****************************************************************************/

int FIG_AddChar(in_char c1)
{
    int smush_amount,row,k,column;
    out_char *temp_line;

    FIG_GetLetter(c1);
    smush_amount = FIG_SmushAmt();
    if (out_line_len+curr_char_width-smush_amount>out_line_len_limit
            ||in_char_line_len+1>in_char_line_len_limit)
    {
        return 0;
    }

    temp_line = (out_char*)malloc(sizeof(out_char)*(out_line_len_limit+1));
    for (row=0; row<char_height; row++)
    {
        if (right2left)
        {
            strcpy(temp_line,curr_char[row]);
            for (k=0; k<smush_amount; k++)
            {
                temp_line[curr_char_width-smush_amount+k] =
                    FIG_SmushEm(temp_line[curr_char_width-smush_amount+k],output_line[row][k]);
            }
            strcat(temp_line,output_line[row]+smush_amount);
            strcpy(output_line[row],temp_line);
        }
        else
        {
            for (k=0; k<smush_amount; k++)
            {
                column = out_line_len-smush_amount+k;
                if (column < 0)
                {
                    column = 0;
                }
                output_line[row][column] = FIG_SmushEm(output_line[row][column],curr_char[row][k]);
            }
            strcat(output_line[row],curr_char[row]+smush_amount);
        }
    }
    free(temp_line);
    out_line_len = FIG_STRLEN(output_line[0]);
    in_char_line[in_char_line_len++] = c1;
    return 1;
}


/****************************************************************************
  FIG_PutString

  Prints out the given null-terminated string, substituting blanks
  for hard_blanks.
****************************************************************************/

void FIG_PutString(out_char *str)
{
    int i,len;
    char c1[10];

    len = FIG_STRLEN(str);
    if (output_width>1)
    {
        if (len>output_width-1)
        {
            len = output_width-1;
        }
        if (justification>0)
        {
            for (i=1; (3-justification)*i+len+justification-2<output_width; i++)
            {
                putchar(' ');
            }
        }
    }
    for (i=0; i<len; i++)
    {
        putchar(str[i]==hard_blank?' ':str[i]);
    }
    putchar('\n');
}


/****************************************************************************
  FIG_PrintLine

  Prints output_line using FIG_PutString, then clears the current line.
****************************************************************************/

void FIG_PrintLine()
{
    int i;

    for (i=0; i<char_height; i++)
    {
        FIG_PutString(output_line[i]);
    }
    FIG_ClearLine();
}


/****************************************************************************
  FIG_SplitLine

  Splits in_char_line at the last word break (bunch of consecutive blanks).
  Makes a new line out of the first part and prints it using
  FIG_PrintLine.  Makes a new line out of the second part and returns.
****************************************************************************/

void FIG_SplitLine()
{
    int i,got_space,last_space,len1,len2;
    in_char *part1,*part2;

    part1 = (in_char*)malloc(sizeof(in_char)*(in_char_line_len+1));
    part2 = (in_char*)malloc(sizeof(in_char)*(in_char_line_len+1));
    got_space = 0;
    last_space = in_char_line_len-1;
    for (i=in_char_line_len-1; i>=0; i--)
    {
        if (!got_space && in_char_line[i]==' ')
        {
            got_space = 1;
            last_space = i;
        }
        if (got_space && in_char_line[i]!=' ')
        {
            break;
        }
    }
    len1 = i+1;
    len2 = in_char_line_len-last_space-1;
    for (i=0; i<len1; i++)
    {
        part1[i] = in_char_line[i];
    }
    for (i=0; i<len2; i++)
    {
        part2[i] = in_char_line[last_space+1+i];
    }
    FIG_ClearLine();
    for (i=0; i<len1; i++)
    {
        FIG_AddChar(part1[i]);
    }
    FIG_PrintLine();
    for (i=0; i<len2; i++)
    {
        FIG_AddChar(part2[i]);
    }
    free(part1);
    free(part2);
}

/****************************************************************************
  FIG_ISO2022

  Called by FIG_GetChar.  Interprets ISO 2022 sequences
******************************************************************************/

in_char FIG_ISO2022()
{
    in_char ch;
    in_char ch2;
    int save_gl;
    int save_gr;

    ch = getchar();
    if (ch == EOF)
        return ch;
    if (ch == 27)
        ch = getchar() + 0x100; /* ESC x */
    if (ch == 0x100 + '$')
        ch = getchar() + 0x200; /* ESC $ x */
    switch (ch)
    {
    case 14: /* invoke G1 into GL */
        gl = 1;
        return FIG_ISO2022();
    case 15: /* invoke G0 into GL */
        gl = 0;
        return FIG_ISO2022();
    case 142:
    case 'N' + 0x100: /* invoke G2 into GL for next char */
        save_gl = gl;
        save_gr = gr;
        gl = gr = 2;
        ch = FIG_ISO2022();
        gl = save_gl;
        gr = save_gr;
        return ch;
    case 143:
    case 'O' + 0x100: /* invoke G3 into GL for next char */
        save_gl = gl;
        save_gr = gr;
        gl = gr = 3;
        ch = FIG_ISO2022();
        gl = save_gl;
        gr = save_gr;
        return ch;
    case 'n' + 0x100: /* invoke G2 into GL */
        gl = 2;
        return FIG_ISO2022();
    case 'o' + 0x100: /* invoke G3 into GL */
        gl = 3;
        return FIG_ISO2022();
    case '~' + 0x100: /* invoke G1 into GR */
        gr = 1;
        return FIG_ISO2022();
    case '}' + 0x100: /* invoke G2 into GR */
        gr = 2;
        return FIG_ISO2022();
    case '|' + 0x100: /* invoke G3 into GR */
        gr = 3;
        return FIG_ISO2022();
    case '(' + 0x100: /* set G0 to 94-char set */
        ch = getchar();
        if (ch == 'B')
            ch = 0; /* ASCII */
        gn[0] = ch << 16;
        gndbl[0] = 0;
        return FIG_ISO2022();
    case ')' + 0x100: /* set G1 to 94-char set */
        ch = getchar();
        if (ch == 'B')
            ch = 0;
        gn[1] = ch << 16;
        gndbl[1] = 0;
        return FIG_ISO2022();
    case '*' + 0x100: /* set G2 to 94-char set */
        ch = getchar();
        if (ch == 'B')
            ch = 0;
        gn[2] = ch << 16;
        gndbl[2] = 0;
        return FIG_ISO2022();
    case '+' + 0x100: /* set G3 to 94-char set */
        ch = getchar();
        if (ch == 'B')
            ch = 0;
        gn[3] = ch << 16;
        gndbl[3] = 0;
        return FIG_ISO2022();
    case '-' + 0x100: /* set G1 to 96-char set */
        ch = getchar();
        if (ch == 'A')
            ch = 0; /* Latin-1 top half */
        gn[1] = (ch << 16) | 0x80;
        gndbl[1] = 0;
        return FIG_ISO2022();
    case '.' + 0x100: /* set G2 to 96-char set */
        ch = getchar();
        if (ch == 'A')
            ch = 0;
        gn[2] = (ch << 16) | 0x80;
        gndbl[2] = 0;
        return FIG_ISO2022();
    case '/' + 0x100: /* set G3 to 96-char set */
        ch = getchar();
        if (ch == 'A')
            ch = 0;
        gn[3] = (ch << 16) | 0x80;
        gndbl[3] = 0;
        return FIG_ISO2022();
    case '(' + 0x200: /* set G0 to 94 x 94 char set */
        ch = getchar();
        gn[0] = ch << 16;
        gndbl[0] = 1;
        return FIG_ISO2022();
    case ')' + 0x200: /* set G1 to 94 x 94 char set */
        ch = getchar();
        gn[1] = ch << 16;
        gndbl[1] = 1;
        return FIG_ISO2022();
    case '*' + 0x200: /* set G2 to 94 x 94 char set */
        ch = getchar();
        gn[2] = ch << 16;
        gndbl[2] = 1;
        return FIG_ISO2022();
    case '+' + 0x200: /* set G3 to 94 x 94 char set */
        ch = getchar();
        gn[3] = ch << 16;
        gndbl[3] = 1;
        return FIG_ISO2022();
    default:
        if (ch & 0x200)   /* set G0 to 94 x 94 char set (deprecated) */
        {
            gn[0] = (ch & ~0x200) << 16;
            gndbl[0] = 1;
            return FIG_ISO2022();
        }
    }

    if (ch >= 0x21 && ch <= 0x7E)   /* process GL */
    {
        if (gndbl[gl])
        {
            ch2 = getchar();
            return gn[gl] | (ch << 8) | ch2;
        }
        else
            return gn[gl] | ch;
    }
    else if (ch >= 0xA0 && ch <= 0xFF)   /* process GR */
    {
        if (gndbl[gr])
        {
            ch2 = getchar();
            return gn[gr] | (ch << 8) | ch2;
        }
        else
            return gn[gr] | (ch & ~0x80);
    }
    else
        return ch;
}

/****************************************************************************
  FIG_UngetChar

  Called by FIG_DrawFont.  Pushes back an "in_char" to be read by FIG_GetChar
  on the next call.
******************************************************************************/
in_char getinchar_buffer;
int getinchar_flag;

in_char FIG_UngetChar(in_char c1)
{
    getinchar_buffer = c1;
    getinchar_flag = 1;
    return c1;
}

/*****************************************************************************
  FIG_GetChar

  Called by FIG_DrawFont.  Processes multibyte characters.  Invokes getchar.
*****************************************************************************/

in_char FIG_GetChar()
{
    int ch, ch2, ch3, ch4, ch5, ch6;

    if (getinchar_flag)
    {
        getinchar_flag = 0;
        return getinchar_buffer;
    }

    switch(multi_byte)
    {
    case 0: /* single-byte */
        return FIG_ISO2022();
    case 1: /* DBCS */
        ch = getchar();
        if ((ch >= 0x80 && ch <= 0x9F) ||
                (ch >= 0xE0 && ch <= 0xEF))
        {
            ch = (ch << 8) + getchar();
        }
        return ch;
    case 2: /* UTF-8 */
        ch = getchar();
        if (ch < 0x80)
            return ch;  /* handles EOF, too */
        if (ch < 0xC0 || ch > 0xFD)
            return 0x0080;  /* illegal first character */
        ch2 = getchar() & 0x3F;
        if (ch < 0xE0)
            return ((ch & 0x1F) << 6) + ch2;
        ch3 = getchar() & 0x3F;
        if (ch < 0xF0)
            return ((ch & 0x0F) << 12) + (ch2 << 6) + ch3;
        ch4 = getchar() & 0x3F;
        if (ch < 0xF8)
            return ((ch & 0x07) << 18) + (ch2 << 12) + (ch3 << 6) + ch4;
        ch5 = getchar() & 0x3F;
        if (ch < 0xFC)
            return ((ch & 0x03) << 24) + (ch2 << 18) + (ch3 << 12) +
                   (ch4 << 6) + ch5;
        ch6 = getchar() & 0x3F;
        return ((ch & 0x01) << 30) + (ch2 << 24) + (ch3 << 18) +
               (ch4 << 12) + (ch5 << 6) + ch6;
    case 3: /* HZ */
        ch = getchar();
        if (ch == EOF)
            return ch;
        if (hzmode)
        {
            ch = (ch << 8) + getchar();
            if (ch == ('}' << 8) + '~')
            {
                hzmode = 0;
                return FIG_GetChar();
            }
            return ch;
        }
        else if (ch == '~')
        {
            ch = getchar();
            if (ch == '{')
            {
                hzmode = 1;
                return FIG_GetChar();
            }
            else if (ch == '~')
            {
                return ch;
            }
            else
            {
                return FIG_GetChar();
            }
        }
        else
            return ch;
    case 4: /* Shift-JIS */
        ch = getchar();
        if ((ch >= 0x80 && ch <= 0x9F) ||
                (ch >= 0xE0 && ch <= 0xEF))
        {
            ch = (ch << 8) + getchar();
        }
        return ch;
    default:
        return 0x80;
    }
}

/****************************************************************************
  FIG_DrawFont

  FIG_DrawFont - Given text it draws whole text on screen. Handles line breaking, (which accounts for most of the
  complexity in this function).
****************************************************************************/

void FIG_DrawFont(const char *font_text)
{
    in_char c1,c2;
    int i=0;
    int last_was_eol_flag;
    int word_break_mode;
    int char_not_added;

    word_break_mode = 0;
    last_was_eol_flag = 0;

    for(i = 0; i < strlen(font_text); i++)
    {
        c1 = font_text[i];
        if (c1=='\n'&&paragraph_flag&&!last_was_eol_flag)
        {
            FIG_UngetChar(c2 = FIG_GetChar());
            c1 = ((isascii(c2)&&isspace(c2))?'\n':' ');
        }
        last_was_eol_flag = (isascii(c1)&&isspace(c1)&&c1!='\t'&&c1!=' ');

        if (isascii(c1)&&isspace(c1))
        {
            c1 = (c1=='\t'||c1==' ') ? ' ' : '\n';
        }

        if ((c1>'\0' && c1<' ' && c1!='\n') || c1==127)
            continue;

        /*
          Note: The following code is complex and thoroughly tested.
          Be careful when modifying!
        */

        do
        {
            char_not_added = 0;

            if (word_break_mode== -1)
            {
                if (c1==' ')
                {
                    break;
                }
                else if (c1=='\n')
                {
                    word_break_mode = 0;
                    break;
                }
                word_break_mode = 0;
            }

            if (c1=='\n')
            {
                FIG_PrintLine();
                word_break_mode = 0;
            }

            else if (FIG_AddChar(c1))
            {
                if (c1!=' ')
                {
                    word_break_mode = (word_break_mode>=2)?3:1;
                }
                else
                {
                    word_break_mode = (word_break_mode>0)?2:0;
                }
            }

            else if (out_line_len==0)
            {
                for (i=0; i<char_height; i++)
                {
                    if (right2left && output_width>1)
                    {
                        FIG_PutString(curr_char[i]+FIG_STRLEN(curr_char[i])-out_line_len_limit);
                    }
                    else
                    {
                        FIG_PutString(curr_char[i]);
                    }
                }
                word_break_mode = -1;
            }

            else if (c1==' ')
            {
                if (word_break_mode==2)
                {
                    FIG_SplitLine();
                }
                else
                {
                    FIG_PrintLine();
                }
                word_break_mode = -1;
            }

            else
            {
                if (word_break_mode>=2)
                {
                    FIG_SplitLine();
                }
                else
                {
                    FIG_PrintLine();
                }
                word_break_mode = (word_break_mode==3)?1:0;
                char_not_added = 1;
            }
        }
        while (char_not_added);
    }

    if (out_line_len!=0)
    {
        FIG_PrintLine();
    }
}
