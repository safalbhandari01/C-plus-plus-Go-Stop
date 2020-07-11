/*
 ************************************************************
 * Name: Safal Bhandari                                     *
 * Project: C++ Go Stop                                     *
 * Class: OPL Spring 20                                     *
 * Date: 02/27/2020                                         *
 ************************************************************
*/
#include "human.h"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


/**********************************************************************
* Function Name: play 
* Purpose: To implement strategy of play for human player
* Parameters:
*                   cardsOnLayout, vector of vector of pointer to cards which is in the layout
*                   cardsOnStockPile, vector of pointer to cards which is in the stockpile
* Return Value: None 
* Local Variables: 
*                   stackedPairIndex, holds int value of index of the stacked pair 
*                   else if no stack pair holds -1
* Algorithm:
*                   calls playCardFromHand function which is an implementation of players move
*                   from their hand. This function implements the strategy for playing card from
*                   hand and returns number of card matched on the layout with the card chosen by
*                   the player from hand. After playCardFromHand playCardFromStockPile function is 
*                   called that implements the strategy for the game when card is drawn from stock
*                   pile in the parent class Player
* Assistance Received: None
**********************************************************************/
void HUMAN::play(vector<vector<Card *> > &cardsOnLayout, vector<Card *> &cardsOnStockPile)
{
    //initialized with negative value because index cannot be negative so it has to be changed... if it is negative when
    //checking on playCardFromStockPile it means no card was stacked as a pair in this turn
    int stackedPairIndex = -1;

    int numMatchedCards = playCardFromHand(cardsOnLayout, stackedPairIndex);

    //Print for checking
    cout << "\tStacked Pair Index: " << stackedPairIndex << endl;

    //Play cards from the stock pile
    //Pass numMatchedCards on the layout with the card played by human from the hand as an argument
    playCardFromStockPile(cardsOnLayout, cardsOnStockPile, numMatchedCards, stackedPairIndex);
}

/**********************************************************************
* Function Name: chooseCardFromHand 
* Purpose: To take input from the human on the card chosen 
* Parameters:
*                   None
* Return Value:     
*                   playedCardIndex, index of card chosen by the player
* Local Variables: 
*                   playedCardIndex, holds index of card chosen by the player
* Algorithm:
*                   None
* Assistance Received: None
**********************************************************************/
int HUMAN::chooseCardFromHand()
{
    int playedCardIndex;

    cout << "\tHuman Turn To Play. Please choose index of the card to play a card From Hand: ";
    cin >> playedCardIndex;

    while (!cin || playedCardIndex < 0 || playedCardIndex >= cardsOnHand.size())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\tPlease enter valid integer option: ";
        cin >> playedCardIndex;
    }

    return playedCardIndex;
}


/**********************************************************************
* Function Name: playCardFromHand 
* Purpose: To implement strategy to play for hand for human player
* Parameters:
*                   cardsOnLayout, vector of vector of pointer to cards which is in the layout
*                   stackedPairIndex, passed as reference to hold the stacked pair index
* Return Value:  
*                   numCardsMatchedOnLayout, int value of number of card matched on layout with the 
*                   card chosen by human player from the hand
* Local Variables: 
*                   cardChosen, pointer to card holds the card chosen by human from hand
*                   faceCardChosen, string value of the face value of the card chosen
*                   numCardsMatchedOnLayout, int value of the num cards matched on layout
*                   playedCard, pointer to card of the card played
*                   tripleStackIndexReturn, int value of the stack of the triple stack if there is one
*                   faceValue, string value of the face value of the card
*                   numCardsMatched, int value of the number of cards matched
*                   matches, vector of int that contains index of the card with same face value as picked
*                   by the human player from the hand
*                   optionChosen, int value of the option chosen by the human from the matches

* Algorithm:
*                   1.checks num of cards matched on layout by calling checkCardOnLayout
*                   2.then check if there is a triple stack present and if the card chosen 
*                    matches with the triple stack if yes, capture the cards and return
*                   3. if no for number, and if number of cards matched is:  
*                   0: no card in the layout, the card is added to the layout.
*                   1: one card in the layout, the player creates a stack pair of the two cards and leaves it in the layout.
*                   2: two cards in the layout, the player picks one of the two cards and creates a stack pair with it and
*                   the card played from the hand, leaving the stack pair in the layout.
*                   3: three cards in the layout, the player captures all four cards, i.e., adds them to their capture pile.2, 
*
* Assistance Received: None
**********************************************************************/
int HUMAN::playCardFromHand(vector<vector<Card *> > &cardsOnLayout, int &stackedPairIndex)
{
    cout << "\n\n\tHAND PILE MOVE\n";
    //Ask human to play a card
    int playedCardIndex = chooseCardFromHand();

    //get string value of facecard chosen and pass it to checkCardOnLayout
    Card *cardChosen = cardsOnHand.at(playedCardIndex);
    string faceCardChosen = cardChosen->getFace();

    //get number of cards matched
    int numCardsMatchedOnLayout;
    numCardsMatchedOnLayout = checkCardOnLayout(cardsOnLayout, faceCardChosen);

    // if cards matched on layout is greater than 3 then it is given the value to 3 because we handle only 3 cards matching at the most in this game.
    if (numCardsMatchedOnLayout > 3)
    {
        numCardsMatchedOnLayout = 3;
    }

    //take the card out from the vector and make a move
    Card *playedCard = new Card(*cardsOnHand.at(playedCardIndex));
    cout << "\tCard Chosen From Hand: " << playedCard->getFace() << playedCard->getSuit() << "\n";

    //check for triple stack and assigns triple stack index to tripleStackIndexReturn
    int tripleStackIndexReturn = findIndexMatchedTripleStack(cardsOnLayout, playedCard->getFace());
    if (tripleStackIndexReturn != -1)
    {
        //capture triple stack and played card if triple stack is present and there is a card on hand with
        //same face value of triple stack present
        //Pushing the stacked pair to the capture pile
        for (int i = 0; i < 3; i++)
        {
            Card *capturedCard = new Card(*cardsOnLayout.at(tripleStackIndexReturn).at(i));
            this->cardsOnCapturePile.push_back(capturedCard);
        }

        //remove the triple stack from layout
        cardsOnLayout.erase(cardsOnLayout.begin() + tripleStackIndexReturn);

        //push the face card to the capture pile
        this->cardsOnCapturePile.push_back(playedCard);

        //print triple stack captured
        cout << "Just captured triple stack \n";

        //number of cards matched on layout set to 3 because triple stack is captured
        numCardsMatchedOnLayout = 3;

        //remove the card from the hand
        cardsOnHand.erase(cardsOnHand.begin() + playedCardIndex);

        return numCardsMatchedOnLayout;
    }

    //inner vector to add the card to incase if needed to add to the layout
    //could not  initialize the inner vector inside each cases because of restriction placed by C++
    //so declared here and pushbacked in the cases
    string faceValue;
    int numErasedCards;

    vector<Card *> innerVector;
    //passed by reference to get the num of cards matched from get Index of Matched Card On Layout function
    int numCardsMatched = 0;
    vector<int> matches;
    vector<Card *> capturePileVector;
    int optionChosen;


    //FOR CARD PLAYED FROM THE HAND STARTS ************************
    //make a move depending on the number of cards matched
    switch (numCardsMatchedOnLayout)
    {
    case 0: //if 0 cards matched add the card to the layout
        innerVector.push_back(playedCard);
        cardsOnLayout.push_back(innerVector);
        break;
    case 1: //get the index of the matched card from layout
        //add to the end of the vector in the matched index
        matches = getIndexOfMatchedCardOnLayout(cardsOnLayout, faceCardChosen, numCardsMatched);
        //optionChosen = chooseIndexOfMatchedCardOnLayout(matches);
        //only one card matched so get the first index of matches vector which is 0
        optionChosen = 0;
        cardsOnLayout.at(matches.at(optionChosen)).push_back(playedCard);
        //setting the stackedpairvalue
        stackedPairIndex = matches.at(optionChosen);

        break;
    case 2: //SAME AS CASE 1. HERE THE HUMAN HAS THE OPTION TO CHOSE FROM 2 possible cards
        matches = getIndexOfMatchedCardOnLayout(cardsOnLayout, faceCardChosen, numCardsMatched);
        optionChosen = chooseIndexOfMatchedCardOnLayout(matches);
        cardsOnLayout.at(matches.at(optionChosen)).push_back(playedCard);
        //setting the stackedpairvalue
        stackedPairIndex = matches.at(optionChosen);
        //print the cards on layout on stack format
        printLayoutStackFormat(cardsOnLayout);

        break;

    case 3:
        matches = getIndexOfMatchedCardOnLayout(cardsOnLayout, faceCardChosen, numCardsMatched);
        // matches = getIndexOfMatchedCardOnLayout(cardsOnLayout, playedCardIndex, numCardsMatched);
        //cout<<"\tThe size of the vector of matches is "<<matches.size()<<endl;
        cout << "\tYou just captured 3 cards from layout and one played by you\n";

        //add played card to the capture pile
        cardsOnCapturePile.push_back(playedCard);

        //create three deep copies of cards to push on the capture pile
        for (int i = 0; i < 3; i++)
        {
            //capture first three cards from the vector and create a deep copy and add it to capture pile of human
            Card *capturedCard = new Card(*cardsOnLayout.at(matches.at(i)).at(0));
            this->cardsOnCapturePile.push_back(capturedCard);
        }
        //erase the first three cards from the vector after capturing it
        numErasedCards = 0;
        //card with face value to delete
        faceValue = playedCard->getFace();

        //Deleting cards from layout one at a  time
        //Deleting all similar card will cause the vector to collapse or go out of range
        //so first face value match taken index and then break out from the loop and delete the card on that index
        //then get inside loop and find another face value and break out and delete the card and so on...
        removeCardsFromLayout(cardsOnLayout, faceValue, 3);

        //printing the capture pile after capturing the cards
        printCapturePileCards(getCardOnCapturePile());
        break;
    }

    //remove the card from the hand
    cardsOnHand.erase(cardsOnHand.begin() + playedCardIndex);

    return numCardsMatchedOnLayout;
} //END OF PLAY CARD FROM HAND
