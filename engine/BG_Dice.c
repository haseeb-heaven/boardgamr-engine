#include "BG_Dice.h"

/**
 * @description - Flip a coin.
 * @return - Returns Heads or Tails.
 */

uint BG_FlipCoin(void)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called\n",BG_FUNC);
    }

    uint coin = BG_RandGenerator(HEAD,TAIL);

    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,coin);
    }

    SetPrivateAccess(FALSE);
    return coin;
}

/**
 * @description - Roll a single Dice.
 * @return - Returns dice number rolled.
 */

uint BG_RollDie(void)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called\n",BG_FUNC);
    }

    uint die = BG_RandGenerator(DICE_ONE,DICE_SIX);
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,die);
    }
    SetPrivateAccess(FALSE);
    return die;
}

/**
 * @description - Roll multiple Dice.
 * @param - dices : Number of dices to roll.
 * @return - Returns total sum of all dices rolled.
 */

uint BG_RollDice(int n_dice)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tn_dice : %d\n",BG_FUNC,n_dice);
    }

    uint dice_index = 1,dice_count = 0;

    for(dice_index = 1; dice_index <= n_dice; dice_index++)
    {
        dice_count += BG_RandGenerator(DICE_ONE,DICE_SIX);
    }

    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,dice_count);
    }
    SetPrivateAccess(FALSE);
    return dice_count;
}
