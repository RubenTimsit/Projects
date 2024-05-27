#include "Goblin.h"


Goblin::Goblin(int force, int loot, int damage) : BattleCard(force, loot, damage)
{

}

void Goblin::applyEncounter(Player &player) const
{
    int playerForce = player.getAttackStrength();
    if(playerForce >= m_force )
    {
        player.levelUp();
        player.addCoins(m_loot);
        printWinBattle(player.getName(),"Goblin");
    }
    else
    {
        player.damage(m_damage);
        printLossBattle(player.getName(),"Goblin");
    }
}
void Goblin::printInfo() const
{
    printCardDetails(std::cout,"Goblin");
    printMonsterDetails(std::cout, m_force, m_damage, m_loot, false);
    printEndOfCardDetails(std::cout);
}
 void Goblin::loseEncounter(Player &player) const
 {
    player.damage(m_damage);
     printLossBattle(player.getName(),"Goblin");
 }


BattleCard* Goblin::clone() const
{
    return new Goblin(*this);
}