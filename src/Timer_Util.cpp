//
//
// Timer_Util.cpp
//
//

#include <fstream>
#include <string>
#include <sstream>
#include "../include/Timer_Util.h"

using namespace Timer_Util;

void Timer_Util::load_config(Timer_Config& tc)
{
    const std::string TOTAL_ROUNDS = "total_rounds";
    const std::string ROUND = "round";
    const std::string REST = "rest";
    const std::string BLITZ_FREQ = "blitz_freq";
    const std::string BLITZ_MM = "blitz_min_max";
    const char s_brak = '{';
    const char e_brak = '}';
    const char div = ':';

    std::string name;
    char ch1,ch2,ch3;
    int min;
    int sec;

    std::string cfg_file = "/opt/boxing_timer/timer.config"; // this is also hard coded in Opt_Win.cpp
    std::ifstream ifs{cfg_file};

    if(!ifs) {return;} //clock will use default values of Timer_Config
  
    std::string line;
    while(std::getline(ifs,line)){ 
        std::stringstream ss{line};
        if(ss >> name >> ch1 >> min >> ch2 >> sec >> ch3){
            
            if(name == TOTAL_ROUNDS){
                tc.total_rounds = min; //to keep it consistant, really means the first entry
            }
    
            if(name == ROUND){
                tc.round_min = min;
                tc.round_sec = sec;
            }

            if(name == REST){
                tc.rest_min = min;
                tc.rest_sec = sec;
            }

            if(name == BLITZ_FREQ){
                tc.blitz_freq = min; //to keep it consistant, really means the first entry
            }

            if(name == BLITZ_MM){
                tc.blitz_min = min;
                tc.blitz_max = sec; //to keep it consistant, really means max
            }
        }
    }
}


