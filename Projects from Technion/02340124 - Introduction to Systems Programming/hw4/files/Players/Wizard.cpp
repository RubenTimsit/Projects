#include "Wizard.h"
using std::string;
Wizard::Wizard(string name): Player(name)
{
}

Wizard::Wizard(const Wizard &wizard): Player(wizard.m_name)
{
}

void Wizard::heal(int upgradeHeal)
{
    if(upgradeHeal <= 0)
    {
        return;
    }
    int sum = m_HP + 2*upgradeHeal;
    if(sum > m_maxHP)
    {
        m_HP = m_maxHP;
        return;
    }
    m_HP += 2*upgradeHeal;
}

void Wizard::printInfo() const
{
    printPlayerDetails(std::cout, m_name,"Wizard", m_level, m_force, m_HP, m_coins);
}


