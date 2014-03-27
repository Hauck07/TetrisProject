#include "Tetris.h"


Tetris::Tetris()
{
    Running = false;
    Display = NULL;
    CurrentState = NULL;
}

bool Tetris::LoadResources()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;

    if((Display = SDL_SetVideoMode(500, 560, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) return false;

    SDL_WM_SetCaption("Tetris", "Tetris");
    StateID = STATE_START_MENU;
    CurrentState = new StartMenu();

    return true;
}

int Tetris::Execute()
{
    const int FPS = 50;

    if(LoadResources() == false)
        return -1;

    while(StateID != STATE_EXIT){

        int Start = SDL_GetTicks();

        CurrentState->HandleEvent();

        CurrentState->Update();

        UpdateState();

        CurrentState->Render(Display);

        SDL_Flip(Display);

        while(1000/FPS > SDL_GetTicks()-Start)
            SDL_Delay(1000/FPS-(SDL_GetTicks()-Start));
    }

    return 0;
}

void Tetris::UpdateState()
{
    if(CurrentState->NextState != STATE_NULL){

        int NextStateID = CurrentState->NextState;
        ReturnParameter* Info = CurrentState->ExitParameters();

        if(CurrentState->NextState != STATE_EXIT)
            delete CurrentState;

        switch(NextStateID){
            case STATE_START_MENU:
                CurrentState = new StartMenu();
                break;

            case STATE_MAIN_GAME:
                CurrentState = new MainGame();
                break;

            case STATE_HIGH_SCORE:
                CurrentState = new Highscore(Info);
                break;
        }

        StateID = NextStateID;
    }
}

Tetris::~Tetris()
{
    SDL_FreeSurface(Display);
    delete CurrentState;
    SDL_Quit();
}

int main(int argc, char* argv[]) {

    Tetris TetrisGame;

    return TetrisGame.Execute();
}
