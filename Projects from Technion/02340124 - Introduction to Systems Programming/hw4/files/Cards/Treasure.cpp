#include "Treasure.h"

void Treasure::applyEncounter(Player &player) const
{
    player.addCoins(TREASURE);
    printTreasureMessage();
}
void Treasure::printInfo() const
{
    printCardDetails(std::cout, "Treasure");
    printEndOfCardDetails(std::cout);
}