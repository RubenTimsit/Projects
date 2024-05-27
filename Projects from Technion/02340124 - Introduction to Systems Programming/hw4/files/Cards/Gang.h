//
// Created by itay8 on 6/19/2022.
//

#ifndef MTMEX4_GANG_H
#define MTMEX4_GANG_H

#include "Card.h"
#include "Goblin.h"
#include "Dragon.h"
#include "Vampire.h"
#include "BattleCard.h"
#include <memory>
#include <vector>
#include <string>
#include <stdio.h>

class Gang : public Card
{
private:
    std::vector<std::unique_ptr<BattleCard>> m_gangList;
    int m_sizeOfGang = 0;

public:
    Gang(std::istream& file, int* lineCounter);
    Gang(const Gang& gang);
    ~Gang() override = default;
    void applyEncounter(Player &player) const override;
    void printInfo() const override;

};






#endif //MTMEX4_GANG_H
