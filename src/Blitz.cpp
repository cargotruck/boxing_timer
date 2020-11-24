//
//
// Blitz.cpp
//
//

#include <chrono>
#include "../include/Blitz.h"

bool Blitz::is_blitz()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(1,100);

    if(distribution(generator) < freq) {return true;}

    return false;
}

int Blitz::get_blitz()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(min,max);
    
    return distribution(generator); 
}
