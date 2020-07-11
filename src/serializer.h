/*
 ************************************************************
 * Name: Safal Bhandari                                     *
 * Project: C++ Go Stop                                     *
 * Class: OPL Spring 20                                     *
 * Date: 02/17/2020                                         *
 ************************************************************
*/
#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <string>
#include <vector>
#include "Card.h"

using namespace std;

class SERIALIZER
{

public:
    //constructor
    SERIALIZER();

    //getter for roundNumber
    int getRoundNumber()
    {
        return this->roundNumber;
    }

    //getter for nextPlayer
    string getNextPlayer()
    {
        return this->nextPlayer;
    }

    //getter for computerScore
    int getComputerScore()
    {
        return this->computerScore;
    }

    //getter for computerHandCards
    vector<Card *> getComputerHandCards()
    {
        return this->computerHandCards;
    }

    //getter for computerCapturePile
    vector<Card *> getComputerCapturePile()
    {
        return this->computerCapturePile;
    }

    //getter for humanScore
    int getHumanScore()
    {
        return this->humanScore;
    }

    //getter for humanHandCards
    vector<Card *> getHumanHandCards()
    {
        return this->humanHandCards;
    }

    //getter for humanCapturePile
    vector<Card *> getHumanCapturePile()
    {
        return this->humanCapturePile;
    }

    //getter for roundCardsOnLayout
    vector<Card *> getRoundCardsOnLayout()
    {
        return this->roundCardsOnLayout;
    }

    //getter for roundCardsOnStockPile
    vector<Card *> getRoundCardsOnStockPile()
    {
        return this->roundCardsOnStockPile;
    }

    //read from a file function
    void readFromFile();

    //save to a file function
    void saveToFile(string fileToSaveIn, string nextPlayer, int roundNumber, int computerScore, vector<Card *> computerHand, vector<Card *> computerCapturePile,
                    int humanScore, vector<Card *> humanHand, vector<Card *> humanCapturePile, vector<Card *> cardsOnLayout, vector<Card *> cardsOnStockPile);

private:
    //holds the round number
    int roundNumber;
    //holds the next player turn
    string nextPlayer;

    //holds computer score
    int computerScore;
    //holds pointer to cards for computer hand pile in a vector
    vector<Card *> computerHandCards;
    //holds pointer to cards for computer capture pile in a vector
    vector<Card *> computerCapturePile;

    //holds human score
    int humanScore;
    //holds pointer to cards for human hand pile in a vector
    vector<Card *> humanHandCards;
    //holds pointer to cards for human capture pile in a vector
    vector<Card *> humanCapturePile;

    //holds pointer to cards for layout pile in a vector
    vector<Card *> roundCardsOnLayout;
    //holds pointer to cards for cards on stock pile in a vector
    vector<Card *> roundCardsOnStockPile;
};
#endif