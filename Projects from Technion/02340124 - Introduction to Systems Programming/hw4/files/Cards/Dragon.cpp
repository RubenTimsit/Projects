#include "Dragon.h"


Dragon::Dragon(int force, int loot, int damage): BattleCard(force, loot, damage)
{

}

void Dragon::applyEncounter(Player &player) const
{
    int playerForce = player.getAttackStrength();
    if(playerForce >= m_force)
    {
        player.levelUp();
        player.addCoins(m_loot);
        printWinBattle(player.getName(),"Dragon");
    }
    else
    {
        player.damage(m_damage);
        printLossBattle(player.getName(), "Dragon");
    }
}

void Dragon::printInfo() const
{
    printCardDetails(std::cout,"Dragon");
    printMonsterDetails(std::cout, m_force, m_damage, m_loot, true);
    printEndOfCardDetails(std::cout);
}

void Dragon::loseEncounter(Player &player) const
{
    player.damage(m_damage);
    printLossBattle(player.getName(), "Dragon");
}

BattleCard* Dragon::clone() const
{
    return new Dragon(*this);
}