//
// Created by Daniel_Meents on 07/04/2022.
//

#ifndef EX2_GAME_H
#define EX2_GAME_H
#include "Card.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using std::vector;

/*
 * GameStatus:
 * MidGame - The game is still active and the player continues to encounter cards.
 * Win - The player reached level 10.
 * Loss - The player's HP is 0.
*/
enum class GameStatus{Win, Loss, MidGame};

class Mtmchkin {
public:

    /*
     * C'tor of the game:
     *
     * @param playerName - The name of the player.
     * @param cardsArray - A ptr to the cards deck.
     * @param numOfCards - Num of cards in the deck.
     * @result
     *      An instance of Mtmchkin
    */
    Mtmchkin(const char* playerName, const Card* cardsArray, int numOfCards);

    ~Mtmchkin();

    Mtmchkin(const Mtmchkin& mtmchkin);

    /*
     *
     * update the status of the game after playing a card
     *
     */
    GameStatus updateGameStatus(bool isKnockedOut, int actualLevel);
    /*
     *
     *
     * Play the next Card - according to the instruction in the exercise document
     *
     * @return
     *      void
    */
    void playNextCard();


    /*
     *  Check if the game ended:
     *
     *  @return
     *          True if the game ended
     *          False otherwise
     */
    bool isOver();


    /*
     *  Get the status of the game:
     *
     *  @return
     *          GameStatus - the current status of the running game
     */
    GameStatus getGameStatus() const;

private:
    //TODO: complete the Mtmchkin class.
    string m_playerName;
    int m_numOfCards;
    Card* m_cardsArray;
    GameStatus m_gameStatus;
    Player m_player1;
    int m_currentCard;
};


#endif //EX2_GAME_H
