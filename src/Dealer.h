//***************************THIS CLASS IS NOT IN USE. PLEASE IGNORE THIS CLASS*********************************
#ifndef DEALER_H
#define DEALER_H

#include<string>
#include<vector>
#include"Deck.cpp"
//#include"Card.cpp"

using namespace std;

class DEALER{
    
    private:
            vector<Card*>* dealingDeck;
            
    public:
            DEALER();
            DEALER(vector<Card*>* deckOfCard);
            vector<Card*>* dealCards(int numCardsToDeal);
            bool isEmptyDeck();
            //return deck of cards assigned to dealer object
            vector<Card*>* getDealingDeck();


};

#endif