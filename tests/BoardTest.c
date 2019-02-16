#define USE_BOARD_MODULE
#define USE_MISC_MODULE
#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
#include "..\engine\BoardGamr.h"
#else
#include "../engine/BoardGamr.h"
#endif

void DrawChessBoard(int,int,int);
void DrawTicTacToeBoard(int,int,int);
void DrawSnakesAndLaddersBoard(int,int,int);
void DrawSudokuBoard(int,int,int);
void FillBoard(int,int,int,int);
void BoardPieceInfoDemo(int);

int main(void)
{
    //BG_EnableLogs();
    AddLog("Create");
    int board_x = 4,board_y = 1,index;
    int chess_grid = 8,tictactoe_gird = 3,snkldr_grid = 10,sudoku_grid = 9,demo_grid = 14;

    int col_num = 1,row_num = 3,ldiag_num = 4,rdiag_num = 6;

    int board_size = demo_grid * demo_grid;
    int game_board[board_size];

    DrawChessBoard(chess_grid,board_x,board_y);
    DrawTicTacToeBoard(tictactoe_gird,board_x,board_y);
    DrawSnakesAndLaddersBoard(snkldr_grid,board_x,board_y);
    DrawSudokuBoard(sudoku_grid,board_x,board_y);

    BoardPieceInfoDemo(demo_grid);
    return 0;
}

void DrawChessBoard(int board_grid,int board_x,int board_y)
{
    enum {B_PIECE_LEN = 2,WHITE_SQUARE = 27, BLACK_SQUARE = 32};

    int board_size = board_grid * board_grid;
    int game_board[board_size];
    printf("\nChess/Checkers board : Grid %dx%d",board_grid,board_grid);
    /*Initialize game board with sequentially with all black blocks.*/
    BG_InitGameBoard(game_board,board_grid,SEQ_INIT,BLACK_SQUARE,NOP_VALUE);

    /*Initialize game board with alternatively with all white blocks.*/
    BG_InitGameBoard(game_board,board_grid,ALT_INIT,WHITE_SQUARE,NOP_VALUE);

    /*Draw alternate game board .*/
    char board_piece[B_PIECE_LEN] = {WHITE_SQUARE,BLACK_SQUARE};
    BG_DrawGameBoard(game_board,board_x,board_y,board_piece,B_PIECE_LEN,ALT_BOARD);
}

void DrawTicTacToeBoard(int board_grid,int board_x,int board_y)
{
    enum {B_PIECE_LEN = 2,CHAR_EMPTY,CROSS,NOUGHT,CHAR_CROSS = 0x58,CHAR_NOUGHT = 0x4F};

    int board_size = board_grid * board_grid;
    int game_board[board_size];
    printf("\nTicTac-Toe-Board board : Grid %dx%d",board_grid,board_grid);

    BG_InitGameBoard(game_board,board_grid,SEQ_INIT,1,INC_VALUE);

    BG_InitGameBoard(game_board,board_grid,RAND_INIT,CHAR_CROSS,NOP_VALUE);
    BG_InitGameBoard(game_board,board_grid,COL_INIT,CHAR_NOUGHT,NOP_VALUE);

    /*Draw sequential game board with no borders .*/
    char board_piece[B_PIECE_LEN] = {CHAR_CROSS,CHAR_NOUGHT};

    BG_BoardBorder(FALSE);
    BG_DrawGameBoard(game_board,board_x,board_y,board_piece,B_PIECE_LEN,SEQ_BOARD);
}

void DrawSnakesAndLaddersBoard(int board_grid,int board_x,int board_y)
{
    enum {B_PIECE_LEN = 11,SNAKE_BODY = 0x6F,SNAKE_HEAD = 94,LADDER_MID = 33,LADDER_BOTTOM = 0x3D,LADDER_TOP = 0x3D,FINISH_PIECE = 36,
          PLAYER1_PIECE = 80,PLAYER2_PIECE = 81,PLAYER3_PIECE = 82,PLAYER4_PIECE = 83,COMPUTER_PIECE = 67
         };


    int board_size = board_grid * board_grid;
    int game_board[board_size];
    printf("\nSnakesAndLadders board : Grid %dx%d",board_grid,board_grid);

    /*Initialize game board sequentially.*/
    BG_InitGameBoard(game_board,board_grid,SEQ_INIT,1,INC_VALUE);

    /*Initialize game board with snakes at random locations.*/
    BG_InitGameBoard(game_board,board_grid,ROW_INIT,SNAKE_HEAD,NOP_VALUE);

    /*Initialize game board with ladders at random locations..*/
    BG_InitGameBoard(game_board,board_grid,COL_INIT,LADDER_MID,NOP_VALUE);

    /*Draw game board in reverse order for this game.*/
    char board_piece[B_PIECE_LEN] = {PLAYER1_PIECE,PLAYER2_PIECE,PLAYER3_PIECE,PLAYER4_PIECE,COMPUTER_PIECE,SNAKE_BODY,SNAKE_HEAD,LADDER_BOTTOM,LADDER_MID,LADDER_TOP,FINISH_PIECE};

    BG_BoardBorder(TRUE); /*Default to TRUE.*/
    BG_DrawGameBoard(game_board,board_x,board_y,board_piece,B_PIECE_LEN,ALT_BOARD);
}

void DrawSudokuBoard(int board_grid,int board_x,int board_y)
{
    int array_index = 0,row_index = 0,cols_index = 0,arr_tmp_index = 0,game_index = 0,index = 0,board_size = board_grid * board_grid,next_row = 0,next_col = 0,dups_removed = TRUE,dups_found = FALSE,rand_value = 0,board_height = 72;
    int game_board[board_size];
    printf("\nSudoku board : Grid %dx%d\n",board_grid,board_grid);

    /*Initialize game board with blank spaces.*/
    BG_InitGameBoard(game_board,board_grid,SEQ_INIT,32,NOP_VALUE);

    /*Initialize game board with random values at random locations.*/
    for(game_index = 0; game_index < board_size; game_index+=BG_RandGenerator(1,0x5))
    {
        game_board[game_index] = BG_RandGenerator(1,board_grid);
    }

    /*Draw sequential game board .*/
    char board_piece[] = {32};
    BG_BoardBorder(TRUE); /*Default to TRUE.*/
    BG_DrawGameBoard(game_board,board_x,board_y,board_piece,1,SEQ_BOARD);
}

void FillBoard(int row_num,int col_num,int ldiag_num,int rdiag_num)
{
#define B_LEN 10
    int game_board[B_LEN * B_LEN] = {NUL};
    BG_InitGameBoard(game_board,B_LEN,SEQ_INIT,NUL,NOP_VALUE);

    char *pieces = "XOP";
    int rows[] = {1,3,4};
    int cols[] = {1,9,3};
    int ldiags[] = {1,8,3};
    int rdiags[] = {2,4,6};

    printf("Row Fill status : %s\n",BG_FillBoardRow(game_board,row_num,'X') == 0 ? "FALSE" : "TRUE");
    printf("Col Fill status : %s\n",BG_FillBoardCol(game_board,col_num,'O') == 0 ? "FALSE" : "TRUE");
    printf("Left Diagonal Fill status : %s\n",BG_FillBoardDiagonal(game_board,ldiag_num,LEFT_DIAG,'L') == 0 ? "FALSE" : "TRUE");
    printf("Right Diagonal  Fill status : %s\n",BG_FillBoardDiagonal(game_board,rdiag_num,RIGHT_DIAG,'R') == 0 ? "FALSE" : "TRUE");

    printf("Rows status : %s\n",BG_FillBoardRows(game_board,rows,pieces,strlen(pieces)) == 0 ? "FALSE" : "TRUE");
    printf("Cols Fill status : %s\n",BG_FillBoardCols(game_board,cols,pieces,strlen(pieces)) == 0 ? "FALSE" : "TRUE");
    printf("Left Diagonals Fill status : %s\n",BG_FillBoardDiagonals(game_board,ldiags,LEFT_DIAG,pieces,strlen(pieces)) == 0 ? "FALSE" : "TRUE");
    printf("Right Diagonals Fill status : %s\n",BG_FillBoardDiagonals(game_board,rdiags,RIGHT_DIAG,pieces,strlen(pieces)) == 0 ? "FALSE" : "TRUE");

    char board_piece[] = {'X','O','P','L','R'};
    BG_DrawGameBoard(game_board,5,1,board_piece,strlen(board_piece),SEQ_BOARD);
}


void BoardPieceInfoDemo(int grid_size)
{
    int index,board_len = grid_size * grid_size,pos;
    int game_board[board_len];

    /*Initialize board sequentially - NOP : No-Operation will be done on value.*/
    BG_InitGameBoard(game_board,grid_size,SEQ_INIT,NUL,NOP_VALUE);

    BG_BoardInfo board_info[grid_size];
    BG_PieceInfo piece_info[board_len];

    /*Get board information in board_info array and print info.*/
    BG_GetBoardInfo(board_info,grid_size,TRUE);

    char board_piece[] = {'X','O','p','*','$'};
    int board_piece_len = sizeof(board_piece)/sizeof(board_piece[0]);

    /*Setting board with pieces with at random locations.*/
    for(index = 0; index < board_piece_len; ++index)
    {
        pos = BG_RandGenerator(NUL,board_len);
        game_board[pos] =   board_piece[index];
    }

    /*Draw game board with all pieces.*/
    BG_DrawGameBoard(game_board,1,1,board_piece,board_piece_len,SEQ_BOARD);

    /*Print board piece info with print info option enabled.*/
    for(index = 0; index < board_piece_len; ++index)
        printf("\n%c found %d times\n",board_piece[index],BG_GetPieceInfo(piece_info,board_len,game_board,board_piece[index],TRUE));
}
