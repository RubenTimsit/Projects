#ifndef EX4_ROGUE_H
#define EX4_ROGUE_H

#include "Player.h"
#include "../utilities.h"

class Rogue: public Player
{
public:

    Rogue(std::string name);
    Rogue(const Rogue& rogue);
    void addCoins(int upgradeCoins) override;
    void printInfo()const override;


};


#endif //EX4_ROGUE_H
