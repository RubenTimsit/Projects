#ifndef EX4_PLAYER_H
#define EX4_PLAYER_H

#include <iostream>
#include <iosfwd>
#include <string>
#include <iostream>

#define MAX_HP 100

class Player
{
protected:
    std::string m_name;
    int m_level;
    int m_maxHP;
    int m_force;
    int m_HP;
    int m_coins;


public:

    Player(std::string name);
    Player(const Player& player);
    ~Player() = default;
    int getLevel()const;
    int getCoins() const;
    std::string getName()const;
    int levelUp();
    void buff(int upgradeBuff);
    virtual void heal(int upgradeHeal);
    void damage(int downgradeHP);
    bool isKnockedOut()const;
    virtual void addCoins(int upgradeCoins);
    bool pay(int toPay);
    virtual int getAttackStrength()const;
    Player& operator=(const Player& player) = default;
    virtual void printInfo()const=0;
    void downgradeForce();
    friend std::ostream& operator<<(std::ostream& os, const Player& player);


};

#endif //EX4_PLAYER_H
