#include "BattleCard.h"

BattleCard::BattleCard(int force, int loot, int damage) : m_force(force), m_loot(loot), m_damage(damage)
{

}


/*void BattleCard::printInfo() const
{
    printMonsterDetails(std::cout,m_force,m_damage,m_loot);
}*/


int BattleCard::getForce() const
{
    return m_force;
}

int BattleCard::getLoot() const
{
    return m_loot;
}
