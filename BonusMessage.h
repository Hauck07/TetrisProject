#ifndef BONUSMESSAGE_H_INCLUDED
#define BONUSMESSAGE_H_INCLUDED
#include <SDL/SDL.h>
#include <vector>
#include "SurfaceHandler.h"
#include "Define.h"

class BonusMessage{
    public:
        SDL_Surface* Surf_BonusMessage;

        int MessageLineCombo, MessageColorMatch;

        float PositionLineCombo, PositionColorMatch;

        BonusMessage();

        bool OnInit();

        void OnLoop();

        void SetColorMatchMessage(int MessageID);

        void SetLineComboMessage(int MessageID);

        void OnRender(SDL_Surface* Surf_Display);

        void OnCleanup();

};


#endif // BONUSMESSAGE_H_INCLUDED
