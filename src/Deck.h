/*
 ************************************************************
 * Name: Safal Bhandari                                     *
 * Project: C++ Go Stop                                     *
 * Class: OPL Spring 20                                     *
 * Date: 02/17/2020                                         *
 ************************************************************
*/
#ifndef DECK_H
#define DECK_H
#include <string>
#include <vector>
#include "Card.cpp"
#include "algorithm"

using namespace std;

class Deck
{

public:
    Deck();
    vector<Card *> getDeck();
    void shuffleDeck();

private:
    //holds pointer to the individual card objects
    vector<Card *> deckOfCards;
};
#endif
