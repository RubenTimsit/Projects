//
// Created by itay8 on 6/19/2022.
//

#include "Gang.h"


Gang::Gang(std::istream& source, int* lineCounter) : m_sizeOfGang(0)
{
    std::string line;
    while(getline(source,line))
    {
        lineCounter++;
        if(line == "EndGang")
        {
            break;
        }
        if(line == "Dragon")
        {
            m_gangList.push_back(std::unique_ptr<BattleCard>(new Dragon()));
        }
        else if(line == "Vampire")
        {
            m_gangList.push_back(std::unique_ptr<BattleCard>(new Vampire()));
        }
        else if(line == "Goblin")
        {
            m_gangList.push_back(std::unique_ptr<BattleCard>(new Goblin()));
        }
        else
        {
            throw DeckFileFormatError(*lineCounter);
        }
        m_sizeOfGang++;
    }
    if(line != "EndGang")
    {
        throw DeckFileFormatError(*lineCounter);
    }
}

void Gang::applyEncounter(Player &player) const
{
    int i;
    bool alreadyLost = false;
    for(i = 0; i < m_sizeOfGang; i++)
    {
        if(alreadyLost)
        {
            m_gangList[i]->loseEncounter(player);
        }
        else
        {
            if(player.getAttackStrength() >= m_gangList[i]->getForce())
            {
                player.addCoins(m_gangList[i]->getLoot());
            }
            else
            {
                m_gangList[i]->loseEncounter(player);
                alreadyLost = true;
            }
        }
    }
    if(!alreadyLost)
    {
        player.levelUp();
        printWinBattle(player.getName(), "Gang");
    }


}

void Gang::printInfo() const
{
        printCardDetails(std::cout,"Gang");
        printEndOfCardDetails(std::cout);
}

Gang::Gang(const Gang &gang) : m_sizeOfGang(gang.m_sizeOfGang)
{
    for(std::vector<std::unique_ptr<BattleCard>>::const_iterator it = gang.m_gangList.begin(); it!= gang.m_gangList.end();it++)
    {
        BattleCard* copy = (*it)->clone();

        m_gangList.push_back(static_cast<std::unique_ptr<BattleCard>>(copy));

    }
}