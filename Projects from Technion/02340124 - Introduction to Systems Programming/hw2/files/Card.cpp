#include "Card.h"

using std::ostream;


Card::Card(CardType type, const CardStats& stats) : m_effect(type), m_stats(stats)
{
}

void Card::applyEncounter(Player& player) const
{
    if(m_effect == CardType::Battle)
    {
        int force = player.getAttackStrength();
        if(force >= m_stats.force)
        {
            player.levelUp();
            player.addCoins(m_stats.loot);
        }
        else
        {
            player.damage(m_stats.hpLossOnDefeat);
        }
        int result = force - m_stats.force;
        if(result >= 0)
        {
            printBattleResult(true);
        }
        else
        {
            printBattleResult(false);
        }
    }
    else if(m_effect == CardType::Treasure)
    {
        player.addCoins(m_stats.loot);
    }
    else
    {
        int cost = m_stats.cost;
        if(cost <= 0)
        {
            cost = 0;
        }
        if(player.pay(cost))
        {
            if(m_effect == CardType::Buff)
            {
                player.buff(m_stats.buff);
            }
            else
            {
                player.heal(m_stats.heal);
            }
        }
    }
}

void Card::printInfo() const
{
    const CardStats card = m_stats;
    if(m_effect == CardType::Battle)
    {
        printBattleCardInfo(card);
    }
    else if(m_effect == CardType::Buff)
    {
        printBuffCardInfo(card);
    }
    else if (m_effect == CardType::Heal)
    {
        printHealCardInfo(card);
    }
    else
    {
        printTreasureCardInfo(card);
    }
}