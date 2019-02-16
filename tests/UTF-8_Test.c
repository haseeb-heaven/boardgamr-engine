#include<stdio.h>
#include <wchar.h>
#include <locale.h>

int main(void)
{
    setlocale(LC_ALL,"UTF-8");/*Set encoding to UTF-8. Arg "C" or "POSIX" might still work in some OS.*/

    puts("ASCII CHARS -- STARTS");
    for (wchar_t ch = 0; ch <= 0xFF; ch++){
         if (ch == 0x7F) puts("E-ASCII CHARS -- STARTS");
        wprintf(L"U+%04X = %c\n", ch, (wchar_t)ch);
    }
    return 0;
}
