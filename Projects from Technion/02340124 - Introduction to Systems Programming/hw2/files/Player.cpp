#include "Player.h"
#include "utilities.h"


using std::string;


Player::Player(string name, int maxHP,  int force):
        m_name(name),m_level(1),m_maxHP(maxHP), m_force(force), m_HP(maxHP),  m_coins(0)
{
    if(maxHP <= 0)
    {
        m_maxHP = 100;
    }
    else{
        m_maxHP = maxHP;
    }

    if(m_force<=0)
    {
        m_force=5;
    }
    else
    {
        m_force= force;
    }

}



Player::Player(const Player& player): m_name(player.m_name), m_level(player.m_level),m_maxHP(player.m_maxHP), m_force(player.m_force),
                                      m_HP(player.m_HP),  m_coins(player.m_coins)
{
}

int Player::getLevel() const
{
    return m_level;
}


int Player::getAttackStrength() const
{
    int attackStrength = m_force + m_level;
    return attackStrength;
}

int Player::levelUp()
{
    if(m_level<10)
    {
        return m_level++;
    }
    return m_level;
}

void Player::buff(int upgradeBuff)
{   if(upgradeBuff>=0)
    {
        m_force += upgradeBuff;
        return;
    }

}

void Player::heal(int upgradeHeal)
{
    if(upgradeHeal <= 0)
    {
        return;
    }
    int sum = m_HP + upgradeHeal;
    if(sum > m_maxHP)
    {
        m_HP = m_maxHP;
        return;
    }
    m_HP += upgradeHeal;

}

void Player::damage(int downgradeHP)
{
    if(downgradeHP<=0)
    {
        return;
    }
    int sum = m_HP - downgradeHP;
    if(sum<0)
    {
        m_HP =0;
        return;
    }

    m_HP = m_HP - downgradeHP;

}

bool Player::isKnockedOut() const
{
    if(m_HP == 0)
    {
        return true;
    }
    return false;
}

void Player::addCoins(int upgradeCoins)
{
    if(upgradeCoins>= 0)
    {
        m_coins+= upgradeCoins;
        return;
    }
}



bool Player::pay(int toPay)
{
    if(m_coins < toPay)
    {
        return false;
    }
    if(toPay <=0)
    {
        return true;
    }
    m_coins -= toPay;
    return true;
}

void Player::printInfo() const
{
    printPlayerInfo(m_name.c_str(),m_level,m_force,m_HP,m_coins);

}


