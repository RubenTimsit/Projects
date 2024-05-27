#include "Mtmchkin.h"

using std::cin;
using std::string;
using std::vector;
using std::deque;
using std::unique_ptr;

Mtmchkin::Mtmchkin(const std::string fileName): m_cardsDeck(), m_playersList(),m_roundCount(0)
{
    printStartGameMessage();
    initialize_deck(fileName);
    receiveSize();
    initializePlayer();
}

void Mtmchkin::playRound()
{
    int index = 0;
    m_roundCount++;
    printRoundStartMessage(m_roundCount);

    for(vector<std::unique_ptr<Player>>::iterator it=m_playersList.begin(); it!=m_playersList.end(); it++)
    {
        if((*it))
        {
            printTurnStartMessage((*it)->getName());
            m_cardsDeck[0]->applyEncounter(**it);
            if ((**it).isKnockedOut())
            {
                m_lossersList.push_front(std::move(*it));

            }
            else if ((**it).getLevel() == 10)
            {
                m_winnersList.push_back(std::move(*it));
            }
            else
            {
                index++;
            }
            m_cardsDeck.push_back(std::move(m_cardsDeck.front()));
            m_cardsDeck.pop_front();
            if (isGameOver())
            {
                printGameEndMessage();
                return;
            }
        }

    }



}

bool Mtmchkin::isGameOver() const
{
    unsigned int sizeLooser= m_lossersList.size();
    unsigned int sizeWinner = m_winnersList.size();
    unsigned int numberPlayer = m_playersList.size();

    if(sizeWinner+sizeLooser == numberPlayer)
    {
        return true;
    }
    return false;

    //return m_playersList.empty();
}

int Mtmchkin::getNumberOfRounds() const
{
    return m_roundCount;
}

void Mtmchkin::printLeaderBoard() const
{
    int ranking = 1;
    printLeaderBoardStartMessage();
    for(const unique_ptr<Player>& temp : m_winnersList)
    {
        printPlayerLeaderBoard(ranking, *temp);
        ranking++;
    }
    for(const unique_ptr<Player>& temp : m_playersList)
    {
        if (temp)
        {
            printPlayerLeaderBoard(ranking, *temp);
            ranking++;
        }
    }
    for(const unique_ptr<Player>& temp : m_lossersList)
    {
        printPlayerLeaderBoard(ranking, *temp);
        ranking++;
    }
    /*  for(vector<unique_ptr<Player>>::const_iterator it=m_winnersList.begin(); it!=m_winnersList.end(); it++)
    {
        std::cout << (**it);
    }
    for(vector<unique_ptr<Player>>::const_iterator it=m_playersList.begin(); it!=m_playersList.end(); it++)
    {
        std::cout << (**it);
    }
    for(deque<unique_ptr<Player>>::const_iterator it=m_lossersList.begin(); it!=m_lossersList.end(); it++)
    {
        std::cout << (**it);
    }*/

}
