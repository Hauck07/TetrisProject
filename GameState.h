#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED
#include <SDL/SDL.h>
#include "Define.h"

#include "SurfaceHandler.h"
#include "ReturnParameter.h"
#include "PlayerData.h"

class GameState{

    public:
        int NextState;

    public:
        GameState(){ NextState = STATE_NULL; }

        virtual void HandleEvent() = 0;

        virtual void Update() = 0;

        virtual void Render(SDL_Surface* Display) = 0;

        virtual ReturnParameter* ExitParameters() = 0;

        virtual ~GameState(){};
};


#endif // GAMESTATE_H_INCLUDED
