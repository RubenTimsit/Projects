//
// Created by Ruben on 08/06/2022.
//

#ifndef EX4_PITFALL_H
#define EX4_PITFALL_H
#include "Card.h"
#include "../utilities.h"
#include "../Players/Rogue.h"

#define DAMAGE 10

class Pitfall: public Card
{
public:
    Pitfall()=default;
    ~Pitfall()override=default;
    void applyEncounter(Player &player) const override;
    void printInfo() const override;



};


#endif //EX4_PITFALL_H
