#ifndef MAINGAME_H_INCLUDED
#define MAINGAME_H_INCLUDED
#include "GameState.h"
#include "Define.h"

#include <SDL/SDL_ttf.h>
#include <algorithm> // used to fill arrays with some value
#include <ctime> //used for generating random seed
#include <string>
#include <vector>

#include "Board.h"
#include "SoundBank.h"
#include "BonusMessage.h"

#include "BlockPiece.h"
#include "BlockSquare.h"
#include "BlockL.h"
#include "BlockJ.h"
#include "BlockS.h"
#include "BlockZ.h"
#include "BlockI.h"
#include "BlockT.h"

const int LevelTable[20] = { 0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95 };

class MainGame: public GameState{
    private:
        SDL_Surface* Graphics;

        SDL_Surface* Pieces;

        TTF_Font* Font;

        SDL_Color* TextColor;

        SoundBank* SoundControl;

        BonusMessage* MessageControl;

        Board* ScreenBoard;

        BlockPiece* CurrentBlock;

        BlockPiece* PreviewBlock;

        int CurrentInfo[4];

        bool MovingRight, MovingLeft, MovingDown;

        bool GameOver;

        std::size_t MainTimeCounter, KeyPressTimeCounter;

        std::string PlayerName;

    public:

        MainGame();

        void HandleEvent();

        void Update();

        void Render(SDL_Surface* Display);

        void ResetBlock();

        void KeyPress(SDLKey sym, SDLMod mod, Uint16 unicode);

        void KeyRelease(SDLKey sym, SDLMod mod, Uint16 unicode);

        ReturnParameter* ExitParameters();

        ~MainGame();
};

#endif // MAINGAME_H_INCLUDED
