#include "Mtmchkin.h"




Mtmchkin::Mtmchkin(const char *playerName, const Card *cardsArray, int numOfCards):
        m_playerName(playerName),m_numOfCards(numOfCards), m_player1(playerName),m_currentCard(0)
{

    m_cardsArray = new Card[m_numOfCards];
    for(int i=0; i< m_numOfCards; i++){
        m_cardsArray[i] = cardsArray[i];
    }
    m_gameStatus = GameStatus::MidGame;
}

GameStatus Mtmchkin::getGameStatus() const
{
    return m_gameStatus;
}

Mtmchkin::Mtmchkin(const Mtmchkin& mtmchkin): m_numOfCards(mtmchkin.m_numOfCards),
                                              m_player1(mtmchkin.m_playerName), m_currentCard(mtmchkin.m_currentCard)
{

    m_cardsArray = new Card[m_numOfCards];
    for(int i=0; i< m_numOfCards; i++)
    {
        m_cardsArray[i] = mtmchkin.m_cardsArray[i];
    }
    m_gameStatus = mtmchkin.m_gameStatus;
}

Mtmchkin::~Mtmchkin()
{
    delete[] m_cardsArray;
}




bool Mtmchkin::isOver()
{
    if(m_gameStatus == GameStatus::Win || m_gameStatus == GameStatus::Loss )
    {
        return true;
    }
    return false;
}

GameStatus Mtmchkin::updateGameStatus(bool isKnockedOut, int actualLevel)
{
    if(isKnockedOut)
    {
        return GameStatus::Loss;
    }
    if(actualLevel<10)
    {
        return GameStatus::MidGame;
    }
    return GameStatus::Win;
}

void Mtmchkin::playNextCard()
{
    if (m_currentCard == m_numOfCards) {
        m_currentCard = 0;
    }
    m_cardsArray[m_currentCard].printInfo();
    m_cardsArray[m_currentCard].applyEncounter(m_player1);
    m_gameStatus = updateGameStatus(m_player1.isKnockedOut(), m_player1.getLevel());
    m_player1.printInfo();
    m_currentCard++;
}

