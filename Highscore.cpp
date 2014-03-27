#include "Highscore.h"

Highscore::Highscore(ReturnParameter* Parameter)
{
    Graphics = SurfaceHandler::OnLoad((char*)"./Graphics/Graphics_Highscore.png");
    HighscoreFile = SDL_RWFromFile("Highscore", "rb+");

    HighscoreData = new HighscoreBoard();
    HighscoreData->Total = 10;

    for(int index = 0; index < 10; index++){
        char buffer[16];
        HighscoreFile->seek(HighscoreFile, index*23, RW_SEEK_SET);
        if(1 != HighscoreFile->read(HighscoreFile, buffer, 16, 1)){
            HighscoreData->Total = index;
            break;
        }
        buffer[16] = '\0';
        HighscoreData->Names[index] = std::string(buffer);
        HighscoreFile->seek(HighscoreFile, index*23+16, RW_SEEK_SET);
        HighscoreFile->read(HighscoreFile, buffer, 7, 1);
        buffer[7] = '\0';
        HighscoreData->Scores.push_back(atoi(buffer));
    }

    HighscoreFile->close(HighscoreFile);

    if(Parameter != NULL){
        PlayerData* Info = dynamic_cast<PlayerData*>(Parameter);
        int PositionToAdd = -1;
        for(int i = 0; i < HighscoreData->Total; i++){
            if(Info->Score > HighscoreData->Scores[i]){
                PositionToAdd = i;
                break;
            }
        }

        if(PositionToAdd != -1){
            for(int index = HighscoreData->Total-1; index > PositionToAdd; index--){
                HighscoreData->Scores[index] = HighscoreData->Scores[index-1];
                HighscoreData->Names[index] = HighscoreData->Names[index-1];
            }
            HighscoreData->Scores[PositionToAdd] = Info->Score;
            HighscoreData->Names[PositionToAdd] = Info->PlayerName;
            HighscoreData->Total += 1;
        }
        else if(HighscoreData->Total < 10){
            HighscoreData->Total += 1;
            HighscoreData->Scores[HighscoreData->Total-1] = Info->Score;
            HighscoreData->Names[HighscoreData->Total-1] = Info->PlayerName;

        }

        HighscoreFile = SDL_RWFromFile("Highscore", "w+");
        for(int i = 0; i < HighscoreData->Total; i++){
            HighscoreData->Names[i].resize(16, ' ');
            HighscoreFile->write(HighscoreFile, HighscoreData->Names[i].c_str(), 16, 1);
            std::stringstream stream;
            stream << HighscoreData->Scores[i];
            std::string save = stream.str();
            save.resize(5, ' ');
            save += '\r';
            save += '\n';
            HighscoreFile->write(HighscoreFile, save.c_str(), 7, 1);
        }
        HighscoreFile->close(HighscoreFile);

    }

    TTF_Init();
    Font = TTF_OpenFont("./Fonts/FrancophilSans.ttf", 16);
    TextColor = new SDL_Color;
    TextColor->b = TextColor->g = TextColor->r = 0;


}

void Highscore::HandleEvent()
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


void Highscore::Update()
{

}

void Highscore::Render(SDL_Surface* Display)
{
    SurfaceHandler::OnDraw(Display, Graphics, 0, 0, 0, 0, 500, 560);
    SurfaceHandler::OnDraw(Display, Graphics, 0, 0, 500, 0, 500, 560);

    char Names[15], Scores[10];
    SDL_Surface* Aux;
    for(int index = 0; index < HighscoreData->Total; index++){
        sprintf(Names, "%s", HighscoreData->Names[index].c_str());
        sprintf(Scores, "%d", HighscoreData->Scores[index]);
        Aux = TTF_RenderText_Blended(Font, Names, *TextColor);
        SurfaceHandler::OnDraw(Display, Aux, 100, 100+25*index);
        SDL_FreeSurface(Aux);
        Aux = TTF_RenderText_Blended(Font, Scores, *TextColor);
        SurfaceHandler::OnDraw(Display, Aux, 250, 100+25*index);
        SDL_FreeSurface(Aux);
    }

}

ReturnParameter* Highscore::ExitParameters()
{
    return new ReturnParameter;
}

Highscore::~Highscore()
{
    SDL_FreeSurface(Graphics);
}

void  Highscore::MouseLeftClick(int X, int Y)
{
    if(X > 138 && X < 360)
        if(Y > 482 && Y < 530)
            NextState = STATE_START_MENU;
}
