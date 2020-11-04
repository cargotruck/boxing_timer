//
// Sound_fx.cpp
//

#include "../include/Sound_fx.h"

#include <iostream>

Sound_fx::Sound_fx(const std::string& file)// : sound_file{Mix_LoadWAV(file.c_str())}
{
    if(SDL_Init(SDL_INIT_AUDIO) != 0)
    {
        std::cerr << ERROR << file << std::endl;
        loading_error = true;
    }

    if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096) != 0)
    {
        std::cerr << ERROR << file << std::endl;
        loading_error = true;
    }
    
    sound_file = Mix_LoadWAV(file.c_str());

    if(sound_file == nullptr){
        std::cerr << ERROR << file << std::endl;
        loading_error = true;
    }
}

//-------------------------------------------------------------------------

Sound_fx::~Sound_fx() 
{
    Mix_FreeChunk(sound_file);
}

//-------------------------------------------------------------------------

void Sound_fx::play() const
{
    Mix_PlayChannel(1,sound_file,0);
}

//-------------------------------------------------------------------------

void Sound_fx::cleanup()
{
    Mix_FreeChunk(sound_file);
}
