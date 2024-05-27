#ifndef MTMEX4_DRAGON_H
#define MTMEX4_DRAGON_H
#include "BattleCard.h"

class Dragon : public BattleCard
{
public:
    Dragon(int force = 25, int loot =1000, int damage =MAX_HP);
    ~Dragon()override=default;
    BattleCard* clone() const override;
    void applyEncounter(Player& player)const override;
    void printInfo()const override;
    void loseEncounter(Player& player)const override;
};
#endif //MTMEX4_DRAGON_H
