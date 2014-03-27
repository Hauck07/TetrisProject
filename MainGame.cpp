#include "MainGame.h"

MainGame::MainGame()
{
    //initialize graphics related stuff
    Graphics = SurfaceHandler::OnLoad((char*)"./Graphics/Graphics_MainGame.png");
    Pieces = SurfaceHandler::OnLoad((char*)"./Graphics/Graphics_Pieces.png");
    //initialize font related stuff
    TTF_Init();
    Font = TTF_OpenFont("./Fonts/FrancophilSans.ttf", 16);
    TextColor = new SDL_Color();
    TextColor->b = TextColor->g = TextColor->r = 0;
    //initialize sound related stuff
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512);
    SoundControl = new SoundBank();
    SoundControl->Load((char*)"./Sound/Blop.wav");
    SoundControl->Load((char*)"./Sound/GameOver.wav");
    SDL_EnableUNICODE(SDL_ENABLE);
    // initialize game related stuff
    std::fill_n(CurrentInfo, 4, 0);
    CurrentInfo[LEVEL] = 1;
    MovingDown = MovingLeft = MovingRight = GameOver = false;
    MainTimeCounter = KeyPressTimeCounter = 0;
    srand(time(NULL)); // generating random seed
    MessageControl = new BonusMessage;
    MessageControl->OnInit();
    ScreenBoard = new Board();
    PreviewBlock = new BlockJ();
    ResetBlock();
}

void MainGame::HandleEvent()
{
    SDL_Event Event;
    while(SDL_PollEvent(&Event)){
        switch(Event.type){
            case SDL_QUIT:
                NextState = STATE_EXIT;
                break;
            case SDL_KEYDOWN:
                KeyPress(Event.key.keysym.sym, Event.key.keysym.mod, Event.key.keysym.unicode);
                break;
            case SDL_KEYUP:
                KeyRelease(Event.key.keysym.sym, Event.key.keysym.mod, Event.key.keysym.unicode);
            default: { break; }
        }
    }
}

void MainGame::Update()
{
    if(GameOver) return;
    MessageControl->OnLoop();

    int* Result = ScreenBoard->CheckLine();
    if(Result[0] != 0){
        CurrentInfo[LINES] += Result[0];
        CurrentInfo[SCORE] += Result[1] * Result[2];
        if(Result[2] > 1)
            MessageControl->SetLineComboMessage(Result[2]- 2);
        if(Result[3] != 0){
            CurrentInfo[SCORE] += Result[3] * 30;
            MessageControl->SetColorMatchMessage(Result[3] - 1);
        }
        if(CurrentInfo[LEVEL] < 20){
            if(CurrentInfo[LINES] >= LevelTable[CurrentInfo[LEVEL]]){
                CurrentInfo[LEVEL]++;
            }
        }
        SoundControl->Play(SFX_LINE_COMPLETED);
    }
    free(Result);

    if(KeyPressTimeCounter + 200 < SDL_GetTicks()){
        KeyPressTimeCounter = SDL_GetTicks();
        if(MovingLeft) CurrentBlock->Move(0, -1, ScreenBoard->Squares);
        if(MovingRight) CurrentBlock->Move(0, 1, ScreenBoard->Squares);
        if(MovingDown){
            if(CurrentBlock->Move(1, 0, ScreenBoard->Squares) == false){
                ScreenBoard->MergeBlock(CurrentBlock->Block, CurrentBlock->X, CurrentBlock->Y, CurrentBlock->Color);
                ResetBlock();
            }
        }
    }

    if(MainTimeCounter + (1000 - CurrentInfo[LEVEL]*45) < SDL_GetTicks()){
        MainTimeCounter = SDL_GetTicks();

        if(ScreenBoard->CheckBlockDown(CurrentBlock->Block, CurrentBlock->X, CurrentBlock->Y)){
            ScreenBoard->MergeBlock(CurrentBlock->Block, CurrentBlock->X, CurrentBlock->Y, CurrentBlock->Color);
            ResetBlock();
        }
        else{
            CurrentBlock->X++;
        }

    }

}

void MainGame::Render(SDL_Surface* Display)
{
    SurfaceHandler::OnDraw(Display, Graphics, 0, 0, 0, 0, 500, 560);
    SurfaceHandler::OnDraw(Display, Graphics, 0, 0, 500, 0, 500, 560);
    char buffer[15];
    SDL_Surface* TextLoader;
    for(int index = 0; index < 4; index++){
        sprintf(buffer, "%d", CurrentInfo[index]);
        TextLoader = TTF_RenderText_Blended(Font, buffer, *TextColor);
        SurfaceHandler::OnDraw(Display, TextLoader, 400, 220 + index*80);
        SDL_FreeSurface(TextLoader);
    }
    ScreenBoard->OnRender(Display, Pieces);
    CurrentBlock->OnRender(Display, Pieces);
    PreviewBlock->OnRenderPreview(Display, Pieces);
    MessageControl->OnRender(Display);
    if(GameOver){
        SurfaceHandler::OnDraw(Display, Graphics, 50, 150, 1024, 0, 1424, 200);
        sprintf(buffer, "%s", PlayerName.c_str());
        TextLoader = TTF_RenderText_Blended(Font, buffer, *TextColor);
        SurfaceHandler::OnDraw(Display, TextLoader, 195, 272);
        SDL_FreeSurface(TextLoader);
    }
}

void MainGame::ResetBlock()
{
    CurrentBlock = PreviewBlock;

    if(ScreenBoard->CheckBlock(CurrentBlock->Block, CurrentBlock->X, CurrentBlock->Y)){
        GameOver = true;
        SoundControl->Play(SFX_GAME_OVER);
    }

    switch(rand() % 7){
        case 0:
            PreviewBlock = new BlockL;
            break;
        case 1:
            PreviewBlock = new BlockJ;
            break;
        case 2:
            PreviewBlock = new BlockS;
            break;
        case 3:
            PreviewBlock = new BlockZ;
            break;
        case 4:
            PreviewBlock = new BlockI;
            break;
        case 5:
            PreviewBlock = new BlockT;
            break;
        default:
            PreviewBlock = new BlockSquare;
           break;
    }
}

void MainGame::KeyPress(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    if(GameOver){
        if(sym == SDLK_BACKSPACE){
            if(!PlayerName.empty())
                PlayerName.erase(PlayerName.length() - 1);
        }
        else if(sym == SDLK_RETURN || sym == SDLK_KP_ENTER){
                if(!PlayerName.empty()){
                   NextState = STATE_HIGH_SCORE;
                }
        }

        else{
                if(PlayerName.length() == 0 && unicode == ' ')
                    return;
                if(PlayerName.length() < 15){
                    if(unicode == ' ' || (unicode >= 'a' && unicode <= 'z') || (unicode >= 'A' && unicode <= 'Z') || (unicode >= '0' && unicode <= '9'))
                        PlayerName += (char)unicode;
                }
        }

    }
    else{
        switch(sym){
            case SDLK_LEFT:{
                MovingLeft = true;
                CurrentBlock->Move(0, -1, ScreenBoard->Squares);
                break;
            }
            case SDLK_RIGHT:{
                MovingRight = true;
                CurrentBlock->Move(0, 1, ScreenBoard->Squares);
                break;
            }
            case SDLK_DOWN:{
                MovingDown = true;
                if(CurrentBlock->Move(1, 0, ScreenBoard->Squares) == false){
                    ScreenBoard->MergeBlock(CurrentBlock->Block, CurrentBlock->X, CurrentBlock->Y, CurrentBlock->Color);
                    ResetBlock();
                }
                break;
            }
            case SDLK_UP:{
                CurrentBlock->Turn(ScreenBoard->Squares);
                break;
            }
            case SDLK_SPACE:{
                while(CurrentBlock->Move(1, 0, ScreenBoard->Squares)){}
            }
            default: {
                break;
            }
        }
        KeyPressTimeCounter = SDL_GetTicks();
    }

}

void MainGame::KeyRelease(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch(sym){
        case SDLK_LEFT:{
            MovingLeft = false;
            break;
        }
        case SDLK_RIGHT:{
            MovingRight = false;
            break;
        }
        case SDLK_DOWN:{
            MovingDown = false;
            break;
        }
        default: {
            break;
        }
    }
}

ReturnParameter* MainGame::ExitParameters(){
    ReturnParameter* Temp = new PlayerData(PlayerName, CurrentInfo[SCORE]);
    Temp->Empty = false;
    return Temp;
    return NULL;
}

MainGame::~MainGame()
{
    MessageControl->OnCleanup();
    SoundControl->OnCleanup();
    Mix_CloseAudio();
    SDL_FreeSurface(Graphics);
    SDL_FreeSurface(Pieces);
    delete ScreenBoard;
    delete TextColor;
    SDL_EnableUNICODE(SDL_DISABLE);
    TTF_Quit();
}
