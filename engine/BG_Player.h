#ifndef BG_PLAYER_H
#define BG_PLAYER_H

#define USE_DICE_MODULE
#define USE_MISC_MODULE

#include "BG_Dice.h"
#include "BG_Misc.h"

/*Player Position/Turn related methods.*/
uint BG_GetRandPosition(void);
uint BG_GetRandTurn(int,int);
int BG_GetPlayerTurn(int,int,bool,bool);
float BG_GetScorePercent(int,int);
#endif // BG_PLAYER_H
