#ifndef EX4_FIGHTER_H
#define EX4_FIGHTER_H


#include "Player.h"
#include "../utilities.h"

class Fighter: public Player
{
public:

    Fighter(std::string name);
    Fighter(const Fighter& fighter);
    int getAttackStrength()const override;
    void printInfo()const override;



};


#endif //EX4_FIGHTER_H
