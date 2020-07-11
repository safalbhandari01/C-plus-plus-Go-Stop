/*
 ************************************************************
 * Name: Safal Bhandari                                     *
 * Project: C++ Go Stop                                     *
 * Class: OPL Spring 20                                     *
 * Date: 02/17/2020                                         *
 ************************************************************
*/
#ifndef ROUND_H
#define ROUND_H

#include <iostream>
#include <vector>
//#include "Game.h"
#include "Player.cpp"
#include "human.cpp"
#include "humanHelper.cpp"
#include "computer.cpp"
#include "serializer.cpp"

using namespace std;

class ROUND
{

public:
    //Default constructor for Round Class
    ROUND(PLAYER *humanPlayer, PLAYER *computerPlayer, int currentRound, int nextPlayerToPlay);

    //Overloading Constructor for Round Class to load the state of previously played incomplete round from a file
    ROUND(PLAYER *humanPlayer, PLAYER *computerPlayer, int currentRound, int nextPlayer, vector<vector<Card *> > cardsOnLayoutPassed, vector<Card *> cardsOnStockPilePassed, string nextPlayerTurn);

    //set up the round
    void roundSetup();

    //start the round
    void startRound();

    //save game and exit
    void saveGameAndExit();

    //deals card to player, computer, layout, and stock pile
    void dealAllCards();

    //add a card
    void addACard(Card cardToAdd);

    //prints all the vectors and necessary information on the console for display
    void printVectors();

    //determine first player turn-- returns HUMAN_INDEX OR COMPUTER_INDEX
    int determineFirstPlayer();

    //displays scores and other info when round is complete
    void roundCompleteInfo();

    //first player determines and checks for modulo suit
    void setUpFirstPlayer();

    //displays the menu and return the option chosen
    int displayMenu(int humanOrComputer);

    //removes all the cards from deck vector
    void clearCardsFromDeck();

    //removes all the cards from the layout vector
    void clearCardsFromLayout();

    //removes all the cards from the stock pile vector
    void clearCardsFromStockPile();

    //getter for cards on layout by value
    vector<vector<Card *> > getCardsOnLayoutByValue();

    //getter for cards on stockpile by value
    vector<Card *> getCardsOnStockPileByValue();

    //getter/setter for round number
    void setRoundNumber(int roundNumber);
    int getRoundNumber();

    //getter setter for round winner
    int getRoundWinnerIndex();
    void setRoundWinnerIndex(int index);

    //getter/setter for is round complete
    bool getIsRoundComplete();
    void setIsRoundComplete(bool trueOrFalse);

    //getter(by reference)/setter for cards on layout
    vector<vector<Card *> > &getCardsOnLayout();
    void setCardsOnLayout(vector<vector<Card *> > cardsOnLayoutPassed);

    //getter(by reference)/setter for cards on stockPile
    vector<Card *> &getCardsOnStockPile();
    void setCardsOnStockPile(vector<Card *> cardsOnStockPilePassed);

private:
    //holds the constant value for Human helper bot, human index, and computer index
    const int HUMAN_HELPER_BOT = 0;
    const int HUMAN_INDEX = 1;
    const int COMPUTER_INDEX = 2;

    //holds the roundNumber
    int roundNumber;
    //holds the index of the winner of the round
    int roundWinnerIndex = -1;
    //holds bool value of whether round is complete or not
    bool isRoundComplete = false;
    //index of player whose turn is to play
    int nextPlayer;
    //holds true if it is a new game, false if it is another round
    bool newGame;
    //holds string value of who is next to play the turn
    string nextPlayerTurn;
    //deck of card to distribute in the round
    vector<Card *> cardDeck;
    //Vector of vector of pointer to cards on layout
    vector<vector<Card *> > cardOnLayout;
    //vector of cards on stock pile to pick from
    vector<Card *> cardOnStockPile;
    //holds the computer player and human player
    PLAYER *players[3];
};

#endif