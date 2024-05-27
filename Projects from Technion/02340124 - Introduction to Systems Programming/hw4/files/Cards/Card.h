#ifndef EX4_CARD_H
#define EX4_CARD_H
#include "../Players/Player.h"
#include "../utilities.h"


class Card
{
protected:

public:

    Card()=default;
    virtual ~Card()=default;
    Card(const Card& card)=default;
    virtual void applyEncounter(Player& player) const=0;
    virtual void printInfo() const=0;
    friend std::ostream& operator<<(std::ostream& os, const Card& card);



};


#endif //EX4_CARD_H
