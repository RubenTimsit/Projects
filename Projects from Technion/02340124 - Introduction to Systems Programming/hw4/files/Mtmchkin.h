#ifndef MTMCHKIN_H_
#define MTMCHKIN_H_
#include <string>
#include <vector>
#include <deque>
#include <memory>
#include <algorithm>
#include "Cards/Card.h"
#include <fstream>
#include <iostream>
#include <map>
#include "Exception.h"
#include "Cards/Goblin.h"
#include "Cards/Vampire.h"
#include "Cards/Dragon.h"
#include "Cards/Merchant.h"
#include "Cards/Treasure.h"
#include "Cards/Pitfall.h"
#include "Cards/Barfight.h"
#include "Cards/Fairy.h"
#include "Cards/Gang.h"
#include "Players/Rogue.h"
#include "Players/Wizard.h"
#include "Players/Fighter.h"

#define MIN_NUMBER 2
#define MAX_NUMBER 6

class Mtmchkin
{
private:
    std::deque<std::unique_ptr<Card>> m_cardsDeck; // holds all the cards
    std::vector<std::unique_ptr<Player>> m_playersList; // holds players that are still playing
    std::vector<std::unique_ptr<Player>> m_winnersList; // holds players who won according to the sequence
    std::deque<std::unique_ptr<Player>> m_lossersList; //holds players who lost according to the sequence
    int m_roundCount;
    int m_teamSize;
    int m_deckSize = 0;

    //this private method gets the fileName and creates and returns the deck.txt for the game
    void initialize_deck(const std::string& fileName)
    {
        std::ifstream source(fileName);
        if (!source)
        {
            throw DeckFileNotFound();
        }
        std::string line;
        int lineCounters = 0;
        while (getline(source,line))
        {
            lineCounters++;
            if(line == "Goblin")
            {
                m_cardsDeck.push_back(std::unique_ptr<Card>(new Goblin()));
            }
            else if(line == "Vampire")
            {
                m_cardsDeck.push_back(std::unique_ptr<Card>(new Vampire()));
            }
            else if(line == "Dragon")
            {
                m_cardsDeck.push_back(std::unique_ptr<Card>(new Dragon()));
            }
            else if(line == "Merchant")
            {
                m_cardsDeck.push_back(std::unique_ptr<Card>(new Merchant()));
            }
            else if(line == "Treasure")
            {
                m_cardsDeck.push_back(std::unique_ptr<Card>(new Treasure()));
            }
            else if(line == "Barfight")
            {
                m_cardsDeck.push_back(std::unique_ptr<Card>(new Barfight()));
            }
            else if(line == "Pitfall")
            {
                m_cardsDeck.push_back(std::unique_ptr<Card>(new Pitfall()));
            }
            else if(line == "Fairy")
            {
                m_cardsDeck.push_back(std::unique_ptr<Card>(new Fairy()));
            }
            else if(line == "Gang")
            {
                m_cardsDeck.push_back(std::unique_ptr<Card>(new Gang(source, &lineCounters)));
            }
            else
            {
                throw DeckFileFormatError(lineCounters);
            }
            m_deckSize++;
        }
        if(m_deckSize < 5)
        {
            throw DeckFileInvalidSize();
        }
    }

    // here we receive the team's size from the user until it's legal
    void receiveSize()
    {
        printEnterTeamSizeMessage();
        std::string tempInput;
        //std::getline(std::cin, tempInput);
        /*int size = std::stoi(tempInput);
        while (size < MIN_NUMBER || size > MAX_NUMBER)
        {
            printInvalidTeamSize();
            printEnterTeamSizeMessage();
            //std::getline(std::cin, tempInput);
            //size = std::stoi(tempInput);
        }

        m_teamSize = size;*/

        //while(!(std::cin >> m_teamSize || m_teamSize< MIN_NUMBER || m_teamSize >MAX_NUMBER)
        bool validInput = false;
        while(!validInput)
        {
            validInput = true;
            try {
                if (!std::getline(std::cin, tempInput) || tempInput.length() != 1 ||
                    std::stoi(tempInput) < MIN_NUMBER ||
                    std::stoi(tempInput) > MAX_NUMBER)
                {
                    throw std::invalid_argument("bad getline");
                }

            }
            catch (std::invalid_argument &) {
                validInput = false;
                printInvalidTeamSize();
                printEnterTeamSizeMessage();
                //std::getline(std::cin, tempInput);
            }

        }

        m_teamSize = std::stoi(tempInput);



}

//creates the list of players in the beginning of the game
void initializePlayer()
{
std::string name, job;
for(int i = 0; i < m_teamSize; i++)
{
    printInsertPlayerMessage();
    getline(std::cin,name,' ');
    getline(std::cin, job);
    while(!nameIsLegal(name) || !jobIsLegal(job))
    {
        if(!nameIsLegal(name))
        {
            printInvalidName();
            getline(std::cin, name, ' ');
            getline(std::cin, job);

        }
        else if(!jobIsLegal(job))
        {
            printInvalidClass();
            getline(std::cin, name, ' ');
            getline(std::cin, job);
        }
    }
    /*while(!jobIsLegal(job))
    {
        printInvalidClass();
        getline(std::cin, job);
    }*/
            if (job == "Rogue")
            {
                m_playersList.push_back(std::unique_ptr<Player>(new Rogue(name)));
            }
            else if (job == "Wizard") {
                m_playersList.push_back(std::unique_ptr<Player>(new Wizard(name)));
            } else {
                m_playersList.push_back(std::unique_ptr<Player>(new Fighter(name)));
            }
        }
    }


    //checks if the inserted name is legal, and handles the case when not legal
    static bool nameIsLegal(std::string string1)
    {
        int size = string1.length();
        if (size == 0 || size > 15)
        {
            return false;
        }
        for(int i=0; i<size; i++)
        {
            if(!isalpha(string1[i]))
            {
                return false;
            }
        }
        return true;
    }

    //checks and handles cases of wrong job
    static bool jobIsLegal(const std::string& string1)
    {
        if(string1 != "Rogue" && string1 != "Wizard" && string1 != "Fighter")
        {
            return false;
        }
        return true;
    }


public:

    /*
    * C'tor of Mtmchkin class
    *
    * @param filename - a file which contains the cards of the deck.txt.
    * @return
    *      A new instance of Mtmchkin.
    */
    Mtmchkin(const std::string fileName);

    /*
    * Play the next Round of the game - according to the instruction in the exercise document.
    *
    * @return
    *      void
    */
    void playRound();

    /*
    * Prints the leaderBoard of the game at a given stage of the game - according to the instruction in
     * the exercise document.
    *
    * @return
    *      void
    */
    void printLeaderBoard() const;

    /*
    *  Checks if the game ended:
    *
    *  @return
    *          True if the game ended
    *          False otherwise
    */
    bool isGameOver() const;

    /*
    *  Returns the number of rounds played.
    *
    *  @return
    *          int - number of rounds played
    */
    int getNumberOfRounds() const;
};



#endif /* MTMCHKIN_H_ */
