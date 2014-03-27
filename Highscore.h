#ifndef HIGHSCORE_H_INCLUDED
#define HIGHSCORE_H_INCLUDED
#include "GameState.h"
#include <SDL/SDL_ttf.h>
#include <cstdio> //used for casting string to char*
#include "HighscoreBoard.h"
#include <sstream>

class Highscore: public GameState{
    private:
        SDL_Surface* Graphics;

        SDL_RWops* HighscoreFile;

        HighscoreBoard* HighscoreData;

        TTF_Font *Font;

        SDL_Color* TextColor;

    public:
        Highscore(ReturnParameter* Parameter);

        void HandleEvent();

        void Update();

        void Render(SDL_Surface* Display);

        void  MouseLeftClick(int X, int Y);

        ReturnParameter* ExitParameters();

        ~Highscore();
};

#endif // HIGHSCORE_H_INCLUDED
