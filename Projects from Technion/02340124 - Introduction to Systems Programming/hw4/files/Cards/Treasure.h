#ifndef EX4_TREASURE_H
#define EX4_TREASURE_H
#include "Card.h"
#include "../utilities.h"
#define TREASURE 10

class Treasure: public Card
{
public:
    Treasure()=default;
    ~Treasure()override=default;
    void applyEncounter(Player& player)const override;
    void printInfo() const override;

};


#endif //EX4_TREASURE_H
