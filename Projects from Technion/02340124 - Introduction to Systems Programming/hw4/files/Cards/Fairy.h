
#ifndef MTMEX4_FAIRY_H
#define MTMEX4_FAIRY_H
#include "Card.h"
#include "../utilities.h"
#include "../Players/Wizard.h"
#define HEAL_AMOUNT 10



class Fairy:public Card
{
private:


public:

    Fairy()=default;
    ~Fairy()override=default;
    void applyEncounter(Player &player) const override;
    void printInfo() const override;


};
#endif //MTMEX4_FAIRY_H
