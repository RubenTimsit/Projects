#include "HealthPoints.h"



HealthPoints::HealthPoints(int maxHP)
{
    if(maxHP<= 0){
        throw InvalidArgument{};
    }
    m_maxHP = maxHP;
    m_currentHP = maxHP;
}

HealthPoints &HealthPoints::operator+=(int number)
{


    m_currentHP+=number;
    if(m_currentHP>= m_maxHP)
    {
        m_currentHP = m_maxHP;
    }
    if(m_currentHP<=0)
    {
        m_currentHP =0;
    }
    return *this;
}

HealthPoints &HealthPoints::operator-=(int number)
{

    m_currentHP-=number;
    if(m_currentHP>= m_maxHP)
    {
        m_currentHP = m_maxHP;
    }
    if(m_currentHP<=0)
    {
        m_currentHP =0;
    }

    return *this;
}

HealthPoints operator+(int number, const HealthPoints& healthPoints)
{
    HealthPoints newHealthPoints(healthPoints);
    return newHealthPoints += number;
}

HealthPoints operator+(const HealthPoints& healthPoints,int number)
{
    HealthPoints newHealthPoints(healthPoints);
    return newHealthPoints += number;
}

HealthPoints operator-(int number, const HealthPoints& healthPoints)
{
    HealthPoints newHealthPoints(healthPoints);
    return newHealthPoints -= number;
}

HealthPoints operator-(const HealthPoints& healthPoints,int number)
{
    HealthPoints newHealthPoints(healthPoints);
    return newHealthPoints -= number;
}

bool HealthPoints::operator!=(const HealthPoints &healthPoints) const
{
    if(this->m_currentHP!= healthPoints.m_currentHP)
    {
        return true;
    }
    return false;
}

bool HealthPoints::operator<=(const HealthPoints &healthPoints) const
{
    if(this->m_currentHP <= healthPoints.m_currentHP)
    {
        return true;
    }
    return false;
}

bool HealthPoints::operator<(const HealthPoints &healthPoints) const
{
    if(this->m_currentHP < healthPoints.m_currentHP)
    {
        return true;
    }
    return false;
}

bool HealthPoints::operator>=(const HealthPoints &healthPoints) const
{
    if(this->m_currentHP >= healthPoints.m_currentHP)
    {
        return true;
    }
    return false;
}

bool HealthPoints::operator>(const HealthPoints &healthPoints) const
{
    if(this->m_currentHP > healthPoints.m_currentHP)
    {
        return true;
    }
    return false;
}

bool operator==(const HealthPoints& healthPoints1,const HealthPoints& healthPoints2)
{
    if(healthPoints1.m_currentHP == healthPoints2.m_currentHP)
    {
        return true;
    }
    return false;
}


ostream& operator<<(ostream& os, const HealthPoints& healthPoints)
{
    return os << healthPoints.m_currentHP << '(' << healthPoints.m_maxHP << ')';
}
