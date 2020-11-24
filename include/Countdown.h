//
//  Countdown_Timer.h
//

#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include "Poco/Timestamp.h"
#include "./Sound_fx.h"

#include "./Clock_win.h"
#include "./Timer_Util.h"

//Forward declarations
class Clock_win;
class Sound_fx;

//-------------------------------------------------------------------------


//-------------------------------------------------------------------------

class Countdown
{
public:
    Countdown();
    ~Countdown();
   
    void set_clock(Clock_win* _clock);

    // Interface methods used by Clock_win.
    void pause();
    void reset();
    void resume();
    void start();
    void stop();

private:
    const int MICRO = 1000000;
    const int TENTH_SEC = 100000;
    const Sound_fx bell{"./sfx/bell_1.wav"};
    const Sound_fx blitz_bell{"./sfx/blitz_1.wav"};

    bool active_round = true;
    int blitz_time = 0;
    int check_for_blitz = MICRO;
    Clock_win* clock = nullptr;
    Timer_Util::Timer_Config config;
    bool is_paused = false;
    bool is_stopped = false;
    int current_round = 1;
    Poco::Timestamp time = 0;
   
    //various helper methods 
    void count_round();
    void make_round_active(bool state = true);
    int min_to_sec(int t);
    void prep_clock();
    void run_clock();
    void run_blitz();
    void run_round();
    void set_time(int min,int sec);
    void set_time(const Poco::Timestamp& _ts);
    void sleep(int t);
    void stop_if_closed();
    bool switch_active_state();
    void tick_clock();
    int to_time(int m,int s);
    void update_round_display();
};

#endif //COUNTDOWN_TIMER_H
