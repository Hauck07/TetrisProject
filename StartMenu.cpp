#include "StartMenu.h"

StartMenu::StartMenu()
{
    Graphics = SurfaceHandler::OnLoad((char*)"./Graphics/Graphics_StartMenu.png");
}

void StartMenu::HandleEvent()
{

    SDL_Event Event;
    while(SDL_PollEvent(&Event)){
        switch(Event.type){
            case SDL_QUIT:
                NextState = STATE_EXIT;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(Event.button.button == SDL_BUTTON_LEFT)
                    MouseLeftClick(Event.button.x, Event.button.y);
                break;
            default:
                break;
        }
    }
}

void StartMenu::Update()
{

}

void StartMenu::Render(SDL_Surface* Display)
{
    SurfaceHandler::OnDraw(Display, Graphics, 0, 0, 0, 0, 500, 560);
    SurfaceHandler::OnDraw(Display, Graphics, 0, 0, 500, 0, 500, 560);
}

ReturnParameter* StartMenu::ExitParameters()
{
    return NULL;
}

StartMenu::~StartMenu()
{
    SDL_FreeSurface(Graphics);
}

void  StartMenu::MouseLeftClick(int X, int Y)
{
    if(X > 110 && X < 385){
        if(Y > 310 && Y < 368)
            NextState = STATE_MAIN_GAME;

        if(Y > 392 && Y < 448)
            NextState = STATE_HIGH_SCORE;

        if(Y > 475 && Y < 532)
            NextState = STATE_EXIT;
    }
}
