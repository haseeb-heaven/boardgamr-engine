#ifndef BG_BOARD_H
#define BG_BOARD_H

#define USE_MISC_MODULE
#include "BG_Misc.h"

/*Board related variables.*/
bool board_invert = FALSE,multi_piece = FALSE,board_border = TRUE;

/*Main Board methods.*/
bool BG_InitGameBoard(int*,int,int,int,int);
void BG_DrawGameBoard(int*,int,int,char*,int,int);
void BG_GetBoardInfo(BG_BoardInfo*,size_t,bool);
int BG_GetPieceInfo(BG_PieceInfo*,size_t,int*,char,bool);

/*Board row and column methods.*/
bool BG_FillBoardRow(int*,int,char);
bool BG_FillBoardRows(int*,int*,char*,size_t);
bool BG_FillBoardCol(int*,int,char);
bool BG_FillBoardCols(int*,int*,char*,size_t);

/*Board diagonal methods.*/
bool BG_FillBoardDiagonal(int*,int,int,char);
bool BG_FillBoardDiagonals(int*,int*,int,char *,size_t);

/*Board properties methods.*/
void BG_InvertBoard(bool);
void BG_MultiPiece(bool);
void BG_BoardBorder(bool);
#endif // BG_BOARD_H
