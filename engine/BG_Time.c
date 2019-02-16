#include "BG_Time.h"

/**
 * @description - Time Delay in mili-seconds.
 * @param - mili_second : Delay time in mili-seconds.
 */

void BG_TimeDelay(const int mili_seconds)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tmili_seconds : %d\n",BG_FUNC,mili_seconds);
    }

    long pause;
    clock_t now,then;

    pause = mili_seconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully\n",BG_FUNC);
    }
    SetPrivateAccess(FALSE);
}

/**
 * @description - Start the timer on clock.
 */
void BG_StartTime()
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called\n",BG_FUNC);
    }
    bg_timer = clock();

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully\n",BG_FUNC);
    }
    SetPrivateAccess(FALSE);
}

/**
 * @description - Stop the timer on clock.
* @return - Elapsed time in seconds.
 */
double BG_StopTime()
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called\n",BG_FUNC);
    }

    bg_timer = clock() - bg_timer;
    double time_taken = ((double)bg_timer)/CLOCKS_PER_SEC;

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %f\n",BG_FUNC,time_taken);
    }
    SetPrivateAccess(FALSE);
    return time_taken;
}
