#ifndef BG_CONST_H
#define BG_CONST_H

/*Defining constants for game.*/
typedef unsigned int uint;

/*re-define standard macros for file,line time etc.*/
#define BG_FUNC __func__
#define BG_LINE __LINE__
#define BG_FILE __FILE__
#define BG_DATE __DATE__
#define BG_TIME __TIME__

/*Defining exception handling constants*/
#if !defined(bg_try) && !defined(bg_catch) && !defined(bg_throw)
#define bg_try bool BG_HadError=FALSE;
#define bg_catch(x) BG_ExitJump:if(BG_HadError)
#define bg_throw(x) BG_HadError=TRUE;goto BG_ExitJump;
#endif

enum BOARD_LAYOUT {UPPER_LEFT = 43,UPPER_RIGHT = 43,LOWER_LEFT = 43,LOWER_RIGHT = 43,VERTICAL_BAR = 124,HORIZONTAL_BAR = 45};
enum BOARD_CONST {BOARD_CELL_WIDTH = 5,GRID_MIN = 3,GRID_MAX = 0x20,BOARD_DIGITS_SIZE = 0x64};
enum MISC_CONST {NUL = 0,FALSE = 0,TRUE = 1,ALT_CONST = 2,HEAD = 0,TAIL = 1,DICE_ONE = 1,DICE_SIX = 6,BG_SUCCESS = 0,BG_ERROR = -1,BG_NOT_FOUND = -1};
enum INIT_TYPE {SEQ_INIT = 1,ALT_INIT = 2,RAND_INIT = 3,ROW_INIT = 4,COL_INIT = 5};
enum VALUE_TYPE {NOP_VALUE = 0,INC_VALUE = 1,DEC_VALUE = 2,RAND_VALUE = 3};
enum BOARD_TYPE {SEQ_BOARD = 1,ALT_BOARD = 2};
enum PLAYER_ID {PLAYER_COMP = 0,PLAYER_1 = 1,PLAYER_2 = 2,PLAYER_3 = 3,PLAYER_4 = 4};
enum PLAY_MODE {SOLO_MODE = 1,COMPUTER_MODE = 2,FRIEND_MODE = 3};
enum DATA_TYPE {CHAR_TYPE,INT_TYPE,FLOAT_TYPE,DOUBLE_TYPE,STRUCT_TYPE};
enum FONT_ALIGN {FONT_LEFT,FONT_CENTER,FONT_RIGHT};
enum DIAGONAL_TYPE{LEFT_DIAG = 1,RIGHT_DIAG = 2};
enum DECKS {DECK_FACES = 13,DECK_SUITS = 4,BUF_LEN = 0x58,DECK_LEN = DECK_FACES * DECK_SUITS,DECK_SPLIT = 20};
enum CARDS {CARD_HEIGHT = 6,CARD_WIDTH = 9, CARD_LEN = 0x7F,CARD_SIZE = ((CARD_HEIGHT * CARD_WIDTH) + 4)};
enum SUITS {CLUB_SUIT = 1,DIAMOND_SUIT = 2,HEARTS_SUIT = 3,SPADES_SUIT = 4};
enum DECK_ERRORS {VALID_DECK = 1,INVALID_DECK = 0,INVALID_SUIT_RANGE = -1,INVALID_CARD_DUP = -2};
enum DECK_TYPE{FULL_DECK = DECK_LEN,HALF_DECK = (FULL_DECK/2),QUARTER_DECK = (HALF_DECK/2)};
enum COPY_CONST{COPY_TO,COPY_FROM};
enum SIDES{FRONT_SIDE,REAR_SIDE};

#define BG_DEFAULT_FONT "standard"
#define BG_DEFAULT_FONT_WIDTH 80
#define BG_DEFAULT_FONT_ALIGN FONT_LEFT

/*Card deck constant.*/
const char card_face[] = "23456789XJQKA";
int card_suit[] = {CLUB_SUIT,DIAMOND_SUIT,HEARTS_SUIT,SPADES_SUIT};

/*Structure to hold Card  information*/
typedef struct Card
{
    char face; /*Card face.*/
    int suit; /*Card suit.*/
}Card;

/*Structure for Board information of All Rows,Columns and diagonals.*/
typedef struct BG_BoardInfo
{
    int row_num; /*Row number.*/
    int row_start; /*Start position of row.*/
    int row_end; /*End position of row.*/

    int col_num;  /*Column number.*/
    int col_start; /*Start position of column.*/
    int col_end; /*End position of column.*/

    int left_diag_num;  /*Left diagonal. number .*/
    int left_diag_start; /*Start position of left diagonal.*/
    int left_diag_end; /*End position of left diagonal.*/
    int left_diag_len; /*Length of left diagonal.*/

    int right_diag_num;  /*Right diagonal. number .*/
    int right_diag_start; /*Start position of right diagonal.*/
    int right_diag_end; /*End position of right diagonal.*/
    int right_diag_len;  /*Length of right diagonal.*/

} BG_BoardInfo;

/*Structure for Piece information of All Rows,Columns and diagonals.*/
typedef struct BG_PieceInfo
{
    int piece_pos; /*Actual position of piece.*/
    int piece_row_num; /*Row number .*/
    int piece_row_start; /*Start position of row .*/
    int piece_row_end; /*End position of row.*/

    int piece_col_num;  /*Column number.*/
    int piece_col_start; /*Start position of column.*/
    int piece_col_end; /*End position of column.*/

    int piece_left_diag_num;  /*Left diagonal. number .*/
    int piece_left_diag_start; /*Start position of left diagonal.*/
    int piece_left_diag_end; /*End position of left diagonal.*/
    int piece_left_diag_len; /*Length of left diagonal.*/

    int piece_right_diag_num;  /*Right diagonal. number .*/
    int piece_right_diag_start; /*Start position of right diagonal.*/
    int piece_right_diag_end; /*End position of right diagonal.*/
    int piece_right_diag_len;  /*Length of right diagonal.*/
} BG_PieceInfo;

/*Private variables for board and clock.*/
int bg_grid_size = 0,bg_board_size = 0;
clock_t bg_timer;

/*****************
FIGLet constants.
******************/

#define FIG_STRLEN(x) ((int)strlen(x)) /* Eliminate ANSI problem */

#define DIRSEP1 '/'
#define DIRSEP2 '\\'
/* Leave alone for Unix and MS-DOS/Windows!
Note: '/' also used in filename in get_columns(). */

#define FONTFILESUFFIX ".flf"
#define FONTFILEMAGICNUMBER "flf2"
#define FSUFFIXLEN MYSTRLEN(FONTFILESUFFIX)
#define DEFAULTFONTDIR "fonts"
#define MAXLEN 255     /* Maximum character width */

/*  Globals dealing with chars that are read*/
typedef long in_char; /* "char" read from stdin */

in_char *in_char_line;  /* Alloc'd in_char in_charline[in_charlinelenlimit+1]; */
/* Note: not null-terminated. */
int in_char_line_len,in_char_line_len_limit;
int hzmode;  /* true if reading double-bytes in HZ mode */
int gndbl[4]; /* gndbl[n] is true if Gn is double-byte */
in_char gn[4]; /* Gn character sets: ASCII, Latin-1, none, none */
int gl; /* 0-3 specifies left-half Gn character set */
int gr; /* 0-3 specifies right-half Gn character set */

/*Globals dealing with chars that are written*/
typedef char out_char; /* "char" written to stdout */

typedef struct fc
{
    in_char ord;
    out_char **the_char;  /* Alloc'd char thechar[char_height][]; */
    struct fc *next;
} fchar_node;

fchar_node *fchar_list;
out_char **curr_char;
int curr_char_width;
int previous_char_width;
out_char **output_line;   /* Alloc'd char output_line[char_height][out_line_lenlimit+1]; */
int out_line_len;

/*  Globals dealing with command file storage*/
typedef struct cfn
{
    char *thename;
    struct cfn *next;
} cfnamenode;

cfnamenode *cfilelist,**cfilelistend;

/*Globals affected by parameters.*/
int justification,paragraph_flag,right2left,multi_byte;

#define SM_SMUSH 128
#define SM_KERN 64
#define SM_EQUAL 1
#define SM_LOWLINE 2
#define SM_HIERARCHY 4
#define SM_PAIR 8
#define SM_BIGX 16
#define SM_hard_blank 32

int smush_mode;

#define SMO_NO 0     /* no command-line smushmode */
#define SMO_YES 1    /* use command-line smushmode, ignore font smushmode */
#define SMO_FORCE 2  /* logically OR command-line and font smushmodes */

int smush_override;
int output_width;
int out_line_len_limit;
char font_dir_name[32],*font_name;


/*  Globals read from font file*/
char hard_blank;
int char_height;


/*Name of program, used in error messages*/
char *file_name;

/*Buffers to store error and log messages.*/
char err_buf[0x100] = {'\0'},log_buf[0x400] = {'\0'};

/*Setting private methods inaccessible*/
bool bg_private_method = FALSE;

/*Global variable for enabling/disabling logs*/
bool bg_logs_enabled = FALSE;

/*Global variable for storing error code*/
int bg_error_code = BG_ERROR;

#endif // BG_CONST_H
