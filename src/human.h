/*
 ************************************************************
 * Name: Safal Bhandari                                     *
 * Project: C++ Go Stop                                     *
 * Class: OPL Spring 20                                     *
 * Date: 02/27/2020                                         *
 ************************************************************
*/
#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

class HUMAN : public PLAYER
{
private:
public:
    //Overriding constructor that calls the parameterized constructor of the base
    //class to set the name of the player in the base class
    HUMAN(string name) : PLAYER(name){};

    //implementation of virtual function play from player class
    void play(vector<vector<Card *> > &cardsOnLayout, vector<Card *> &cardsOnStockPile);

    //returns index of the chosen card from hand 
    int chooseCardFromHand();

    //implementation of strategy to play card from hand for human class
    int playCardFromHand(vector<vector<Card *> > &cardsOnLayout, int &stackedPairIndex);
};

#endif