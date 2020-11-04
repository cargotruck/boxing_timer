//
// Clock_win.h
//

#ifndef CLOCK_WIN_H
#define CLOCK_WIN_H

#include <wx/wx.h>
#include "./Countdown.h"
#include "./Opt_win.h"

class Countdown;
class Opt_win;

class Clock_win : public wxFrame
{
public:
    Clock_win(const wxString& title,const wxPoint& pos,const wxSize& size);
    ~Clock_win();

    wxStaticText* txt_clock = nullptr;
    wxStaticText* txt_round_counter = nullptr;
     
    //event handlers
    void on_opt(wxCommandEvent& event);
    void on_pause(wxCommandEvent& event);
    void on_pause();
    void on_resume(wxCommandEvent& event);
    void on_resume();
    void on_start(wxCommandEvent& event);
    void on_start();
    void on_stop(wxCommandEvent& event);
    void on_stop();

    void set_countdown(Countdown* cd);

    void update_clock(const std::string& t);
    void update_rounds(const std::string& r);


private:
    Countdown* countdown = nullptr;

    wxButton* btn_opt = nullptr;
    wxButton* btn_pause = nullptr;
    wxButton* btn_resume = nullptr;
    wxButton* btn_start = nullptr;
    wxButton* btn_stop = nullptr;


    Opt_win* opt_win = nullptr;
    
    wxDECLARE_EVENT_TABLE();
};

#endif //CLOCK_WIN_H
