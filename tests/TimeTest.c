#define USE_TIME_MODULE

#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
#include "..\engine\BoardGamr.h"
#else
#include "../engine/BoardGamr.h"
#endif

int main(void)
{
    BG_EnableLogs();
     BG_StartTime();/*Start the timer.*/
    volatile unsigned int mili_seconds = 0;
    volatile float seconds = 0;

    /*Start the loop and print time delay from 100ms to 3000ms.*/
    for(mili_seconds = 100; mili_seconds <= 1000;mili_seconds+=200){
    printf("This is time delay of ");
    BG_TimeDelay(mili_seconds);
    seconds = ((float)mili_seconds/1000);
    printf("%0.2f seconds.\n",seconds);
    }

    printf("It took %0.2f seconds to run this test\n",BG_StopTime()); /*Stop the timer.*/
    return 0;
}
