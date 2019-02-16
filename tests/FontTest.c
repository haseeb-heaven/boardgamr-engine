#define USE_FONT_MODULE
#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
#include "..\engine\BoardGamr.h"
#else
#include "../engine/BoardGamr.h"
#endif

void DrawFontDemo(char *);

int main(void)
{
    char *logo_str = "BoardGamr";
    DrawFontDemo(logo_str);
    return 0;
}

void DrawFontDemo(char *logo_str)
{
    /*Draw LOGO in default font width and default alignment.*/
    BG_DrawFontDefault(logo_str);

    /*Draw LOGO in Georgia11 font with default width and default alignment.*/
    BG_DrawFont(logo_str,"Georgia11");

    /*Draw LOGO in DOH font with 150 width aligned left.*/
    BG_DrawFontArgs(logo_str,"Doh",150,FONT_LEFT);

    /*Draw LOGO in Georgia11 font with 100 width and default alignment.*/
    BG_DrawFontEx(logo_str,"Georgia11",100);

    /*Draw LOGO from RTL [Right-To-Left] in Colossal font with default width and default alignment.*/
    BG_DrawFontRTL(logo_str,"Colossal",BG_DEFAULT_FONT_WIDTH);

    /*Draw LOGO in default font,width,alignment with variable number of arguments.*/
    BG_DrawFontVargs("Line no : %d\n",BG_LINE);

    /*Draw LOGO in Big font with 100 width and default alignment with variable number of arguments.*/
    BG_DrawFontVargsEx("Slant",100,"Line no : %d\n",BG_LINE);
}
