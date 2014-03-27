#ifndef SOUNDBANK_H_INCLUDED
#define SOUNDBANK_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <vector>


class SoundBank{
    public:
        std::vector<Mix_Chunk*>     SoundList;

    public:
        SoundBank();

        int Load(char* File);

        void OnCleanup();

        void Play(std::size_t ID);

};

#endif // CSOUNDBANK_H_INCLUDED
