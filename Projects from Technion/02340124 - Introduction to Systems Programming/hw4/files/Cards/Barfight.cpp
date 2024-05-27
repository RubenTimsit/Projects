
#include "Barfight.h"


void Barfight::applyEncounter(Player &player) const
{

    try
    {
        dynamic_cast<Fighter&>(player);
    }

    catch(const std::bad_cast&)
    {
        printBarfightMessage(false);
        player.damage(DAMAGE);
        return;
    }
    printBarfightMessage(true);

    /*int type = player.getType();
    if(type != 2)
    {
        printBarfightMessage(false);
        player.damage(DAMAGE);
    }
    else
    {
        printBarfightMessage(true);
    }*/

}

void Barfight::printInfo() const
{
    printCardDetails(std::cout,"Barfight");
    printEndOfCardDetails(std::cout);
}


