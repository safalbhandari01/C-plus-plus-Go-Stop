/*
 ************************************************************
 * Name: Safal Bhandari                                     *
 * Project: C++ Go Stop                                     *
 * Class: OPL Spring 20                                     *
 * Date: 02/27/2020                                         *
 ************************************************************
*/
#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

class COMPUTER : public PLAYER
{
private:
public:
    //Overriding constructor that calls the parameterized constructor of the base
    //class to set the name of the player in the base class
    COMPUTER(string name) : PLAYER(name){};

    //implementation of virtual function from player class
    void play(vector<vector<Card *> > &cardsOnLayout, vector<Card *> &cardsOnStockPile);

    //implementation of strategy to play card from hand for computer class
    int playCardFromHand(vector<vector<Card *> > &cardsOnLayout, int &stackedPairIndex);
};

#endif