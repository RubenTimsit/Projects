#include "Pitfall.h"

void Pitfall::applyEncounter(Player &player) const
{
    try
    {
        dynamic_cast<Rogue&>(player);

    }
    catch(const std::bad_cast&)
    {
        player.damage(DAMAGE);
        printPitfallMessage(false);
        return;
    }
    printPitfallMessage(true);

}

void Pitfall::printInfo() const
{
    printCardDetails(std::cout,"Pitfall");
    printEndOfCardDetails(std::cout);
}
