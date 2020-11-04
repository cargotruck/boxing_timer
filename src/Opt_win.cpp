//
// Opt_win.cpp
//

#include <fstream>
#include <string>
#include "../include/Opt_win.h"
#include "../include/Timer_Util.h"

//-------------------------------------------------------------------------

Timer_Util::Timer_Config conf;

//-------------------------------------------------------------------------

Opt_win::Opt_win(wxWindow* parent,const wxString& title,const wxPoint& pos,const wxSize& size)
    :wxFrame(parent,wxID_ANY,title,pos,size)
{
    parent = parent;
    Timer_Util::load_config(conf);
    
    wxFont font_label(14,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false);

    //declared in tab order    
    //rounds
    txt_num_rnd = new wxStaticText(this,wxID_ANY,"Total Rounds:",wxPoint(40,25),wxSize(130,30));
    in_num_rnd = new wxTextCtrl(this,11001,std::to_string(conf.total_rounds),wxPoint(175,20),wxSize(70,30));

    //round time
    txt_rnd = new wxStaticText(this,wxID_ANY,"Rounds:",wxPoint(30,65),wxSize(130,30));
    txt_rnd_min = new wxStaticText(this,wxID_ANY,"min:",wxPoint(120,65),wxSize(70,30));
    in_rnd_min = new wxTextCtrl(this,11002,std::to_string(conf.round_min),wxPoint(150,60),wxSize(70,30));
    txt_rnd_sec = new wxStaticText(this,wxID_ANY,"sec:",wxPoint(225,65),wxSize(70,30));
    in_rnd_sec = new wxTextCtrl(this,11003,std::to_string(conf.round_sec),wxPoint(255,60),wxSize(70,30));

    //rest time
    txt_rest = new wxStaticText(this,wxID_ANY,"Rest:",wxPoint(30,105),wxSize(130,30));
    txt_rest_min = new wxStaticText(this,wxID_ANY,"min:",wxPoint(120,110),wxSize(70,30));
    in_rest_min = new wxTextCtrl(this,11004,std::to_string(conf.rest_min),wxPoint(150,105),wxSize(70,30));
    txt_rest_sec = new wxStaticText(this,wxID_ANY,"sec:",wxPoint(225,110),wxSize(70,40));
    in_rest_sec = new wxTextCtrl(this,11005,std::to_string(conf.rest_sec),wxPoint(255,105),wxSize(70,30));

    //blitz
    txt_blitz = new wxStaticText(this,wxID_ANY,"Blitz:",wxPoint(30,160),wxSize(130,30));

    txt_blitz_freq = new wxStaticText(this,wxID_ANY,"Frequency:",wxPoint(120,160),wxSize(70,30));
    cmb_blitz_freq = new wxComboBox(this,11006,std::to_string(conf.blitz_freq),wxPoint(120,160),wxSize(70,30),
                                    0,nullptr,0,wxTextValidator(wxFILTER_DIGITS));
    txt_blitz_min = new wxStaticText(this,wxID_ANY,"min:",wxPoint(120,205),wxSize(70,30));
    in_blitz_min = new wxTextCtrl(this,11007,std::to_string(conf.blitz_min),wxPoint(150,200),wxSize(70,30));
    txt_blitz_max = new wxStaticText(this,wxID_ANY,"max:",wxPoint(225,205),wxSize(70,30));
    in_blitz_max = new wxTextCtrl(this,11008,std::to_string(conf.blitz_max),wxPoint(255,200),wxSize(70,30));

    //buttons
    btn_save = new wxButton(this,11009,"SAVE",wxPoint((400 / 2) + 10,400 - 80),wxSize(100,50));
    btn_back = new wxButton(this,11010,"BACK",wxPoint((400 / 2) - 110,400 - 80),wxSize(100,50));

    for(int i = 0;i < 11;++i) {cmb_blitz_freq->Append(std::to_string(i));} //fill combo box 0-10

    txt_num_rnd->SetFont(font_label);
    txt_rnd->SetFont(font_label);
    txt_rest->SetFont(font_label);
    txt_blitz->SetFont(font_label);
};

//-------------------------------------------------------------------------

Opt_win::~Opt_win() {};

//-------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(Opt_win,wxFrame)
    EVT_BUTTON(11009,Opt_win::on_save)
    EVT_BUTTON(11010,Opt_win::on_back)
wxEND_EVENT_TABLE()

//-------------------------------------------------------------------------

void Opt_win::on_save(wxCommandEvent& event)
{
    std::string cfg_file = "/opt/boxing_timer/timer.config";
    int num_rnd = wxAtoi(in_num_rnd->GetValue());
    int rnd_min = wxAtoi(in_rnd_min->GetValue());
    int rnd_sec = wxAtoi(in_rnd_sec->GetValue());
    int rest_min = wxAtoi(in_rest_min->GetValue());
    int rest_sec = wxAtoi(in_rest_sec->GetValue());
    int blitz_freq = wxAtoi(cmb_blitz_freq->GetValue());
    int blitz_min = wxAtoi(in_blitz_min->GetValue());
    int blitz_max = wxAtoi(in_blitz_max->GetValue());

    if(num_rnd < 0) {num_rnd = 0;}
    if(rnd_min < 0) {rnd_min = 0;}
    if(rnd_sec < 0) {rnd_sec = 0;}
    if(rest_min < 0) {rest_min = 0;}
    if(rest_sec < 0) {rest_sec = 0;}
    if(blitz_freq < 0 || blitz_freq > 10) {blitz_freq = 0;}
    if(blitz_min < 0) {blitz_min = 0;}
    if(blitz_max < 0) {blitz_max = 0;}

    std::ofstream ofs{cfg_file};

    ofs << "total_rounds " << '{' << num_rnd << ':' << '0' << '}' << std::endl;
    ofs << "round " << '{' << rnd_min << ':' << rnd_sec << '}' << std::endl;
    ofs << "rest " << '{' << rest_min << ':' << rest_sec << '}' << std::endl;
    ofs << "blitz_freq " << '{' << blitz_freq << ':' << '0' << '}' << std::endl;
    ofs << "blitz_min_max " << '{' << blitz_min << ':' << blitz_max << '}' << std::endl;
    ofs.close();
}

//-------------------------------------------------------------------------

void Opt_win::on_back(wxCommandEvent& event)
{
    Destroy();
}
