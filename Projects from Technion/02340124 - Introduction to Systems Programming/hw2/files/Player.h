#include <iosfwd>

#ifndef EX2_PLAYER_H
#define EX2_PLAYER_H


#include <string>
#define MAX 100

using std::string;

class Player
{
private:
    string m_name;
    int m_level;
    int m_maxHP;
    int m_force;
    int m_HP;
    int m_coins;


public:

    Player(string name, int maxHP=MAX, int force=5);
    Player(const Player& player);
    ~Player() = default;
    int getLevel()const;
    int levelUp();
    void buff(int upgradeBuff);
    void heal(int upgradeHeal);
    void damage(int downgradeHP);
    bool isKnockedOut()const;
    void addCoins(int upgradeCoins);
    bool pay(int toPay);
    int getAttackStrength()const;
    Player& operator=(const Player& player) = default;
    void printInfo()const;


};


#endif //EX2_PLAYER_H