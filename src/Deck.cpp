/*
 ************************************************************
 * Name: Safal Bhandari                                     *
 * Project: C++ Go Stop                                     *
 * Class: OPL Spring 20                                     *
 * Date: 02/17/2020                                         *
 ************************************************************
*/
#include "Deck.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

/**********************************************************************
 * Function Name: Deck
 * Purpose: To construct the deck object of 52 cards
 * Parameters:
 *              None
 * Return Value:
 *              None
 * Local Variables: 
 *                  a string array faces, that contains face
 *                  values of a card from A-K
 *                  a string array suits, that contains four suits of 
 *                  a card
 * Algorithm:
 *                  a card object created for every combination of suit
 *                  and face and is pushed into the vector of cards
 * Assistance Received: None
 **********************************************************************/
Deck::Deck()
{

    //filling the deck object with 52 cards
    string faces[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "X", "J", "Q", "K"};
    string suits[4] = {"C", "D", "H", "S"};

    int sizeFaces = sizeof(faces) / sizeof(faces[0]);
    int sizeSuits = sizeof(suits) / sizeof(suits[0]);

    //Adding 52 cards to the vector
    for (int i = 0; i < sizeFaces; i++)
    {

        for (int j = 0; j < sizeSuits; j++)
        {
            //first values are pushed at the end of the stack
            deckOfCards.push_back(new Card(faces[i], suits[j]));
        }
    }

    // //Adding additional 52 cards to the vector
    // for(int i=0; i<sizeFaces; i++){

    //     for(int j=0; j<sizeSuits; j++){
    //         //first values are pushed at the end of the stack
    //         deckOfCards.push_back(new Card(faces[i],suits[j]));
    //     }
    // }
}

/**********************************************************************
* Function Name: getDeck
* Purpose: To return the deck of cards
* Parameters: None
* Return Value: vector of pointer to card object 
* Local Variables: None
* Assistance Received: None
**********************************************************************/
vector<Card *> Deck::getDeck()
{
    return deckOfCards;
}

/**********************************************************************
 * Function Name: shuffleDeck
 * Purpose: To shuffle the deck of cards
 * Parameters:
 *              None
 * Return Value:
 *              None
 * Local Variables: 
 *                  seedValue, contains seed value for random number generation
 *                  
 * Algorithm:
 *                  Create a seed value and generate a random number using
 *                  that value. Use the random number to shuffle the deck 
 *                  of pointer to cards     
 * Assistance Received: None
 **********************************************************************/
void Deck::shuffleDeck()
{

    //initializing the seed value
    auto seedValue = static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count());

    //creating and assigning a random number generator using the seed value
    auto randomNumberGenerator = default_random_engine(seedValue);

    //shuffling the deck of cards
    shuffle(deckOfCards.begin(), deckOfCards.end(), randomNumberGenerator);
}
