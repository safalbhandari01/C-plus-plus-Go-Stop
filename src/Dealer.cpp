//***************************THIS CLASS IS NOT IN USE. PLEASE IGNORE THIS CLASS*********************************

#include "Dealer.h"

#include<string>
#include<vector>

using namespace std;

//default constructor
DEALER::DEALER(){

}

//overloading constructor
//passing the vector of deck as a pointer
DEALER::DEALER(vector<Card*>* deckOfCard){
    this->dealingDeck = deckOfCard;
}

//function that deals the card
//takes the number of cards to be dealt as a parameter
vector<Card*>* DEALER::dealCards(int numCardsToDeal){

    //store the cards to be dealt in a vector
    vector<Card*>* dealtCards = new vector<Card*>(); 

    //check if the number of cards to deal is less than the size of deck or not
    if(numCardsToDeal>this->dealingDeck->size()){
        cout<<"The size of the deck is smaller than the number of cards to deal\n";
        cout<<"Exiting\n";
        exit;
    }
        
    //remove the cards from the member variable vector
    for(int i=0;i<numCardsToDeal;i++){
        
        //check if you are getting a value or a pointer to the value in the  local vector 
        dealtCards->push_back(this->dealingDeck->front());

        //remove the first element from the vector 
        this->dealingDeck->erase(dealingDeck->begin());

    }

    //return the dealt card vector as a pointer
    return dealtCards;

}

vector<Card*>* DEALER::getDealingDeck(){
    return this->dealingDeck;
}

//function that checks if the deck to be dealt is empty or not
bool DEALER::isEmptyDeck(){

    //Checking the size of the deck to see if the pointer gives us  the size of the vector or not 
    cout<<"The size of the vector after dealing is"<<dealingDeck->size()<<endl;

    //CHECK IF THIS IS WORKING OR NOT 
    //is it true or not
    if(dealingDeck->empty())
        return true;
    else
        return false;
    
}



//Test main 
// int main(){


//     //FIRDS DECK OBJECT
//     cout<<"Checking the shuffled vector";
    

//     //Deck object and printing cards in the deck object
//     Deck deckObj;
//     deckObj.shuffleDeck();
//     vector<Card*> cardDeck = deckObj.getDeck();

//     cout<<"Printing DECK OBJECT  card"<<endl;
//     for(Card* i : cardDeck) 
//         cout << i->getFace() <<i->getSuit();
//     cout<<endl;
//     cout<<endl;
//     //Deal Object and printing cards in the deal object
//     DEALER dealObj(&cardDeck);

//     cout<<"Printing DEAL OBJECT card"<<endl;
//     for(Card* i : *dealObj.getDealingDeck()) 
//         cout << i->getFace() <<i->getSuit();
//     cout<<endl;
//     cout<<endl;


//     vector<Card*>* pointerToDealtCards = dealObj.dealCards(5);


//     cout<<"Printing 5 Dealt card"<<endl;
//     for(Card* i : *pointerToDealtCards) 
//         cout << i->getFace() <<i->getSuit();
//     cout<<endl;
//     cout<<endl;

//     //Printing the dealt Cards from member variable after deleting 5 cards for Testing
//     cout<<"Printing DEAL OBJECT card after 5 deletion"<<endl;
//     for(Card* i : *dealObj.getDealingDeck()) 
//         cout << i->getFace() <<i->getSuit();
//     cout<<endl;
//     cout<<endl;
    


//     return 0;

// }

