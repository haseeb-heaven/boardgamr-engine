#ifndef BOARDGAMR_H
#define BOARDGAMR_H

/*
BRIEF : (BoardGamr) :  is game-engine to make console board games in c/c++ it provide all the necessary methods to make simple game using
only ASCII characters and provides various types of board,game cards,dice and player modules.
It works with all OS Windows,Mac,Linux etc because it used only standard header files.

*****************************
*******Main Modules.********
*****************************

1)Board-Module --> For Drawing game board, filling board pieces, getting board information.
2)Card-Module --> For Drawing game cards,shuffling/adding/removing deck.
3)Player-Module --> For managing game player turns,score position etc.
4)Dice-Module --> For managing game dice/coins.

*****************************
****Additional components.***
*****************************
5)Font-Module --> For Drawing text on screen with different fonts like making LOGO, printing game score,position data in fancy fonts.
6)Time-Module --> For managing time delays, countdown etc.
7)Misc-Module --> For Utilities like Convert/Fill array, clearing console screen.

AIM : The aim of this engine is only to provide the most efficient way of creating board games with pure c/c++ (no 3rd party library required)
and with portability to any OS (Windows,Mac,Linux).

DOCUMENTATION INFO :
All Public methods are well documented.but private methods are not documented as it was not necessary to do so
see 'docs' folder for whole documentation.

VERSION INFO :
BoardGamr Version : V 1.0

WHATS NEW IN THIS VERSION  v1.0 :
[+]Added All Modules.
[+]Added docs folder.
[+]Added Test folder.
[+]Added FIGlet fonts support.
V 1.0 -> Dated : 23/03/2018


FEATURES : 
1)Fast and flexible modules and methods to create board/player,cards and more.
2)Board module to access,manipulate game boards easily by row/columns/diagonals etc.
3)Player module to access,manipulate player's position/character easily.
4)Card module to add/remove/shuffle/draw game cards easily with deck management. 
5)Dice module to manage game die/dices and coins easily.  
6)Time module to manage game time easily. 
7)Font module to draw fonts that supports FIGlet fonts with no external dependency.
8)Inbuilt tools for converting/filling all type of arrays.
9)Adanced memory efficient design by selecting specific module at compile time.
10)Portable Game engine works any OS (Windows,Mac,Linux) with pure c/c++ (no 3rd party library required).

Written by Ha5eeB Mir (haseebmir.hm@gmail.com)
*/

/*Include all the necessary header files needed.*/
#include <stdio.h>/*For printf,fprintf,vprintf.*/
#include <stdlib.h> /*For rand,system.*/
#include <stdarg.h> /*For va_args.*/
#include <stdbool.h> /*For boolean.*/
#include <string.h>/*For memset.memove*/
#include <time.h> /*For time,clock.*/
#include <ctype.h> /*For isascii,isspace*/
#include <errno.h> /*For errno.*/

/*No module is selected by default. Use 'USE_"ModuleName"_MODULE' macro to select modules you need.
or use 'USE_ALL_MODULES' macro to include all modules.
*/

/*Include All module if selected.*/
#ifdef USE_ALL_MODULES
#define USE_BOARD_MODULE
#define USE_CARD_MODULE
#define USE_PLAYER_MODULE
#define USE_DICE_MODULE
#define USE_FONT_MODULE
#define USE_TIME_MODULE
#define USE_MISC_MODULE
#endif // USE_ALL_MODULES

/*Include Board module if selected.*/
#ifdef USE_BOARD_MODULE
#include "BG_Board.c"
#endif

/*Include Card module if selected.*/
#ifdef USE_CARD_MODULE
#include "BG_Card.c"
#endif

/*Include Player module if selected.*/
#ifdef USE_PLAYER_MODULE
#include "BG_Player.c"
#endif

/*Include Font module if selected.*/
#ifdef USE_FONT_MODULE
#include "BG_Font.c"
#endif

/*Include Time module if selected.*/
#ifdef USE_TIME_MODULE
#include "BG_Time.c"
#endif

/*Include Dice module if selected.*/
#ifdef USE_DICE_MODULE
#include "BG_Dice.c"
#endif

/*Include Miscellaneous module if selected.*/
#ifdef USE_MISC_MODULE
#include "BG_Misc.c"
#endif

/*Show error if no module was selected.*/
#if !defined(USE_BOARD_MODULE) && !defined(USE_CARD_MODULE) \
&& !defined(USE_PLAYER_MODULE) && !defined(USE_FONT_MODULE) \
&& !defined(USE_TIME_MODULE) && !defined(USE_DICE_MODULE) \
&& !defined(USE_MISC_MODULE)
#error No module selected from engine. Must select atleast one module.
#endif

#endif	/* BOARDGAMR_H */
