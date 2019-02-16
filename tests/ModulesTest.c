#define USE_ALL_MODULES

#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
#include "..\engine\BoardGamr.h"
#else
#include "../engine/BoardGamr.h"
#endif

int main(void)
{
    int errcode;
    /*Board Module - TEST.*/
    int game_board[100];
    BG_InitGameBoard(game_board,10,SEQ_INIT,1,INC_VALUE);

    printf("Game board\n");
    BG_DrawGameBoard(game_board,1,1,NULL,NUL,SEQ_BOARD);

    /*Card Module - TEST.*/
    Card deck[QUARTER_DECK+1] = {'\0',NUL};

    BG_GetDeck(deck);
    printf("\nGame cards\n");
    BG_DrawDeck(deck);
    BG_DisableLogs();

    BG_EnableLogs();
     /*Player Module - TEST.*/
    int turn = BG_GetPlayerTurn(COMPUTER_MODE,NUL,FALSE,TRUE);
    printf("%s's turn\n\n",turn == PLAYER_1 ? "Player" : "Computer");

     /*Dice Module - TEST.*/
    int die = BG_RollDie();
    printf("Rolled Die is %d\n",die);

    bg_try{
     /*Font Module - TEST.*/
    char *logo_str = "BoardGamr";
    /*Draw LOGO in Georgia11 font with 150 width.*/
    BG_DrawFontEx(logo_str,"Georgia11",150);

    if(logo_str == NULL)
    {
        bg_throw(BG_ERROR);
    }


    /*Time Module - TEST.*/
    printf("This is time delay of... ");
    BG_TimeDelay(2500);
    printf("%0.2f seconds.\n",((float)2500/1000));
    BG_DisableLogs();

    /*Misc Module - TEST.*/
    int clen = 10;char carr[clen],cval = 'x';
    BG_FillArray(carr,clen,NUL,&cval,CHAR_TYPE); /*Fill Character array with 'a'*/
    puts(carr);

    }
    bg_catch(errcode)
    {
        printf("Error is %d\n",errcode);
    }
    return 0;
}


