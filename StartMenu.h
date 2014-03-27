#ifndef STARTMENU_H_INCLUDED
#define STARTMENU_H_INCLUDED
#include "GameState.h"

class StartMenu : public GameState{

    private:
        SDL_Surface* Graphics;

    public:

        StartMenu();

        void HandleEvent();

        void Update();

        void MouseLeftClick(int X, int Y);

        void Render(SDL_Surface* Display);

        ReturnParameter* ExitParameters();

        ~StartMenu();
};

#endif // STARTMENU_H_INCLUDED
