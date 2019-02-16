#define USE_DICE_MODULE

#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
#include "..\engine\BoardGamr.h"
#else
#include "../engine/BoardGamr.h"
#endif

int main(void)
{
    BG_EnableLogs();

    int die = BG_RollDie();
    printf("Rolled Die is %d\n",die);

    int dice = BG_RollDice(3);
    printf("Rolled number from 3 dices is %d\n",dice);

    int coin = BG_FlipCoin();
    printf("Flipped coin is %s\n",(coin == HEAD) ? "Heads" : "Tails");

    return 0;
}
