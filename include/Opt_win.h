//
//
// Opt_Win.h
//
//

#ifndef OPT_WIN_H
#define OPT_WIN_H

#include <wx/wx.h>
#include "./Clock_win.h"

class Clock_win;

class Opt_win : public wxFrame
{
public:
    Opt_win(wxWindow* parent,const wxString& title,const wxPoint& pos,const wxSize& size);
    ~Opt_win();

    //event handlers
    void on_save(wxCommandEvent& event);
    void on_back(wxCommandEvent& event);

private:

    Clock_win* parent = nullptr;

    wxButton* btn_save = nullptr;
    wxButton* btn_back = nullptr;

    wxComboBox* cmb_blitz_freq = nullptr;

    wxTextCtrl* in_blitz_min = nullptr;
    wxTextCtrl* in_blitz_max = nullptr;
    wxTextCtrl* in_num_rnd = nullptr;
    wxTextCtrl* in_rest_min = nullptr;
    wxTextCtrl* in_rest_sec = nullptr;
    wxTextCtrl* in_rnd_min = nullptr;
    wxTextCtrl* in_rnd_sec = nullptr;

    wxStaticText* txt_blitz = nullptr;
    wxStaticText* txt_blitz_freq = nullptr;
    wxStaticText* txt_blitz_min = nullptr;
    wxStaticText* txt_blitz_max = nullptr;
    wxStaticText* txt_num_rnd = nullptr;
    wxStaticText* txt_rest = nullptr;
    wxStaticText* txt_rest_min = nullptr;
    wxStaticText* txt_rest_sec = nullptr;
    wxStaticText* txt_rnd = nullptr;
    wxStaticText* txt_rnd_min = nullptr;
    wxStaticText* txt_rnd_sec = nullptr;

    wxDECLARE_EVENT_TABLE();
};

#endif //OPT_WIN_H
