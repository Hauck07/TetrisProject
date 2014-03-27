#include "BonusMessage.h"

BonusMessage::BonusMessage(){
    Surf_BonusMessage = NULL;
    MessageLineCombo = MessageColorMatch = MESSAGE_NONE;
    PositionColorMatch = PositionLineCombo = 0;
}

bool BonusMessage::OnInit(){
     if((Surf_BonusMessage = SurfaceHandler::OnLoad((char*)"./Graphics/bonusmessages.png")) == NULL)
        return false;
    return true;
}

void BonusMessage::OnLoop(){
    if(MessageColorMatch != MESSAGE_NONE || MessageLineCombo != MESSAGE_NONE){
        if(MessageColorMatch != MESSAGE_NONE)
            PositionColorMatch -= 1;
        if(MessageLineCombo != MESSAGE_NONE)
            PositionLineCombo -= 1;
        if(PositionColorMatch < -75){
            PositionColorMatch = 0;
            MessageColorMatch = MESSAGE_NONE;
        }
        if(PositionLineCombo < -75){
            PositionLineCombo = 0;
            MessageLineCombo = MESSAGE_NONE;
        }
    }
}

void BonusMessage::SetColorMatchMessage(int MessageID){
    switch(MessageID){
        case MESSAGE_NONE: MessageColorMatch = MESSAGE_NONE; break;
        case COLOR_MATCH_1: MessageColorMatch = COLOR_MATCH_1; break;
        case COLOR_MATCH_2: MessageColorMatch = COLOR_MATCH_2; break;
        case COLOR_MATCH_3: MessageColorMatch = COLOR_MATCH_3; break;
        case COLOR_MATCH_4: MessageColorMatch = COLOR_MATCH_4; break;
    }
}

void BonusMessage::SetLineComboMessage(int MessageID){
    switch(MessageID){
        case MESSAGE_NONE: MessageLineCombo = MESSAGE_NONE; break;
        case LINE_COMBO_2: MessageLineCombo = LINE_COMBO_2; break;
        case LINE_COMBO_3: MessageLineCombo = LINE_COMBO_3; break;
        case LINE_COMBO_4: MessageLineCombo = LINE_COMBO_4; break;
    }
}

void BonusMessage::OnRender(SDL_Surface* Surf_Display){
    if(MessageColorMatch != MESSAGE_NONE)
        SurfaceHandler::OnDraw(Surf_Display, Surf_BonusMessage, 160, 460+(int)PositionColorMatch, 0, MessageColorMatch*59, 224, 59);
    if(MessageLineCombo != MESSAGE_NONE)
        SurfaceHandler::OnDraw(Surf_Display, Surf_BonusMessage, 140, 480+(int)PositionLineCombo, 224, MessageLineCombo*59, 224, 59);
}

void BonusMessage::OnCleanup(){
    SDL_FreeSurface(Surf_BonusMessage);
    delete Surf_BonusMessage;
    MessageLineCombo = MESSAGE_NONE;
    PositionLineCombo = MESSAGE_NONE;
}
