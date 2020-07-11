/*
 ************************************************************
 * Name: Safal Bhandari                                     *
 * Project: C++ Go Stop                                     *
 * Class: OPL Spring 20                                     *
 * Date: 02/27/2020                                         *
 ************************************************************
*/
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "Dealer.cpp"

using namespace std;

class PLAYER
{

public:
    //default constructor
    PLAYER();

    //overloading constructor
    PLAYER(string name);

    //destructor
    ~PLAYER();

    //pure virtual function for now
    virtual void play(vector<vector<Card *> > &cardsOnLayout, vector<Card *> &cardsOnStockPile) = 0;

    //getter/setter for name
    string getName();
    void setName(string name);

    //getter/setter for player score
    int getScore();
    void setScore(int score);

    //getter/setter for rounds played
    // int getRoundsPlayed();
    // void setRoundsPlayed(int totalRoundsPlayed);

    //getter/setter for cardsOnHand
    vector<Card *> getCardsOnHand();
    void setCardsOnHand(vector<Card *> cardsDealtForHand);

    //getter/setter for cardsOnCapturePile
    vector<Card *> getCardOnCapturePile();
    void setCardOnCapturePile(vector<Card *> cardsOnCapturePile);

    //add card/remove card from hands
    void addCardOnHand(Card *cardToAdd);
    void removeCardFromHand(Card *cardToRemove); //IMPLEMENTATION IS NOT DONE YET ON .cpp

    //returns size of the cards on Hand
    int sizeOfHandCards();

    //add card/remove card from capture pile
    void addCardOnCapturePile(Card cardToAdd);
    void removeCardFromCapturePile(Card cardToRemove);

    //getter/setter for ishelperbot
    void setHelperBot(bool trueOrFalse);

    //empties all the cards from hand
    void emptyCardsOnHand();
    //empties all the cards from capture pile
    void emptyCardsOnCapturePile();

    //print capture pile
    void printCapturePileCards(vector<Card *> capturePilePassed);

    //delete empty inner vectors from layout
    void deleteEmptyVectorsInsideLayout(vector<vector<Card *> > &cardsOnLayout);

    //calculates score from capture pile when called at the end of the round
    int calculateScore();

    //getter/setter for total score of the game
    int getTotalScore();
    void setTotalScore(int totalScorePassed);

    //provides option to choose index of matched card on layout
    int chooseIndexOfMatchedCardOnLayout(vector<int> matchVector);

    //removes cards from layout
    void removeCardsFromLayout(vector<vector<Card *> > &cardsOnLayout, string faceCard, int numCardsToRemove);

    //checks if there is a card on layout or not
    int checkCardOnLayout(vector<vector<Card *> > cardsOnLayout, string faceCardChosen);

    //returns vector of integer of all the cards matched from the chosen card with the layout
    vector<int> getIndexOfMatchedCardOnLayout(vector<vector<Card *> > cardsOnLayout, string faceCardChosen, int &numCardsMatched);

    //prints the layout in stack format
    void printLayoutStackFormat(vector<vector<Card *> > cardsOnLayout);

    //implementation of the strategy of when card is played from the stock pile
    void playCardFromStockPile(vector<vector<Card *> > &cardsOnLayout, vector<Card *> &cardsOnStockPile, int numCardsMatchedOnHand, int stackPairedIndex);

    //returns index of matched triple stack if there is a triple stack present else returns -1
    int findIndexMatchedTripleStack(vector<vector<Card *> > cardsOnLayout, string faceCardChosen);

protected:
    string playerName;
    int totalScore;
    int roundsPlayed;
    int currentRound;
    bool isHelperBot;
    vector<Card *> cardsOnHand;
    vector<Card *> cardsOnCapturePile;
};
#endif