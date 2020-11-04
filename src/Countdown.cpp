//
//  Countdown.cpp
//

#include <chrono>
#include <ctime>
#include <sstream>
#include <thread>
#include "Poco/DateTimeFormatter.h"
#include "Poco/Timestamp.h"
#include <wx/wx.h>
#include "../include/Blitz.h"
#include "../include/Countdown.h"
#include "../include/Sound_fx.h"

//-------------------------------------------------------------------------

Countdown::Countdown() 
{
    if(bell.loading_error) clock->Close(true);  
};

Countdown::~Countdown() {};

//-------------------------------------------------------------------------

void Countdown::set_clock(Clock_win* _clock)
{
    clock = _clock;
}

//-------------------------------------------------------------------------
// Interface methods used by Clock_win.
//-------------------------------------------------------------------------

void Countdown::pause()
{
    is_paused = true;
}

//-------------------------------------------------------------------------

void Countdown::reset()
{
    current_round = 1;
    make_round_active();
    is_paused = false;
}

//-------------------------------------------------------------------------

void Countdown::resume()
{
    run_round();
}

//-------------------------------------------------------------------------

void Countdown::start()
{
    is_stopped = false;
    Timer_Util::load_config(config);
    prep_clock();
    run_clock();
}

//-------------------------------------------------------------------------

void Countdown::stop()
{
    is_stopped = true;
    reset();
    update_round_display();
    set_time(config.round_min,config.round_sec);
    clock->update_clock(Poco::DateTimeFormatter::format(time,"%M:%S"));
    clock->Update();
}

//-------------------------------------------------------------------------
// various helper methods
//-------------------------------------------------------------------------

void Countdown::count_round()
{
    ++current_round;
}

//-------------------------------------------------------------------------

void Countdown::make_round_active(bool state)
{
    active_round = state;
}

//-------------------------------------------------------------------------

int Countdown::min_to_sec(int t)
{
    return t * 60;
}

//-------------------------------------------------------------------------

void Countdown::prep_clock()
{
    if(active_round)
    {
        if(current_round > config.total_rounds) 
        {
            reset(); 
            return;
        }
        
        update_round_display();
    }
}

//-------------------------------------------------------------------------

void Countdown::run_clock()
{
    while(current_round <= config.total_rounds)
    {
        if(active_round && !is_paused)
        {
            set_time(config.round_min,config.round_sec);
            update_round_display();
            if(current_round == 1) {bell.play();} //plays bell for first round, no other
        }else{
            set_time(config.rest_min,config.rest_sec);
        }

        run_round();

        if(is_paused || is_stopped) break;
    }
}

//-------------------------------------------------------------------------

void Countdown::run_blitz()
{
    if(blitz_time == 0){
        Blitz blitz{config.blitz_freq,config.blitz_min,config.blitz_max};
        
        if(blitz.is_blitz()) blitz_time = blitz.get_blitz();
    }

    if(blitz_time > 0 && time > 1){
        blitz_bell.play();
        --blitz_time;
    }
}

//-------------------------------------------------------------------------

void Countdown::run_round()
{
    is_paused = false;
    while(time >= 0 || !is_paused)
    {
        stop_if_closed();
        if(config.blitz_freq > 0 && active_round) run_blitz();
        tick_clock();

        if(is_paused || is_stopped) break;

        if(time == 0) 
        {
            bell.play(); //play bell only when time reaches 0
            if(active_round) count_round();
            make_round_active(switch_active_state());
            break;
        }
    }
}

//-------------------------------------------------------------------------

void Countdown::set_time(int min,int sec)
{
    Countdown::set_time(Poco::Timestamp{to_time(min,sec) * MICRO});
}

//-------------------------------------------------------------------------

void Countdown::set_time(const Poco::Timestamp& _time)
{
    time = _time;
}

//-------------------------------------------------------------------------

void Countdown::sleep(int t)
{
    std::this_thread::sleep_for(std::chrono::microseconds(t));
}

//-------------------------------------------------------------------------

void Countdown::stop_if_closed()
{
    if(!clock->IsShown()) Countdown::reset(); //if main window exits stop countdown loop
}

//-------------------------------------------------------------------------

bool Countdown::switch_active_state()
{
    if(active_round) return false;

    return true;
}

//-------------------------------------------------------------------------

void Countdown::tick_clock()
{
        wxYield();
        sleep(TENTH_SEC);
        clock->txt_clock->SetLabel(Poco::DateTimeFormatter::format(time,"%M:%S"));
        clock->Update();
        time -= TENTH_SEC;
}

//-------------------------------------------------------------------------

int Countdown::to_time(int m,int s)
{
    return min_to_sec(m) + s;
}

//-------------------------------------------------------------------------

void Countdown::update_round_display()
{
    std::stringstream ss;
    ss << "Round " << current_round << " / " << config.total_rounds;

    clock->update_rounds(ss.str());
}
