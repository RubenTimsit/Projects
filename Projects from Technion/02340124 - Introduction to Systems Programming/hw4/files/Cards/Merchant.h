#ifndef EX4_MERCHANT_H
#define EX4_MERCHANT_H

#include "../utilities.h"
#include "Card.h"
#include <iostream>
#define DO_NOTHING 0
#define BUY_HP 1
#define BUY_FORCE 2
class Merchant: public Card
{
public:
    Merchant()=default;
    ~Merchant()override=default;
    void applyEncounter(Player& player)const override;
    void printInfo() const override;


};


#endif //EX4_MERCHANT_H
