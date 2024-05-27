#ifndef EX4_GOBLIN_H
#define EX4_GOBLIN_H
#include "BattleCard.h"


class Goblin:public BattleCard
{
public:

    Goblin(int force = 6, int loot =2, int damage =10);
    ~Goblin()override=default;
    BattleCard* clone() const override;
    void applyEncounter(Player& player)const override;
    void printInfo()const override;
    void loseEncounter(Player& player)const override;

};


#endif //EX4_GOBLIN_H
