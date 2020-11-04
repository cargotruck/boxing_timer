//
// Sound_fx.h
//

#ifndef SOUND_FX_H
#define SOUND_FX_H

#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

class Sound_fx
{
public:
    Sound_fx(const std::string& file);
    ~Sound_fx();

    bool loading_error = false;
    const std::string ERROR = "ERROR: There was a problem loading the audio files or module.";

    void play() const;
    void cleanup();

private:
    Mix_Chunk* sound_file = nullptr;
};

#endif //SOUND_FX_H
