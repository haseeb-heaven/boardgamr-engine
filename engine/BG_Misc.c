#include "BG_Misc.h"

/******************************************************************
******************PUBLIC-METHODS***********************************
*******************************************************************/

/**
 * @description - Fill any type of array with provided value.
 * @param - arr : Input Array to fill.
 * arr_len  : Length of array.
 * struct_size : Size of structure . [Optional. Required only when data type of type Struct, otherwise ignored.]
 * arr_value  : Pointer to value that you want to fill in array.
 * arr_type  : Data type of array and value . Use Enum 'DATA_TYPE' to provide value.
 */

void BG_FillArray(void* arr,uint arr_len,size_t struct_size,void* arr_value,int arr_type)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        char *arr_type_str = (arr_type == CHAR_TYPE) ? "CHAR_TYPE" : (arr_type == INT_TYPE) ? "INT_TYPE"  : (arr_type == FLOAT_TYPE) ? "FLOAT_TYPE" : (arr_type == DOUBLE_TYPE) ? "DOUBLE_TYPE"  : (arr_type == STRUCT_TYPE) ? "STRUCT_TYPE" : "UNKNOWN_TYPE";
        AddLog("%s -> called with arguments\tarr : %p\tarr_len : %u\tstruct_size : %u\tarr_value : %p\tarr_type : %s\n",BG_FUNC,arr,arr_len,struct_size,arr_value,arr_type_str);
    }
    uint index = 0;

    bg_try
    {
        if(arr == NULL)
        {
            CopyError("%s -> ERROR : \"No Array provided to fill !. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
            SetErrorCode(BG_ERROR);
            bg_throw(GetErrorCode());
        }

        /*Fill whole structure array with provided value.*/
        else if(arr_type == STRUCT_TYPE)
        {
            memset(arr,*(int*)arr_value,struct_size * arr_len);
            SetErrorCode(BG_SUCCESS);
            bg_throw(GetErrorCode());
        }

        /*Fill whole char,int,float or double array with provided value.*/
        for(index = 0; index < arr_len; ++index)
        {
            if(arr_type  == CHAR_TYPE)
                *(char*)((char*)arr+index) = *(char*)arr_value;

            else if(arr_type  == INT_TYPE)
                *(int*)((int*)arr+index) = *(int*)arr_value;

            else if(arr_type == FLOAT_TYPE)
                *(float*)((float*)arr+index) = *(float*)arr_value;

            else if(arr_type == DOUBLE_TYPE)
                *(double*)((double*)arr+index) = *(double*)arr_value;
        }

    }
    bg_catch(bg_error_code)
    {
        if(bg_error_code == BG_ERROR)
        {
            ShowError(err_buf);
            SetPrivateAccess(FALSE);
            return;
        }
    }

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully\n",BG_FUNC);
    }
    SetPrivateAccess(FALSE);
}

/**
 * @description - Convert 1d array to 2d array or vice versa.
 * @param -
 * arr_dest : [Output]  Destination array.
 * arr_src :  [Input] Source array.
 * arr_src_size : [Input] Size of  Source array.
* @return -Returns the source array.
 */

void* BG_ConvertArray(void *arr_dest,void *arr_src,uint arr_size)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tarr : %p\tarr_dest : %p\tarr_src: %p\tarr_size : %u\n",BG_FUNC,arr_dest,arr_src,arr_size);
    }

    void *ret_src = NULL;

    bg_try
    {
        /*Safe check for input/output.*/
        if(arr_dest == NULL)
        {
            CopyError("%s -> ERROR : \"No Output array provided to receive output. !. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
            SetErrorCode(BG_ERROR);
            bg_throw(GetErrorCode());
        }

        else if(arr_src == NULL)
        {
            CopyError("%s -> ERROR : \"No Input array provided. !. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
            SetErrorCode(BG_ERROR);
            bg_throw(GetErrorCode());
        }
        else
        {
            ret_src = memmove(arr_dest,arr_src,arr_size);
        }
    }
    bg_catch(bg_error_code)
    {
        if(bg_error_code == BG_ERROR)
        {
            ShowError(err_buf);
        }
        SetPrivateAccess(FALSE);
        return ret_src;
    }

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %p\n",BG_FUNC,ret_src);
    }
    SetPrivateAccess(FALSE);
    return ret_src;
}

/**
* @description - Clear terminal screen.
*/

void BG_ClearScreen()
{
    system("cls||clear");
}


/**
 * @description - Custom random generator.
 * @param -
 * start_range : Starting range of random.
 * end_range : End range of random.
* @return - Random number between given range.
 */

uint BG_RandGenerator(uint start_range,uint end_range)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tstart_range : %d\tend_range : %d\n",BG_FUNC,start_range,end_range);
    }
    uint rand_num = NUL;
    static bool seed_init = FALSE;

    /*check for valid range.*/
    if(start_range >= end_range)
    {
        ShowError("%s -> ERROR : \"Invalid range provided !. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        return rand_num;
    }
    else if(!seed_init)
    {
        /*init the state with current time.*/
        srand(time(NULL));
        seed_init = TRUE;
    }

    /*set random number in range.*/
    rand_num =  rand() % (end_range + 1 - start_range) + start_range;

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,rand_num);
    }
    SetPrivateAccess(FALSE);
    return rand_num;
}


/**
 * INFO : Whether  engine. should maintain logs internally (enable this if you want this feature).
 * @description - Enable logs in library.
 * @return - Returns TRUE if enabled is success otherwise returns FALSE.
 */

bool BG_EnableLogs()
{
    SetPrivateAccess(TRUE);
    bool enable_status = FALSE;

    if (!IsLogEnabled())
    {
        bg_logs_enabled = TRUE;
        enable_status = TRUE;
    }
    else
    {
        ShowError("%s -> ERROR : \"Logs already enabled !. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        enable_status = FALSE;
    }
    SetPrivateAccess(FALSE);
    return enable_status;
}

/**
 * @description - Disable logs in engine.
 * @return - Returns TRUE if disable is success otherwise returns FALSE.
 */

bool BG_DisableLogs()
{
    SetPrivateAccess(TRUE);
    bool disable_status = FALSE;

    if (IsLogEnabled())
    {
        bg_logs_enabled = FALSE;
        disable_status = TRUE;
    }
    else
    {
        ShowError("%s -> ERROR : \"Logs already disabled !. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        disable_status = FALSE;
    }
    SetPrivateAccess(FALSE);
    return disable_status;
}

/**
 * @description - Get Handle to current game's process.
 * @return - If game found it return Handle to current game's process otherwise returns BG_NULL.
 */


/****************************************************************************
****************-PRIVATE-METHODS-*******************************************
****************************************************************************/

/**
 * @description - Check if logs are enabled or not.
 */
bool IsLogEnabled()
{
    bool log_status = FALSE;
    if (IsPrivateMethod(BG_FUNC,BG_LINE))
    {
        if (bg_logs_enabled == TRUE)
            log_status = TRUE;
    }
    return log_status;
}

/**
 * @description - Append root path to engine's folder.
 */
void AppendRootPath(char *suffix_folder)
{
    if(IsPrivateMethod(BG_FUNC,BG_LINE))
    {
        char root_path[64] = {'\0'};
        root_path[0] = root_path[1] = '.';
        char *dir_sep_linux  = "/",*dir_sep_win  = "\\";

#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
        strcpy(suffix_folder,strcat(strcat(root_path,dir_sep_win),suffix_folder));
#else
        strcpy(suffix_folder,strcat(strcat(root_path,dir_sep_linux),suffix_folder));
#endif
    }
}

/**
 * @description - Show custom message.
 */
void ShowError(const char *err_fmt,...)
{
    if(IsPrivateMethod(BG_FUNC,BG_LINE))
    {
        va_list arglist;
        va_start( arglist, err_fmt );
        vsprintf(err_buf,err_fmt, arglist );
        fprintf(stderr,err_buf);
        va_end( arglist );

        if (IsLogEnabled())
        {
            AddLog(err_buf);
        }
    }
}

/**
 * @description - Check if file already exist.
 */
bool FileExist(const char *file_name)
{
    bool file_exist = FALSE;
    FILE *file_handle = NULL;

    if(IsPrivateMethod(BG_FUNC,BG_LINE))
    {
        if((file_handle = fopen(file_name,"r")) != NULL)
        {
            fclose(file_handle);
            file_exist = TRUE;
        }
    }
    return file_exist;
}

char *GetBoolAlpha(bool bool_value)
{
     static char *bool_str = NULL;
    if(IsPrivateMethod(BG_FUNC,BG_LINE)){
    bool_str = (bool_value == TRUE) ? "TRUE" : "FALSE";
    }
    return bool_str;
}

/**
 * @description - Custom logger to add logs for engine.
 */
void AddLog(const char *log_fmt, ...)
{
    static const char *log_file_name = "BoardGamrLogs.log";
    static bool date_adder = FALSE;
    char *file_mode = NULL;
    int date_len = NUL;
    static FILE *file_handle = NULL;

    if(IsPrivateMethod(BG_FUNC,BG_LINE))
    {
        bg_try
        {

            if(!IsLogEnabled())
            {
                fprintf(stderr,"%s -> Logs are not enabled.! Use BG_EnableLogs() to enable logs\n",BG_FUNC);
                SetErrorCode(EPERM);
                bg_throw(GetErrorCode());
            }

            /*Only write data at beginning of file.*/
            if (!date_adder)
            {
                date_len = sprintf(log_buf, "\nLog created by BoardGamr at : Date : %s\tTime : %s\n", BG_DATE, BG_TIME);
                date_adder = TRUE;
            }

            /*Parse log message to buffer.*/
            va_list va_alist;
            va_start(va_alist, log_fmt);
            vsprintf(log_buf + date_len, log_fmt, va_alist);
            va_end(va_alist);

            /*Append mode accordingly.*/
            file_mode =  FileExist(log_file_name) ? "a+" : "w";
            file_handle = fopen(log_file_name,file_mode);

            if (file_handle == NULL)
            {
                SetErrorCode(errno);
                bg_throw(GetErrorCode());
            }

            if (fputs(log_buf,file_handle) == EOF)
            {
                SetErrorCode(errno);
                bg_throw(GetErrorCode());
            }
        }
        bg_catch(bg_error_code)
        {
            fprintf(stderr,"%s -> ERROR : \"%s!. Occurred at line no : %d\"\n",BG_FUNC,strerror(bg_error_code),BG_LINE);
        }
    }
    fclose(file_handle);
}

void CopyError(const char *err_fmt, ...)
{
    if(IsPrivateMethod(BG_FUNC,BG_LINE))
    {
        va_list arglist;
        va_start(arglist, err_fmt);
        vsprintf(err_buf,err_fmt,arglist);
        va_end(arglist);
    }
}

void SetErrorCode(int error_code)
{
    if(IsPrivateMethod(BG_FUNC,BG_LINE))
    {
        bg_error_code = error_code;
    }
}

int GetErrorCode()
{
    if(IsPrivateMethod(BG_FUNC,BG_LINE))
    {
        return bg_error_code;
    }
}

/**
 * @description - Check if provided method is private.
 */
bool IsPrivateMethod(const char* func_name, int line_no)
{
    bool is_private = FALSE;
    if (bg_private_method)
    {
        is_private = TRUE;
    }

    else
    {
        fprintf(stderr,"ERROR : %s method failed!\nREASON : Access to private method! (ERROR_INVALID_FUNCTION) \nLINE : occurred at line no. %d\n", func_name,line_no);
        is_private = FALSE;
    }
    return is_private;
}

/**
 * @description - Set private access to methods.
 */
void SetPrivateAccess(bool pvt_access)
{
    bg_private_method = pvt_access;
}
