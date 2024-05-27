#include "Vampire.h"

Vampire::Vampire(int force, int loot, int damage)  : BattleCard(force, loot, damage)
{

}


void Vampire::applyEncounter(Player &player) const
{
    int playerForce = player.getAttackStrength();
    if(playerForce >= m_force)
    {
        player.levelUp();
        player.addCoins(m_loot);
        printWinBattle(player.getName(),"Vampire");
    }
    else
    {
        player.damage(m_damage);
        player.downgradeForce();
        printLossBattle(player.getName(), "Vampire");
    }
}

void Vampire::printInfo() const
{
    printCardDetails(std::cout,"Vampire");
    printMonsterDetails(std::cout, m_force, m_damage, m_loot, false);
    printEndOfCardDetails(std::cout);
}

void Vampire::loseEncounter(Player &player) const
{
    player.damage(m_damage);
    player.downgradeForce();
    printLossBattle(player.getName(), "Vampire");
}

BattleCard* Vampire::clone() const
{
    return new Vampire(*this);
}