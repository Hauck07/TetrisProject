#ifndef PLAYERDATA_H_INCLUDED
#define PLAYERDATA_H_INCLUDED
#include "ReturnParameter.h"
#include <string>

class PlayerData: public ReturnParameter{
    public:
        std::string PlayerName;
        int Score;

        PlayerData(std::string N, int S){
            PlayerName = N;
            Score = S;
        }
};


#endif // PLAYERDATA_H_INCLUDED
