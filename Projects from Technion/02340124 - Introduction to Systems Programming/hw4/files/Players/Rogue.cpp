#include "Rogue.h"
using std::string;
using std::cout;
using std::ostream ;
Rogue::Rogue(string name): Player(name)
{

}

Rogue::Rogue(const Rogue &rogue): Player(rogue.m_name)
{

}

void Rogue::addCoins(int upgradeCoins)
{
    if(upgradeCoins>= 0)
    {
        m_coins+= 2*upgradeCoins;
        return;
    }
}

void Rogue::printInfo() const
{
    printPlayerDetails(std::cout, m_name,"Rogue", m_level, m_force, m_HP, m_coins);

}


