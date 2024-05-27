#include <iostream>
#include "../Mtmchkin.h"

int main()
{
    try
    {
        const int MAX_NUMBER_OF_ROUNDS = 100;
        Mtmchkin game("deck.txt");
        while(!game.isGameOver() && game.getNumberOfRounds() < MAX_NUMBER_OF_ROUNDS)
        {
            game.playRound();
        }
        game.printLeaderBoard();
    }
    catch (std::exception &e)
    {
        std::cout << e.what();
    }
    return 0;
}
