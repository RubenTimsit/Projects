
#ifndef MTMEX4_VAMPIRE_H
#define MTMEX4_VAMPIRE_H
#include "BattleCard.h"

class Vampire:public BattleCard
{
public:
    Vampire(int force = 10, int loot =2, int damage =10);
    ~Vampire()override=default;
    BattleCard* clone() const override;
    void applyEncounter(Player& player)const override;
    void printInfo()const override;
    void loseEncounter(Player& player)const override;

};
#endif //MTMEX4_VAMPIRE_H
