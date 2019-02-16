#include "BG_Font.h"

/****************************************************************************
****************-PUBLIC-MACROS-******************************************
****************************************************************************/

/*Draw font text on screen using FIGlet .
* see https://github.com/cmatsuoka/figlet/blob/master/LICENSE for licensing.
* we use custom FIGlet library called "BG_FIGlet" in which we reduced complexity and improved readability of code.
* but the original code/logic wasn't altered by any means and application still uses its core to draw fonts.
*/

/**
 * @description - Draw the text with provided font.
 * @param -
 * text_str : Text to draw.
 * text_font  : Font of text.
 */
#define BG_DrawFont(...) DrawFont(__VA_ARGS__,BG_DEFAULT_FONT_WIDTH,BG_DEFAULT_FONT_ALIGN,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE)

/**
 * @description - Draw the text with provided font and width.
 * @param -
 * text_str : Text to draw.
 * text_font  : Font of text.
 * text_width  :Width of text. (Defaults to 80).
 */
#define BG_DrawFontEx(...) DrawFont(__VA_ARGS__,BG_DEFAULT_FONT_ALIGN,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE)

/**
 * @description - Draw the text with provided font,width and alignment.
 * @param -
 * text_str : Text to draw on screen.
 * text_font  : Font of text.
 * text_width  : Width of text. (Defaults to 80).
 * text_align  : Alignment of text. Use Enum 'text_ALIGN' to provide values.
 */
#define BG_DrawFontArgs(...) DrawFont(__VA_ARGS__,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE)


/**
 * @description - Draw the text with default attributes (font,width,spacing etc).
 * @param - * text_str : Text to draw on screen.
 */
#define BG_DrawFontDefault(...) DrawFont(__VA_ARGS__,BG_DEFAULT_FONT,BG_DEFAULT_FONT_WIDTH,BG_DEFAULT_FONT_ALIGN,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE)

/**
 * @description - Draw the text from right-to-left
 * @param -
 * text_str : Text to draw.
 * text_font  : Font of text.
 * text_width  :Width of text. (Defaults to 80).
 * text_align  : Automatically selected alignment to right.
 */
#define BG_DrawFontRTL(...) DrawFont(__VA_ARGS__,FONT_RIGHT,TRUE,TRUE,FALSE,FALSE,FALSE,TRUE)

/**
 * @description - Draw the text with provided variable numbers arguments in default fonts and width.
 * @param -
 * __VA_ARGS__ : Variable number of arguments.
 */
#define BG_DrawFontVargs(...)  BG_DrawFontVargsEx(BG_DEFAULT_FONT,BG_DEFAULT_FONT_WIDTH,__VA_ARGS__)


/**
 * @description - Draw the text with provided variable numbers arguments in provided font and width.
 * @param -
  * text_font  : Font of text. (Only FIGlet fonts supported , TOIlet fonts not supported) see '/fonts' directory for list of fonts.
 * text_width  :Width of text. (Defaults to 80).
 * text_fmt : Variable number of arguments.
 */

void BG_DrawFontVargsEx(char *text_font,int text_width,char * text_fmt,...)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\ttext_font : %s\ttext_width : %d\ttext_fmt : %s\n",BG_FUNC,text_font,text_width,text_fmt);
    }

    char font_buf[0x400] = {'\0'};

    /*Error checking for attributes.*/
    if(text_fmt == NULL)
    {
        ShowError("%s -> ERROR : \"No variable number of arguments provided to print. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        return;/*return to caller immediately.*/
    }

    /*Parse text_fmt and place them into font buffer.*/
    va_list arglist;
    va_start( arglist, text_fmt );
    vsprintf(font_buf,text_fmt, arglist );
    va_end( arglist );

    if(IsLogEnabled())
    {
        AddLog("%s -> Parsed fonts arglist\n",BG_FUNC);
        AddLog("%s -> Caliing BG_DrawFontArgs Library to handle the rest of job\n",BG_FUNC);
    }

    /*Use BG_DrawFontArgs Macro to handle the buffer.*/
    BG_DrawFontArgs(font_buf,text_font,text_width,BG_DEFAULT_FONT_ALIGN);

    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully\n",BG_FUNC);
    }
    SetPrivateAccess(FALSE);
}


/****************************************************************************
****************-PRIVATE-METHOD-****************************************
****************************************************************************/

/**
 * NOTE : Don't use this method directly , use BG_DrawFontArgs(),BG_DrawFont(),BG_DrawFontDefault() etc MACROS.
 * Use this method only if you want full control over text with all its attributes like smushing,kerning,merging etc.

 * @description - Draw the text using FIGlet fonts (Main Method.).
 * @param -
 * text_str : Text to draw.
 * text_font  : Font of text. (Only FIGlet fonts supported , TOIlet fonts not supported) see '/fonts' directory for list of fonts.
 * text_width  :Width of text. (Defaults to 80).
 * text_align  : Alignment of text. Use Enum 'text_ALIGN' to provide values. (Defaults to Align Left)
 * text_paragraph  : Whether to use paragraph or not.  Use (TRUE/FALSE) (Defaults to TRUE)
 * text_spacing (Kerning) : Whether to use spacing between characters or not.  Use (TRUE/FALSE) (Defaults to TRUE)
 * text_merged  (Smushing) : Whether to merge text or not . Use (TRUE/FALSE) (Defaults to FALSE)
 * text_full_width  : Whether to use Fonts full width or not . Use (TRUE/FALSE). (Defaults to FALSE)
 * text_overlap  : Whether to overlap text or not . Use (TRUE/FALSE). (Defaults to FALSE)
 * text_rtl  : Is text written from Right-to-Left. Use (TRUE/FALSE). (Defaults to FALSE)
 */

void DrawFont(char *text_str,char *text_font,int text_width,int text_align,bool text_paragraph,bool text_spacing,bool text_merged,bool text_full_width,bool text_overlap,bool text_rtl)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\ttext_str : %s\ttext_font : %s\ttext_width : %d\ttext_align : %d\ttext_paragraph : %s\n",BG_FUNC,text_str,text_font,text_width,text_align,GetBoolAlpha(text_paragraph));
        AddLog("text_spacing : %s\ttext_merged : %s\ttext_full_width : %s\ttext_overlap : %s\ttext_rtl : %s\n",GetBoolAlpha(text_spacing),GetBoolAlpha(text_merged),GetBoolAlpha(text_full_width),GetBoolAlpha(text_overlap),GetBoolAlpha(text_rtl));
    }

    bg_try
    {
        /*Error checking for attributes.*/
        if(text_str == NULL)
        {
            CopyError("%s -> ERROR : \"No text provided to print. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
            SetErrorCode(BG_ERROR);
            bg_throw(GetErrorCode());
        }
        else if(text_font == NULL)
        {
            CopyError("%s -> ERROR : \"No font provided. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
            SetErrorCode(BG_ERROR);
            bg_throw(GetErrorCode());
        }

        if(IsLogEnabled())
        {
            AddLog("%s -> Using FIGlet library calling FIG_DrawFont(text_str), These are not covered by Logs because of private library.\n",BG_FUNC);
        }

        /*Private library not covered by Logs.*/
        FIG_SetAttribs(text_font,text_width,text_spacing,text_merged,text_align,text_overlap,text_full_width,text_paragraph,text_rtl);/*Set all the attributes needed for font.*/
        FIG_ReadFont(); /*Read FIGlet font from /fonts directory.*/
        FIG_LineAlloc(); /*Allocate & clears output_line and in_char_line.*/
        FIG_DrawFont(text_str);/*Draw text using selected font.*/
    }
    bg_catch(bg_error_code)
    {
        ShowError(err_buf);
        SetPrivateAccess(FALSE);
        return;
    }

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully\n",BG_FUNC);
    }
    SetPrivateAccess(FALSE);
}
