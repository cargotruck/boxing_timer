//
//
// Timer_Utils.h
//
//

#ifndef TIMER_UTIL_H
#define TIMER_UTIL_H

namespace Timer_Util{

struct Timer_Config
{
    bool is_set = false;
    int total_rounds = 0;
    int round_min = 3;
    int round_sec = 0;
    int rest_min = 0;
    int rest_sec = 5;
    int blitz_freq = 0;
    int blitz_min = 0;
    int blitz_max = 0;
};

//-------------------------------------------------------------------------

void load_config(Timer_Config& tc);

} //end namespace Timer_Util

#endif //TIMER_UTIL_H
