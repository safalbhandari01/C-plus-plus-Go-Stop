//***************************THIS CLASS IS NOT IN USE. PLEASE IGNORE THIS CLASS*********************************
#ifndef HUMANHELPER_H
#define HUMANHELPER_H


#include<iostream>
#include<string>
#include"Player.h"

using namespace std;

class HUMANHELPER: public PLAYER {
    private:

    public:
        //Overriding constructor that calls the parameterized constructor of the base 
        //class to set the name of the player in the base class
        HUMANHELPER(string name):PLAYER(name){};

        void play(vector< vector<Card*> > &cardsOnLayout,vector<Card*> &cardsOnStockPile);
        void playCardFromHand(vector<vector<Card*> > &cardsOnLayout, int &stackedPairIndex);
    

};

#endif 