#ifndef EX4_BARFIGHT_H
#define EX4_BARFIGHT_H
#include "Card.h"
#include "../utilities.h"
#include "../Players/Fighter.h"
#define DAMAGE 10

class Barfight: public Card
{

public:
    Barfight()=default;
    ~Barfight()override=default;
    void applyEncounter(Player &player) const override;
    void printInfo() const override;


};

#endif //EX4_BARFIGHT_H
