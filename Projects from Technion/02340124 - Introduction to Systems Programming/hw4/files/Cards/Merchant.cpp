#include "Merchant.h"


void Merchant::applyEncounter(Player &player) const
{
    int cost;
    std::string name  = player.getName();
    printMerchantInitialMessageForInteractiveEncounter(std::cout, name, player.getCoins());
    int answer;
    /*std::cin >> answer;



    while(answer != DO_NOTHING && answer != BUY_FORCE && answer != BUY_HP )
    {
        printInvalidInput();
        std::cin >> answer;
    }
    if(answer == DO_NOTHING)
    {
        printMerchantSummary(std::cout, name, answer, 0 );
        return;
    }
    else if(answer == BUY_HP)
    {
        cost = 5;
    }
    else
    {
        cost = 10;
    }

     */
    std::string tempInput;
    bool validInput = false;
    while(!validInput)
    {
        validInput = true;
        try {
            if (!std::getline(std::cin, tempInput) || tempInput.length() != 1 || (stoi(tempInput) != DO_NOTHING && stoi(tempInput) != BUY_FORCE
            && stoi(tempInput) != BUY_HP))
            {
                throw std::invalid_argument("bad getline");
            }
        }
        catch (std::invalid_argument &) {
            validInput = false;
            printInvalidInput();
        }
    }
    answer = stoi(tempInput);
    if(answer == DO_NOTHING)
    {
        printMerchantSummary(std::cout, name, answer, 0 );
        return;
    }
    else if(answer == BUY_HP)
    {
        cost = 5;
    }
    else
    {
        cost = 10;
    }

    if(player.getCoins() < cost)
    {
        printMerchantInsufficientCoins(std::cout);
        printMerchantSummary(std::cout, name, answer, 0 );
        return;
    }
    player.pay(cost);
    if(answer == BUY_HP)
    {
        player.heal(1);
    }
    else
    {
        player.buff(1);
    }

    printMerchantSummary(std::cout, name, answer, cost );
}

void Merchant::printInfo() const
{
    printCardDetails(std::cout, "Merchant");
    printEndOfCardDetails(std::cout);
}


















