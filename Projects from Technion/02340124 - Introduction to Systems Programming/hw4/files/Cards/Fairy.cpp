#include "Fairy.h"

void Fairy::applyEncounter(Player &player) const
{
    try
    {
        dynamic_cast<Wizard&>(player);
    }
    catch(const std::bad_cast&)
    {
        printFairyMessage(false);
        return;
    }
    player.heal(HEAL_AMOUNT);
    printFairyMessage(true);
}

void Fairy::printInfo() const
{
    printCardDetails(std::cout,"Fairy");
    printEndOfCardDetails(std::cout);
}
