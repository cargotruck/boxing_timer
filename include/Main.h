//
// app.h
//

#include <wx/wx.h>
#include "./Clock_win.h"

class Application : public wxApp
{
public:
    Application();
    ~Application();

    virtual bool OnInit();

private:
    Clock_win* main_win = nullptr;
};
