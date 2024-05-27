#ifndef CARD_H_BATTLECARD_H
#define CARD_H_BATTLECARD_H
#include "Card.h"



class BattleCard: public Card
{
protected:
    int m_force;
    int m_loot;
    int m_damage;

public:

    BattleCard(int force, int loot, int damage);
    BattleCard(const BattleCard& battleCard)=default;
    virtual ~BattleCard()=default;
    virtual BattleCard* clone() const = 0;
    virtual void applyEncounter(Player& player) const=0;
    virtual void loseEncounter(Player& player) const=0;
    void printInfo() const override=0;
    int getForce() const;
    int getLoot() const;

};


#endif //CARD_H_BATTLECARD_H
