#ifndef EX4_WIZARD_H
#define EX4_WIZARD_H

#include "ostream"
#include "Player.h"
#include "../utilities.h"

class Wizard: public Player
{
public:

    Wizard(std::string name);
    Wizard(const Wizard& wizard);
    void heal(int upgradeHeal)override;
    void printInfo()const override;
};
#endif //EX4_WIZARD_H
