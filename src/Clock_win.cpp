//
// Clock_win.cpp
//

#include <fstream>
#include <string>
#include <sstream>
#include "../include/Clock_win.h"
#include "../include/Timer_Util.h"

//-------------------------------------------------------------------------

Timer_Util::Timer_Config config;

//-------------------------------------------------------------------------

Clock_win::Clock_win(const wxString& title,const wxPoint& pos,const wxSize& size)
    :wxFrame(nullptr,wxID_ANY,title,pos,size)
{
    wxFont font_clock(48,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false);
    wxFont font_rnds(16,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false);

    //defined in tab order   
    btn_start = new wxButton(this,10001,"START",wxPoint((400 / 2) + 10,400 - 80),wxSize(100,50));
    btn_stop = new wxButton(this,10002,"STOP",wxPoint((400 / 2) - 110,400 - 80),wxSize(100,50));
    btn_pause = new wxButton(this,10004,"PAUSE",wxPoint((400 / 2) + 10,400 - 80),wxSize(100,50));
    btn_resume = new wxButton(this,10003,"RESUME",wxPoint((400 / 2) + 10,400 - 80),wxSize(100,50));
    btn_opt = new wxButton(this,10005,"OPTIONS",wxPoint(10,10),wxSize(100,50)); 

    txt_clock = new wxStaticText(this,10006,"00:00",wxPoint(100,75),wxSize(100,100));
    txt_round_counter = new wxStaticText(this,10007,"ROUND 0/0",wxPoint(130,150),wxSize(100,100));

    txt_clock->SetFont(font_clock);
    txt_round_counter->SetFont(font_rnds);

    btn_resume->Enable(false);
    btn_pause->Enable(false);
    btn_resume->Hide();
    btn_pause->Hide();
}

//-------------------------------------------------------------------------

Clock_win::~Clock_win() {};

//-------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(Clock_win,wxFrame)
    EVT_BUTTON(10001,Clock_win::on_start)
    EVT_BUTTON(10002,Clock_win::on_stop)
    EVT_BUTTON(10003,Clock_win::on_resume)
    EVT_BUTTON(10004,Clock_win::on_pause)
    EVT_BUTTON(10005,Clock_win::on_opt)
wxEND_EVENT_TABLE()

//-------------------------------------------------------------------------

void Clock_win::on_opt(wxCommandEvent& event)
{

    wxPoint parent_coord = ClientToScreen(GetClientAreaOrigin());

    opt_win = new Opt_win(this,"Options",wxPoint(parent_coord.x + 100,parent_coord.y + 100),wxSize(400,400));
    opt_win->SetMinSize(wxSize(400,400));
    opt_win->SetMaxSize(wxSize(400,400));
    opt_win->Show();
}

//-------------------------------------------------------------------------

void Clock_win::on_pause(wxCommandEvent& event)
{
    on_pause();
}

//-------------------------------------------------------------------------

void Clock_win::on_pause()
{
    btn_pause->Enable(false);
    btn_pause->Hide();
    btn_resume->Enable(true);
    btn_resume->Show();

    countdown->pause();
}

//-------------------------------------------------------------------------

void Clock_win::on_resume(wxCommandEvent& event)
{
    on_resume();
}

//-------------------------------------------------------------------------

void Clock_win::on_resume()
{
    btn_resume->Enable(false);
    btn_resume->Hide();
    btn_pause->Enable(true);
    btn_pause->Show();
 
    countdown->resume();
}

//-------------------------------------------------------------------------

void Clock_win::on_start(wxCommandEvent& event)
{
    on_start();
}

//-------------------------------------------------------------------------

void Clock_win::on_start()
{
    btn_start->Enable(false);
    btn_start->Hide();
    btn_pause->Enable(true);
    btn_pause->Show(); 
 
    countdown->start();
}

//-------------------------------------------------------------------------

void Clock_win::on_stop(wxCommandEvent& event)
{
    on_stop();
}

//-------------------------------------------------------------------------

void Clock_win::on_stop()
{
    if(btn_pause->IsShown()){
        btn_pause->Enable(false);
        btn_pause->Hide();
    }

    if(btn_resume->IsShown()){
        btn_resume->Enable(false);
        btn_resume->Hide();
    }
    
    btn_start->Enable(true);
    btn_start->Show();


    countdown->stop();
}

//-------------------------------------------------------------------------

void Clock_win::set_countdown(Countdown* cd)
{
    countdown = cd;
}
//-------------------------------------------------------------------------

void Clock_win::update_clock(const std::string& t)
{
    txt_clock->SetLabel(t);
}

//-------------------------------------------------------------------------

void Clock_win::update_rounds(const std::string& r)
{
    txt_round_counter->SetLabel(r);
}
