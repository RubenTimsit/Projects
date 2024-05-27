#include "Fighter.h"

using std::ostream;
using std::cout;

Fighter::Fighter(std::string name): Player(name)
{

}

Fighter::Fighter(const Fighter &fighter): Player(fighter.m_name)
{

}

int Fighter::getAttackStrength() const
{
    int attackStrength = 2*m_force + m_level;
    return attackStrength;
}

void Fighter::printInfo() const
{
    printPlayerDetails(cout, m_name,"Fighter",m_level,m_force,m_HP,m_coins);
}

