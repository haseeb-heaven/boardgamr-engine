#define USE_PLAYER_MODULE

#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
#include "..\engine\BoardGamr.h"
#else
#include "../engine/BoardGamr.h"
#endif

int main(void)
{
    BG_EnableLogs();
    int rand_turn = BG_GetRandTurn(10,11);
    printf("Rand Position is %d\n",rand_turn);

    int total_wins = 5,total_games = 13;

    float win_percent = BG_GetScorePercent(total_wins,total_games);
    printf("Win percentage : %.2f\n",win_percent);

    int turn = BG_GetPlayerTurn(COMPUTER_MODE,NUL,FALSE,TRUE);
    printf("%s's turn\n",turn == PLAYER_1 ? "Player" : "Computer");

    for(int i = 2; i <= 4; ++i)
    {
        turn = BG_GetPlayerTurn(FRIEND_MODE,i,TRUE,TRUE);
        printf("PLAYER_%d's turn\n",turn);
    }
    return 0;
}
