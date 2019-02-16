#include "BG_Board.h"

/* NOTE : This engine assumes that you have 1D-Array for your game board.
* if you are using 2D-Array for your game board then use the convert utility
* Utility name : 'BG_ConvertArray()'
* Module name : 'BG_MISC'
*/

/**
 * @description - Initialize the game board.
 * @param -
 * game_board : Pointer to variable in which game board is stored.
 * grid_size : size of game board grid ex [3x3] or [9x9]. Provide only row or col like '3' for [3x3] grid or '9' for [9x9] grid.
 * init_type : Initialize board sequentially,alternate or Row/Col wise values, Use Enum BOARD_INIT for more information.
 * init_value : Initialize board with this value. [Parameter is ignored when value_type is RAND_VALUE].
 * value_type : Type of value like Incremented/Decremented or plain value. Use Enum VALUE_TYPE for more information.
 * @return - If initialize was success it returns TRUE otherwise returns FALSE.
 */

bool BG_InitGameBoard(int *game_board,int grid_size,int init_type,int init_value,int value_type)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        char *init_type_str = (init_type == SEQ_INIT) ? "SEQ_INIT" : (init_type == ALT_INIT) ? "ALT_INIT"  : (init_type == RAND_INIT) ? "RAND_INIT" : (init_type == ROW_INIT) ? "ROW_INIT"  : (init_type == COL_INIT) ? "COL_INIT" : "UNKNOWN_INIT";
        char *value_type_str = (value_type == NOP_VALUE) ? "NOP_VALUE" : (value_type == INC_VALUE) ? "INC_VALUE"  : (value_type == DEC_VALUE) ? "DEC_VALUE" : (value_type == RAND_VALUE) ? "RAND_VALUE"  : "UNKNOWN_TYPE";
        AddLog("%s -> called with arguments\tgame_board : %p\tgrid_size : %d\tinit_type : %s\tinit_value : %d\tvalue_type : %s\n",BG_FUNC,game_board,grid_size,init_type_str,init_value,value_type_str);
    }

    uint  index = 0;
    int b_index = 0,g_index = 0,grid_line = 0,grid_count = 2, grid_index = 0,grid_run = FALSE,board_index = 0,board_size = grid_size * grid_size;
    int board_cols = grid_size,board_rows = grid_size;
    bool init_status = FALSE;

    bg_grid_size = grid_size;
    bg_board_size  = bg_grid_size * bg_grid_size;

    /*Error checking for parameters.*/
    if(value_type < NOP_VALUE || value_type > RAND_VALUE)
    {
        ShowError("\n%s -> ERROR : \"Game board not initialized invalid option provided for value_type. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        init_status = FALSE;
    }

    else if(game_board == NULL)
    {
        ShowError("\n%s -> ERROR : \"No game board provided in parameter. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        init_status = FALSE;
    }

    else if(grid_size < GRID_MIN || grid_size > GRID_MAX)
    {
        ShowError("\n%s -> ERROR : \"Grid size '%d' must be in range [%d - %d]. Occurred at line no : %d\"\n",BG_FUNC,grid_size,GRID_MIN,GRID_MAX,BG_LINE);
        init_status = FALSE;
    }

    else
    {
        /*Initialize boards at sequential index locations.*/
        if(init_type == SEQ_INIT)
        {
            for(index = 0; index < board_size; index++)
            {
                game_board[index] = (value_type == NOP_VALUE) ? init_value : (value_type == INC_VALUE) ? init_value++: (value_type == DEC_VALUE) ? init_value-- : BG_ERROR;
            }
            init_status = TRUE;
        }

        /*Initialize boards at alternate index locations (Works with Columns init also).*/
        else if(init_type == ALT_INIT || init_type == COL_INIT)
        {
            for(index = 0; index < board_size; index += ALT_CONST)
            {
                game_board[index] = (value_type == NOP_VALUE) ? init_value : (value_type == INC_VALUE) ? init_value++: (value_type == DEC_VALUE) ? init_value-- : BG_ERROR;
            }
            init_status = TRUE;
        }

        /*Initialize board at random index locations.*/
        else if(init_type == RAND_INIT)
        {
            for(index = 0; index < board_size; index = BG_RandGenerator(NUL,board_size))
            {
                game_board[index] = (value_type == NOP_VALUE) ? init_value : (value_type == INC_VALUE) ? init_value++: (value_type == DEC_VALUE) ? init_value-- : (value_type == RAND_VALUE) ? BG_RandGenerator(NUL,board_size) : BG_ERROR;
            }
            init_status = TRUE;
        }

        /*Initialize board at row index locations.*/
        else if(init_type == ROW_INIT)
        {
            for(index = 0; index < board_size; index++)
            {
                index += (index % bg_grid_size == 0) ? board_rows : 0;
                game_board[index] = (value_type == NOP_VALUE) ? init_value : (value_type == INC_VALUE) ? init_value++: (value_type == DEC_VALUE) ? init_value-- : BG_ERROR;
            }
            init_status = TRUE;
        }

        else
        {
            ShowError("\n%s -> ERROR : \"Game board not initialized invalid option provided for init_type. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
            init_status = FALSE;
        }
    }

    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,init_status);
    }
    SetPrivateAccess(FALSE);
    return init_status;
}

/**
 * @description - Draw the game board.
 * @param -
 * game_board : Pointer to variable in which game board is stored.
 * board_x : X-Position of board.
  * board_y : Y-Position of board.
  * board_pieces : Array of board pieces to show on board like ('X' or 'O' in TicTacToe) and so on.
  * board_pieces_len : Length of game board pieces array.
  * board_type : Type of board to draw sequential or alternate, Use Enum BOARD_TYPE to provide values.
 */

void BG_DrawGameBoard(int *game_board,int board_x,int board_y,char* board_pieces,int board_pieces_len,int board_type)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        char *board_type_str = (board_type == SEQ_BOARD) ? "SEQ_BOARD" : (board_type == ALT_BOARD) ? "ALT_BOARD" : "UNKNOWN_BOARD";
        AddLog("%s -> called with arguments\tgame_board : %p\tboard_x : %d\tboard_y : %d\tboard_pieces : %p\tboard_pieces_len : %d\tboard_type : %s\n",BG_FUNC,game_board,board_x,board_y,board_pieces,board_pieces_len,board_type_str);
    }

    int g_index = 0,board_index = 0,xy_index = 0,piece_index = 0,cell_index = 0,r_edge = 1,l_edge = 1,grid_line = 0,grid_count = 2, grid_index = 0,index = 0;
    bool piece_bool = FALSE,grid_run = FALSE;
    int board_cols = bg_grid_size,board_rows = bg_grid_size;
    int  b_index = 0,grid_liner = 0;

    /*Error checking for parameters.*/
    if(bg_grid_size == NUL)
    {
        ShowError("\n%s -> ERROR : \"Use BG_InitGameBoard() method to initialize game board first!. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        return;/*return to caller immediately.*/
    }

    else if(bg_grid_size < GRID_MIN || bg_grid_size > GRID_MAX)
    {
        ShowError("\n%s -> ERROR : \"Grid size '%d' must be in range [%d - %d]. Occurred at line no : %d\"\n",BG_FUNC,bg_grid_size,GRID_MIN,GRID_MAX,BG_LINE);
        return;/*return to caller immediately.*/
    }

    else if(game_board == NULL)
    {
        ShowError("\n%s -> ERROR : \"No game board provided in parameter. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        return;/*return to caller immediately.*/
    }

    /*Move Upper board to Y-Position.*/
    for(xy_index = 1; xy_index <= board_y; ++xy_index)
        printf("\n");

    /*Main loop for drawing game board.*/
    for(board_index = (board_invert ? bg_board_size -1 : 0); (board_invert ? board_index >= 0 : board_index < bg_board_size) ; (board_invert ?  board_index-- : board_index++))
    {
        /*Upper board section.*/
        if( ((board_invert ? board_index + 1 : board_index) % board_rows == 0))
        {
            printf("\n");

            /*Move Upper board to X-Position.*/
            for(xy_index = 1; xy_index <= board_x; ++xy_index)
                printf("\t");

            if(board_border)
            {
                if(l_edge)
                {
                    putchar(UPPER_LEFT);
                    l_edge = 0;
                }

                (grid_line > 0) ? putchar(LOWER_LEFT) : NUL;

                for(cell_index = 1; cell_index < (board_rows * BOARD_CELL_WIDTH); ++cell_index)
                {
                    putchar(HORIZONTAL_BAR);
                }

                (grid_line > 0) ? putchar(LOWER_RIGHT) : NUL;

                if(r_edge)
                {
                    putchar(UPPER_RIGHT);
                    r_edge = 0;
                }
            }

            printf("\n");
            /*Move board to X-Position.*/
            for(xy_index = 1; xy_index <= board_x; ++xy_index)
                printf("\t");

            putchar(VERTICAL_BAR);
            grid_line++;
        }

        /*Alternate board.*/
        if(board_type == ALT_BOARD)
        {
            if(grid_line == grid_count)
            {
                grid_index = b_index = (board_invert) ? board_index+1 : board_index-1;
                grid_index = (board_invert) ? (grid_index - bg_grid_size) : (grid_index + bg_grid_size);
                grid_count +=ALT_CONST;
                grid_run = TRUE;
            }
            grid_run = (grid_index == b_index) ? FALSE : grid_run;
            grid_index = (grid_run == TRUE) ? (board_invert ? grid_index+1 : grid_index-1) : (board_invert ? board_index+1 : board_index-1);

            g_index = board_index;
            board_index = (board_invert ? grid_index-1 : grid_index+1);
        }

        /*Draw game board_piece characters.*/
        for(piece_index = 0; piece_index < board_pieces_len; ++piece_index)
        {
            if(game_board[board_index] == (board_pieces[piece_index] & 0x7F))
            {
                (multi_piece) ?
                printf(" %c%c %c",game_board[board_index],game_board[board_index],VERTICAL_BAR)
                : printf(" %c  %c",game_board[board_index],VERTICAL_BAR);
                piece_bool = TRUE;
                break;
            }
        }

        if(game_board[board_index] >= BOARD_DIGITS_SIZE && !piece_bool)
        {
            printf("%d %c",game_board[board_index],VERTICAL_BAR);
        }

        else if(!piece_bool)
        {
            printf(" %02d %c",game_board[board_index],VERTICAL_BAR);
        }

        piece_bool = FALSE;
        board_index = (board_type == ALT_BOARD) ?  g_index : board_index;
    }

    /*Lower board section.*/
    if(board_border)
    {
        printf("\n");
        /*Move Lower board to X-Position.*/
        for(xy_index = 1; xy_index <= board_x; ++xy_index)
            printf("\t");

        putchar(LOWER_LEFT);
        for(cell_index = 1; cell_index < (board_rows * BOARD_CELL_WIDTH); ++cell_index)
        {
            putchar(HORIZONTAL_BAR);
        }
        putchar(LOWER_RIGHT);
    }
    printf("\n");

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully\n",BG_FUNC);
    }
    SetPrivateAccess(FALSE);
}


/**
 * @description - Get board information such as Rows,Columns,diagonals. start/end positions or length etc..
  * @param - board_info  [output]: Array to receive information of board . Must be of type 'BG_BoardInfo'.
  * pieces_len [input] : Length of 'board_info' array. Must be in range [1 to GridSize].
  * print_info [input] : Print information of board rows,cols and diagonals or not . Use TRUE or FALSE.
 */

void BG_GetBoardInfo(BG_BoardInfo* board_info,size_t pieces_len,bool print_info)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tboard_info : %p\tpieces_len : %d\tprint_info : %s\n",BG_FUNC,board_info,pieces_len,GetBoolAlpha(print_info));
    }

    int bg_not_found = BG_NOT_FOUND,index = 0,row_index = 0,col_index = 0,diag_index = 0,left_diag_index = 0,right_diag_index = 0;
    int row_start = 0,row_end = 0,row_num = 0;
    int col_start = 0,col_end = 0,col_num = 0;
    int left_diag_start = 0,left_diag_end = 0,left_diag_num = 0,left_diag_len = 0;
    int right_diag_start = 0,right_diag_end = 0,right_diag_num = 0,right_diag_len = 0;
    int diag_row_end = 0,diag_col_end = 0;
    bool is_next_row = FALSE;

    /*Error checking for parameters.*/
    if(bg_grid_size == NUL)
    {
        ShowError("\n%s -> ERROR : \"Use BG_InitGameBoard() method to initialize game board first!. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        return;/*return to caller immediately.*/
    }

    else if(board_info == NULL)
    {
        ShowError("\n%s -> ERROR : \"No Array provided to receive output !. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        return;/*return to caller immediately.*/
    }

    else if(pieces_len < 1 || pieces_len > bg_grid_size)
    {
        ShowError("\n%s -> ERROR : \" Array length : '%d' must be in range [1 - %d] \"\n",BG_FUNC,pieces_len,bg_grid_size,BG_LINE);
        return;/*return to caller immediately.*/
    }

    /*Initialize board_info array with default value.*/
    BG_FillArray(board_info,pieces_len,sizeof(BG_BoardInfo),&bg_not_found,STRUCT_TYPE);
    SetPrivateAccess(TRUE);

    /*Save board row information in board_info array.*/
    for(row_index = 0; row_index <= bg_board_size; row_index++)
    {
        is_next_row = (row_index % bg_grid_size) == 0 && row_index > 1;

        if(is_next_row)
        {
            row_end = row_index - 1;
            row_start = ((row_end+1)  -  bg_grid_size);

            /*Save current row's start,end and no.*/
            board_info[row_num].row_start  = row_start;
            board_info[row_num].row_end  = row_end;
            board_info[row_num++].row_num  = row_num;
        }
    }

    /*Save board column information in board_info array.*/
    for(col_num = 0; col_num < bg_grid_size; ++col_num)
    {
        for(col_index = col_num; col_index < bg_board_size; col_index+=bg_grid_size)
        {
            col_start = (col_num == col_index) ? col_index : col_start;
        }
        col_end = col_index - bg_grid_size;

        /*Save current column's start end and no.*/
        board_info[col_num].col_num = col_num+1;
        board_info[col_num].col_start = col_start;
        board_info[col_num].col_end = col_end;
    }

    /*Save board left diagonal information in board_info array.*/
    diag_row_end = bg_board_size-1; /*Get current end row for left diagonal.*/
    diag_col_end = board_info[0].col_end; /*Get current end column for left diagonal.*/
    left_diag_len = bg_grid_size;/*Get current length for left diagonal.*/

    for(diag_index = 0; diag_index < diag_col_end; diag_index+=bg_grid_size)
    {
        for(left_diag_index = diag_index; left_diag_index <= diag_row_end; left_diag_index+=(bg_grid_size+1))
        {
            left_diag_start = (left_diag_index == diag_index) ? left_diag_index : left_diag_start;
        }
        left_diag_end = diag_row_end;

        /*Save left diagonal start end and no.*/
        board_info[left_diag_num].left_diag_start = left_diag_start;
        board_info[left_diag_num].left_diag_end = left_diag_end;
        board_info[left_diag_num].left_diag_len = left_diag_len;
        board_info[left_diag_num++].left_diag_num = left_diag_num;
        diag_row_end--;
        left_diag_len--;
    }

    /*Save board right diagonal information in board_info array.*/
    diag_row_end = (bg_board_size - bg_grid_size); /*Get current end row for right diagonal.*/
    diag_col_end = board_info[bg_grid_size-1].col_end; /*Get current end column for right diagonal.*/
    right_diag_len = bg_grid_size;/*Get current length for right diagonal.*/

    for(diag_index = bg_grid_size-1; diag_index < col_end; diag_index+=bg_grid_size)
    {
        for(right_diag_index = diag_index; right_diag_index <= diag_row_end; right_diag_index+=(bg_grid_size-1))
        {
            right_diag_start = (right_diag_index == diag_index) ? right_diag_index : right_diag_start;
        }
        right_diag_end = diag_row_end;

        /*Save right diagonal start end and no.*/
        board_info[right_diag_num].right_diag_start = right_diag_start;
        board_info[right_diag_num].right_diag_end = right_diag_end;
        board_info[right_diag_num].right_diag_len = right_diag_len;
        board_info[right_diag_num++].right_diag_num = right_diag_num;
        diag_row_end++;
        right_diag_len--;
    }

    /*Print board information if selected.*/
    if(print_info)
    {
        for(index = 0; index < pieces_len; ++index)
        {
            printf("Row No : %d\tStarts : %d\tEnd : %d\n",board_info[index].row_num,board_info[index].row_start,board_info[index].row_end);
            printf("Column No : %d\tStarts : %d\tEnd : %d\n",board_info[index].col_num,board_info[index].col_start,board_info[index].col_end);

            if(index < pieces_len-1)
            {
                printf("Left Diagonal No : %d\tStarts : %d\tEnd : %d\tLen : %d\n",board_info[index].left_diag_num,board_info[index].left_diag_start,board_info[index].left_diag_end,board_info[index].left_diag_len);
                printf("Right Diagonal No : %d\tStarts : %d\tEnd : %d\tLen : %d\n\n",board_info[index].right_diag_num,board_info[index].right_diag_start,board_info[index].right_diag_end,board_info[index].right_diag_len);
            }
        }
    }
    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully\n",BG_FUNC);
    }
    SetPrivateAccess(FALSE);
}

/**
 * @description - Get information of piece such as position,row/columns/diagonal start end and length etc.
 * @param - piece_info_arr  [output]: Array to receive information of piece . Must be of type 'BG_PieceInfo'.
 * arr_len [input] : Length of array. Must be of same size as BoardSize i.e [GridSize * GridSize].
  * game_board [input] : Your current game board .
  * board_piece [input] : Character denoting board piece.
 * print_info [input] : Whether to print information of piece rows,cols and diagonals or not . Use TRUE or FALSE.
  * @return - On success it return total number of times piece was found on board otherwise return BG_ERROR.
 */

int BG_GetPieceInfo(BG_PieceInfo* piece_info_arr,size_t arr_len,int *game_board,char board_piece,bool print_info)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tpiece_info_arr : %p\tarr_len : %d\tgame_board : %p\tboard_piece : %c\tprint_info : %s\n",BG_FUNC,piece_info_arr,arr_len,game_board,board_piece,GetBoolAlpha(print_info));
    }
    int bg_not_found = BG_NOT_FOUND,index = 0,board_index = 0,piece_index = -1,row_index = 0,col_index = 0,left_diag_index = 0,right_diag_index = 0;
    int row_start = 0,row_end = 0,col_start = 0,col_end;
    int left_diag_start = 0,left_diag_end = 0,right_diag_start = 0,right_diag_end = 0;
    bool pos_found = FALSE,row_found = FALSE,col_found = FALSE,left_diag_found = FALSE,right_diag_found = FALSE;

    BG_BoardInfo board_info_arr[bg_grid_size];
    /*Initialize board_info_arr array with default value.*/
    BG_FillArray(board_info_arr,bg_grid_size,sizeof(BG_BoardInfo),&bg_not_found,STRUCT_TYPE);
    SetPrivateAccess(TRUE);

    /*Get board information of rows,cols etc.*/
    BG_GetBoardInfo(board_info_arr,bg_grid_size,FALSE);
    SetPrivateAccess(TRUE);

    /*Error checking for parameters.*/
    if(bg_grid_size == NUL)
    {
        ShowError("\n%s -> ERROR : \"Use BG_InitGameBoard() method to initialize game board first!. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        return BG_ERROR;/*return to caller immediately.*/
    }

    else if(board_info_arr == NULL)
    {
        ShowError("\n%s -> ERROR : \"No Array provided to receive output !. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        return BG_ERROR;/*return to caller immediately.*/
    }

    else if(arr_len != bg_board_size)
    {
        ShowError("\n%s -> ERROR : \" Array length : '%d' must be of same size of GridSize i.e '%d'! Occurred at line no : %d\"\n",BG_FUNC,arr_len,bg_board_size,BG_LINE);
        return BG_ERROR;/*return to caller immediately.*/
    }

    /*Initialize piece_info_arr array with default value.*/
    BG_FillArray(piece_info_arr,bg_board_size,sizeof(BG_PieceInfo),&bg_not_found,STRUCT_TYPE);
    SetPrivateAccess(TRUE);

    /*Main loop for finding piece information.*/
    for(board_index = 0; board_index < bg_board_size; ++board_index)
    {
        pos_found = FALSE;

        /*Get actual position information of piece.*/
        if(game_board[board_index] == board_piece)
        {
            piece_index++;
            piece_info_arr[piece_index].piece_pos = board_index;
            pos_found = TRUE;
        }

        if(pos_found)
        {
            /*Get Rows information of piece.*/
            for(index = 0; index < bg_grid_size; ++index)
            {
                row_start = board_info_arr[index].row_start;
                row_end = board_info_arr[index].row_end;

                for(row_index = row_start; row_index <= row_end; row_index++)
                {
                    if(piece_info_arr[piece_index].piece_pos == row_index)
                    {
                        piece_info_arr[piece_index].piece_row_start = board_info_arr[index].row_start;
                        piece_info_arr[piece_index].piece_row_end = board_info_arr[index].row_end;
                        piece_info_arr[piece_index].piece_row_num = board_info_arr[index].row_num;
                        row_found = TRUE;
                        break;
                    }
                }
            }


            /*Get Cols information of piece.*/
            for(index = 0; index < bg_grid_size; ++index)
            {
                col_start = board_info_arr[index].col_start;
                col_end = board_info_arr[index].col_end;

                for(col_index = col_start; col_index <= col_end; col_index+=bg_grid_size)
                {
                    if(piece_info_arr[piece_index].piece_pos== col_index)
                    {
                        piece_info_arr[piece_index].piece_col_start = board_info_arr[index].col_start;
                        piece_info_arr[piece_index].piece_col_end= board_info_arr[index].col_end;
                        piece_info_arr[piece_index].piece_col_num = board_info_arr[index].col_num;
                        col_found = TRUE;
                        break;
                    }
                }
            }


            /*Get Left diagonal information of piece.*/
            for(index = 0; index < bg_grid_size-1; ++index)
            {
                left_diag_start = board_info_arr[index].left_diag_start;
                left_diag_end = board_info_arr[index].left_diag_end;

                for(left_diag_index = left_diag_start; left_diag_index <= left_diag_end; left_diag_index+=(bg_grid_size+1))
                {
                    if(piece_info_arr[piece_index].piece_pos == left_diag_index)
                    {
                        piece_info_arr[piece_index].piece_left_diag_start = board_info_arr[index].left_diag_start;
                        piece_info_arr[piece_index].piece_left_diag_end = board_info_arr[index].left_diag_end;
                        piece_info_arr[piece_index].piece_left_diag_num = board_info_arr[index].left_diag_num;
                        left_diag_found = TRUE;
                        break;
                    }
                }
            }

            /*Get Right diagonal information of piece.*/
            for(index = 0; index < bg_grid_size-1; ++index)
            {
                right_diag_start = board_info_arr[index].right_diag_start;
                right_diag_end = board_info_arr[index].right_diag_end;

                for(right_diag_index = right_diag_start; right_diag_index <= right_diag_end; right_diag_index+=(bg_grid_size-1))
                {
                    if(piece_info_arr[piece_index].piece_pos == right_diag_index)
                    {
                        piece_info_arr[piece_index].piece_right_diag_start = board_info_arr[index].right_diag_start;
                        piece_info_arr[piece_index].piece_right_diag_end = board_info_arr[index].right_diag_end;
                        piece_info_arr[piece_index].piece_right_diag_num = board_info_arr[index].right_diag_num;
                        right_diag_found = TRUE;
                        break;
                    }
                }
            }

            if(print_info)
            {
                (pos_found) ? printf("\nPiece '%c' found at position : %d\n",board_piece,piece_info_arr[piece_index].piece_pos) : printf("Piece position not found !\n");
                (row_found) ? printf("Piece Row No : %d\tRow Start : %d\tRow End : %d\n",piece_info_arr[piece_index].piece_row_num,piece_info_arr[piece_index].piece_row_start,piece_info_arr[piece_index].piece_row_end) : printf("Piece row not found !\n");
                (col_found) ? printf("Piece Column No : %d\tColumn Start : %d\tColumn End : %d\n",piece_info_arr[piece_index].piece_col_num,piece_info_arr[piece_index].piece_col_start,piece_info_arr[piece_index].piece_col_end)  : printf("Piece column not found !\n");
                (left_diag_found) ? printf("Left Diagonal No : %d\tLeft Diagonal Start : %d\tLeft Diagonal End : %d\n",piece_info_arr[piece_index].piece_left_diag_num,piece_info_arr[piece_index].piece_left_diag_start,piece_info_arr[piece_index].piece_left_diag_end)  : printf("Piece left diagonal not found !\n");
                (right_diag_found) ?  printf("Right Diagonal No : %d\tRight Diagonal Start : %d\tRight Diagonal End : %d\n\n",piece_info_arr[piece_index].piece_right_diag_num,piece_info_arr[piece_index].piece_right_diag_start,piece_info_arr[piece_index].piece_right_diag_end)  : printf("Piece right diagonal not found !\n");
            }
        }
    }

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,piece_index+1);
    }
    SetPrivateAccess(FALSE);
    return piece_index+1;
}


/**
 * @description - Fill selected row of game board with board piece.
 * @param -
 * game_board : Pointer to variable in which game board is stored.
 * row_num : Row number to be filled.
 * board_piece : Board piece to fill selected row with.
  * @return - If filling was success it returns TRUE otherwise returns FALSE.
 */

bool BG_FillBoardRow(int* game_board, int row_num, char board_piece)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tgame_board : %p\trow_num : %d\tboard_piece : %c\n",BG_FUNC,game_board,row_num,board_piece);
    }

    bool fill_status = FALSE;
    int nul = NUL,i,j;

    if(bg_grid_size == NUL)
    {
        ShowError("\n%s -> ERROR : \"Use BG_InitGameBoard() method to initialize game board first!. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        return fill_status;/*return to caller immediately.*/
    }

    BG_BoardInfo board_info[bg_grid_size];
    BG_FillArray(board_info,bg_grid_size,sizeof(BG_BoardInfo),&nul,STRUCT_TYPE);
    SetPrivateAccess(TRUE);

    BG_GetBoardInfo(board_info,bg_grid_size,FALSE);
    SetPrivateAccess(TRUE);

    if(row_num > bg_grid_size)
    {
        ShowError("\n%s -> ERROR : \"Invalid row number provided '%d', Row range [%d-%d]. Occurred at line no : %d\"\n",BG_FUNC,row_num,board_info[0].row_num,board_info[bg_grid_size-1].row_num,BG_LINE);
        fill_status = FALSE;
    }

    else
    {
        for(i = 0; i < bg_grid_size; ++i)
        {
            if( (board_info[i].row_num) == row_num)
            {
                for(j = board_info[i].row_start; j <= board_info[i].row_end; j++)
                {
                    game_board[j] = board_piece;
                }
                fill_status = TRUE;
                break;
            }
        }
    }

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,fill_status);
    }
    SetPrivateAccess(FALSE);
    return fill_status;
}

/**
 * @description - Fill selected rows of game board with multiple board_pieces.
 * @param -
 * game_board : Pointer to variable in which game board is stored.
 * row_nums : Array of row numbers to be filled.
 * board_pieces : Array of board pieces to fill selected row with.
 * board_pieces_len : Length of board pieces array.
  * @return - If filling was success it returns TRUE otherwise returns FALSE.
 */

bool BG_FillBoardRows(int* game_board, int *row_nums,char *board_pieces,size_t board_pieces_len)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tgame_board : %p\trow_nums : %p\tboard_pieces : %p\tboard_pieces_len : %u\n",BG_FUNC,game_board,row_nums,board_pieces,board_pieces_len);
    }

    int i,fill_status = TRUE;;
    for(i = 0; i < board_pieces_len; ++i)
    {
        if(!BG_FillBoardRow(game_board,row_nums[i],board_pieces[i]))
        {
            fill_status =  FALSE;
            break;
        }
    }
    SetPrivateAccess(TRUE);

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,fill_status);
    }
    SetPrivateAccess(FALSE);
    return fill_status;
}

/**
 * @description - Fill selected Column of game board with board piece.
 * @param -
 * game_board : Pointer to variable in which game board is stored.
 * col_num : Column number to be filled.
 * board_piece : Board piece to fill selected column with.
  * @return - If filling was success it returns TRUE otherwise returns FALSE.
 */

bool BG_FillBoardCol(int*game_board, int col_num, char board_piece)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tgame_board : %p\tcol_num : %d\tboard_piece : %c\n",BG_FUNC,game_board,col_num,board_piece);
    }

    bool fill_status = FALSE;
    int nul = NUL,i,j;

    if(bg_grid_size == NUL)
    {
        ShowError("\n%s -> ERROR : \"Use BG_InitGameBoard() method to initialize game board first!. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        return fill_status;/*return to caller immediately.*/
    }

    BG_BoardInfo board_info[bg_grid_size];
    BG_FillArray(board_info,bg_grid_size,sizeof(BG_BoardInfo),&nul,STRUCT_TYPE);
    SetPrivateAccess(TRUE);

    BG_GetBoardInfo(board_info,bg_grid_size,FALSE);
    SetPrivateAccess(TRUE);

    if(col_num > bg_grid_size)
    {
        ShowError("\n%s -> ERROR : \"Invalid column number provided '%d', Column range [%d-%d]. Occurred at line no : %d\"\n",BG_FUNC,col_num,board_info[0].col_num,board_info[bg_grid_size-1].col_num,BG_LINE);
        fill_status = FALSE;
    }

    else
    {
        for(i = 0; i < bg_grid_size; ++i)
        {
            if( (board_info[i].col_num) == col_num)
            {
                for(j = board_info[i].col_start; j <= board_info[i].col_end; j+=bg_grid_size)
                {
                    game_board[j] = board_piece;
                }
                fill_status = TRUE;
                break;
            }
        }
    }
    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,fill_status);
    }
    SetPrivateAccess(FALSE);
    return fill_status;
}

/**
 * @description - Fill selected columns of game board with multiple board pieces.
 * @param -
 * game_board : Pointer to variable in which game board is stored.
 * col_nums : Array of column number to be filled.
 * board_pieces : Array of board pieces to fill selected column with.
 * board_pieces_len : Length of board pieces array.
  * @return - If filling was success it returns TRUE otherwise returns FALSE.
 */

bool BG_FillBoardCols(int*game_board, int*col_nums,char *board_pieces,size_t board_pieces_len)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tgame_board : %p\tcol_nums : %p\tboard_pieces : %p\tboard_pieces_len : %u\n",BG_FUNC,game_board,col_nums,board_pieces,board_pieces_len);
    }

    int i,fill_status = TRUE;;
    for(i = 0; i < board_pieces_len; ++i)
    {
        if(!BG_FillBoardCol(game_board,col_nums[i],board_pieces[i]))
        {
            fill_status =  FALSE;
            break;
        }
    }
    SetPrivateAccess(TRUE);

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,fill_status);
    }
    SetPrivateAccess(FALSE);
    return fill_status;
}

/**
 * @description - Fill selected left/right diagonal of game board with board piece.
 * @param -
 * game_board : Pointer to variable in which game board is stored.
 * diag_num : Diagonal number to be filled.
 * diag_type : Diagonal type to be filled . LEFT or RIGHT diagonal , Use Enum 'DIAGONAL_TYPE' to provide value.
 * board_piece : Board piece to fill selected diagonal with.
  * @return - If filling was success it returns TRUE otherwise returns FALSE.
 */

bool BG_FillBoardDiagonal(int* game_board, int diag_num, int diag_type, char board_piece)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        char *diag_type_str = (diag_type == LEFT_DIAG) ? "LEFT_DIAG" : (diag_type == RIGHT_DIAG) ? "RIGHT_DIAG"  : "UNKNOWN_DIAG";
        AddLog("%s -> called with arguments\tgame_board : %p\tdiag_num : %d\tdiag_type : %s\tboard_piece : %c\n",BG_FUNC, game_board,diag_num,diag_type_str,board_piece);
    }

    bool fill_status = FALSE;
    int nul = NUL,i,j;

    if(bg_grid_size == NUL)
    {
        ShowError("\n%s -> ERROR : \"Use BG_InitGameBoard() method to initialize game board first!. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        return fill_status;/*return to caller immediately.*/
    }

    BG_BoardInfo board_info[bg_grid_size];
    BG_FillArray(board_info,bg_grid_size,sizeof(BG_BoardInfo),&nul,STRUCT_TYPE);
    SetPrivateAccess(TRUE);

    BG_GetBoardInfo(board_info,bg_grid_size,FALSE);
    SetPrivateAccess(TRUE);

    if(diag_num >= bg_grid_size-1)
    {
        (diag_type == LEFT_DIAG) ?
        ShowError("\n%s -> ERROR : \"Invalid diagonal number provided '%d', Diagonal range [%d-%d]. Occurred at line no : %d\"\n",BG_FUNC,diag_num,board_info[0].left_diag_num,board_info[bg_grid_size-2].left_diag_num,BG_LINE)
        : ShowError("\n%s -> ERROR : \"Invalid diagonal number provided '%d', Diagonal range [%d-%d]. Occurred at line no : %d\"\n",BG_FUNC,diag_num,board_info[0].right_diag_num,board_info[bg_grid_size-2].right_diag_num,BG_LINE);
        fill_status = FALSE;
    }

    else
    {
        for(i = 0; i < bg_grid_size; ++i)
        {

            if(   (diag_type == LEFT_DIAG) ?  ((board_info[i].left_diag_num) == diag_num) : ((board_info[i].right_diag_num) == diag_num) )
            {
                if(diag_type == LEFT_DIAG)
                {
                    for(j = board_info[i].left_diag_start; j <= board_info[i].left_diag_end; j+=(bg_grid_size+1) )
                        game_board[j] = board_piece;
                }

                else if(diag_type == RIGHT_DIAG)
                {
                    for(j = board_info[i].right_diag_start; j <= board_info[i].right_diag_end; j+=(bg_grid_size-1) )
                        game_board[j] = board_piece;
                }
                fill_status = TRUE;
                break;
            }
        }
    }

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,fill_status);
    }
    SetPrivateAccess(FALSE);
    return fill_status;
}

/**
 * @description - Fill selected left/right diagonals of game board with multiple board pieces.
 * @param -
 * game_board : Pointer to variable in which game board is stored.
 * diag_nums : Array of Diagonal numbers to be filled.
 * diag_type : Diagonal type to be filled . LEFT or RIGHT diagonal , Use Enum 'DIAGONAL_TYPE' to provide value.
 * board_pieces : Array of  board pieces to fill selected diagonal with.
  * board_pieces_len : Length of board pieces array.
  * @return - If filling was success it returns TRUE otherwise returns FALSE.
 */

bool BG_FillBoardDiagonals(int* game_board,int* diag_nums,int diag_type,char *board_pieces,size_t board_pieces_len)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        char *diag_type_str = (diag_type == LEFT_DIAG) ? "LEFT_DIAG" : (diag_type == RIGHT_DIAG) ? "RIGHT_DIAG"  : "UNKNOWN_DIAG";
        AddLog("%s -> called with arguments\tgame_board : %p\tdiag_nums : %d\tdiag_type : %s\tboard_pieces : %p\tboard_pieces_len : %u\n",BG_FUNC, game_board,diag_nums,diag_type_str,board_pieces,board_pieces_len);
    }

    int i,fill_status = TRUE;;
    for(i = 0; i < board_pieces_len; ++i)
    {
        if(!BG_FillBoardDiagonal(game_board,diag_nums[i],diag_type,board_pieces[i]))
        {
            fill_status =  FALSE;
            break;
        }
    }

    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,fill_status);
    }
    SetPrivateAccess(FALSE);
    return fill_status;
}

/**
 * @description - Invert the game board.
 * @param - invert_bool : Invert the current board or not. Use TRUE or FALSE.
 */

void BG_InvertBoard(bool invert_bool)
{
    SetPrivateAccess(TRUE);
    board_invert = (invert_bool) ? TRUE : FALSE;
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tinvert_bool : %s\n",BG_FUNC,GetBoolAlpha(invert_bool));
        AddLog("%s -> ended successfully\n",BG_FUNC);
    }
    SetPrivateAccess(FALSE);
}

/**
 * @description - Use multi-piece for board_piece character.
 * @param - piece_bool : Whether to use multi-piece or not. Use TRUE or FALSE.
 */

void BG_MultiPiece(bool piece_bool)
{
    SetPrivateAccess(TRUE);
    multi_piece = (piece_bool) ? TRUE : FALSE;
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tpiece_bool : %s\n",BG_FUNC,GetBoolAlpha(piece_bool));
        AddLog("%s -> ended successfully\n",BG_FUNC);
    }
    SetPrivateAccess(FALSE);
}

/**
 * @description - Draw border of game board.
 * @param - border_bool : Whether draw border of game board or not. Use TRUE or FALSE. (Defaults to TRUE).
 */
void BG_BoardBorder(bool border_bool)
{
    SetPrivateAccess(TRUE);
    board_border = (border_bool) ? TRUE : FALSE;
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tboard_border : %s\n",BG_FUNC,GetBoolAlpha(board_border));
        AddLog("%s -> ended successfully\n",BG_FUNC);
    }
    SetPrivateAccess(FALSE);
}
