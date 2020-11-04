//
//
// Blitz.h
//
//

//TODO: 1. ensure the min is lower than the max


#ifndef BLITZ_H
#define BLITZ_H

#include <random>

class Blitz
{
public:
    Blitz(int _freq,int _min,int _max)
        :freq{_freq * multiplier},min{_min},max{_max}
    {}

    ~Blitz() {};

    bool is_blitz();
    int get_blitz();    

private:
    int multiplier = 5;
    int freq;
    int min;
    int max;
};



#endif //BLITZ_H
