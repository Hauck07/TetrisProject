#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED

/*
Including libraries and predefined stuff
*/
#include <SDL/SDL.h>
#include "Define.h"

/*
Including GameStates
*/
#include "GameState.h"
#include "StartMenu.h"
#include "Highscore.h"
#include "MainGame.h"

/*
Including Remaining Stuff
*/
#include "ReturnParameter.h"


class Tetris{
    public:

        SDL_Surface* Display;

        GameState* CurrentState;

        bool Running;

        int StateID;

    public:

        Tetris();

        bool LoadResources();

        int Execute();

        void UpdateState();

        void Cleanup();

        ~Tetris();
};

#endif // TETRIS_H_INCLUDED
