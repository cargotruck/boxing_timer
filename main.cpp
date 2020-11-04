//
// main.cpp
//

#include "./include/Main.h"
#include "./include/Countdown.h"

wxIMPLEMENT_APP(Application);

Application::Application() {};

Application::~Application() {};

bool Application::OnInit()
{
    main_win = new Clock_win("Boxing Timer",wxPoint(200,200),wxSize(400,400));
    main_win->SetMinSize(wxSize(400,400));
    main_win->SetMaxSize(wxSize(400,400));

    Countdown* countdown = new Countdown;

    main_win->set_countdown(countdown);
    countdown->set_clock(main_win);

    main_win->Show();    
 
    return true;
}
