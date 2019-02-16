#define USE_MISC_MODULE

#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
#include "..\engine\BoardGamr.h"
#else
#include "../engine/BoardGamr.h"
#endif

void FillArrayDemo();
void ConvertArrayDemo();

#define ARR_COLS 5
#define ARR_ROWS 4
#define ARR_2D_LEN (ARR_COLS * ARR_ROWS)

int main(void)
{
    if(BG_EnableLogs())/*Enable logs in game-engine.*/
        printf("Logs are enabled  in game engine\n");

    else if(BG_DisableLogs())/*Disable logs in game-engine.*/
        printf("Logs are disabled in game engine\n");

    FillArrayDemo();

    return 0;
}

void FillArrayDemo()
{
    int i,clen = 20,ilen = 50,flen = 30,dlen = 35,bi_len = 10,oi_len = 15;

    /*Different types of values to fill.*/
    int ival = -1;
    char cval = 'a';
    float fval = 3.5f;
    double dval = 55.44;
    int bi_val = -1,oi_val = 0;

    /*Different types of array to be filled.*/
    char carr[clen];
    int iarr[ilen];
    float farr[flen];
    double darr[dlen];
    BG_BoardInfo bi_arr[bi_len];
    BG_PieceInfo pi_arr[oi_len];

    BG_FillArray(carr,clen,NUL,&cval,CHAR_TYPE); /*Fill Character array with 'a'*/
    BG_FillArray(iarr,ilen,NUL,&ival,INT_TYPE);     /*Fill Integer array with -1*/
    BG_FillArray(farr,flen,NUL,&fval,FLOAT_TYPE);    /*Fill Float array with 3.5*/
    BG_FillArray(darr,dlen,NUL,&dval,DOUBLE_TYPE);    /*Fill Double array with 55.44*/
    BG_FillArray(bi_arr,bi_len,sizeof(BG_BoardInfo),&bi_val,STRUCT_TYPE); /*Fill Board info array with -1*/
    BG_FillArray(pi_arr,oi_len,sizeof(BG_PieceInfo),&oi_val,STRUCT_TYPE); /*Fill piece info array with 0*/

    /*Print Different types of array after filling.*/
    for(i = 0; i < clen; ++i)
        printf("char array[%d]: %c\n",i+1,carr[i]);
    printf("\n");

    for(i = 0; i < ilen; ++i)
        printf("int array[%d]: %d\n",i+1,iarr[i]);
    printf("\n");

    for(i = 0; i < flen; ++i)
        printf("float array[%d]: %f\n",i+1,farr[i]);
    printf("\n");

    for(i = 0; i < dlen; ++i)
        printf("double array[%d]: %f\n",i+1,darr[i]);

    for(i = 0; i < bi_len; ++i)
    {
        printf("board_info_arr[%d].row : %d\tstart : %d\tend : %d\n",i,bi_arr[i].row_num,bi_arr[i].row_start,bi_arr[i].row_end);
        printf("board_info_arr[%d].col : %d\tstart : %d\tend : %d\n",i,bi_arr[i].col_num,bi_arr[i].col_start,bi_arr[i].col_end);
        printf("board_info_arr[%d].left_diag : %d\tstart : %d\tend : %d\n",i,bi_arr[i].left_diag_num,bi_arr[i].left_diag_start,bi_arr[i].left_diag_end);
        printf("board_info_arr[%d].right_diag : %d\tstart : %d\tend : %d\n\n",i,bi_arr[i].right_diag_num,bi_arr[i].right_diag_start,bi_arr[i].right_diag_end);
    }

    for(i = 0; i < bi_len; ++i)
    {
        printf("piece_info_arr[%d].row : %d\tstart : %d\tend : %d\n",i,pi_arr[i].piece_row_num,pi_arr[i].piece_row_start,pi_arr[i].piece_row_end);
        printf("piece_info_arr[%d].col : %d\tstart : %d\tend : %d\n",i,pi_arr[i].piece_col_num,pi_arr[i].piece_col_start,pi_arr[i].piece_col_end);
        printf("piece_info_arr[%d].piece_left_diag : %d\tstart : %d\tend : %d\n",i,pi_arr[i].piece_left_diag_num,pi_arr[i].piece_left_diag_start,pi_arr[i].piece_left_diag_end);
        printf("piece_info_arr[%d].piece_right_diag : %d\tstart : %d\tend : %d\n\n",i,pi_arr[i].piece_right_diag_num,pi_arr[i].piece_right_diag_start,pi_arr[i].piece_right_diag_end);
    }

}

void ConvertArrayDemo()
{
    int i,j;

    /*Convert 1d array to 2d array.*/
    float farr_1d[9] = {2.3,4.5,6.6,7.7,3.88,56.6,77.5,8.5,99.9};/*Input array.*/
    float farr_2d[3][3];/*Output array.*/

    BG_ConvertArray(farr_2d,farr_1d,sizeof(farr_1d));
    puts("\n2-d Array converted : ");
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            printf("%.2f ",farr_2d[i][j]);
        }
    }


    /*Convert 2d array to 1d array.*/
    int arr_2d[ARR_COLS][ARR_ROWS]= {{5,2,6,4},{7,6,1,8},{10,12,11,42},{13,74,15,46},{23,56,78,57}}; /*Input array.*/
    int arr_1d[ARR_2D_LEN];/*Output array.*/

    BG_ConvertArray(arr_1d,arr_2d,sizeof(arr_2d));
    puts("\n1-d Array converted: ");
    for(i=0; i<ARR_2D_LEN; i++)
    {
        printf("%d ",arr_1d[i]);
    }
}
