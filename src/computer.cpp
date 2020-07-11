/*
 ************************************************************
 * Name: Safal Bhandari                                     *
 * Project: C++ Go Stop                                     *
 * Class: OPL Spring 20                                     *
 * Date: 02/27/2020                                         *
 ************************************************************
*/
#include "computer.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

/**********************************************************************
* Function Name: play 
* Purpose: To implement strategy of play for computer player
* Parameters:
*                   cardsOnLayout, vector of vector of pointer to cards which is in the layout
*                   cardsOnStockPile, vector of pointer to cards which is in the stockpile
* Return Value: None 
* Local Variables: 
*                   stackedPairIndex, holds int value of index of the stacked pair 
*                   else if no stack pair holds -1
*                   numMatchedCards, holds int value of number of cards matched when played from
*                   hand by computer
* Algorithm:
*                   calls playCardFromHand function which is an implementation of computers move
*                   from their hand. This function implements the strategy for playing card from
*                   hand and returns number of card matched on the layout with the card chosen by
*                   the computer from hand. After playCardFromHand playCardFromStockPile function is 
*                   called that implements the strategy for the game when card is drawn from stock
*                   pile in the parent class Player
* Assistance Received: None
**********************************************************************/
void COMPUTER::play(vector<vector<Card *> > &cardsOnLayout, vector<Card *> &cardsOnStockPile)
{


    int stackedPairIndex = -1;

    //NOTE::here the value of 1 is also assigned as 2 because how many cards are matched is not checked in the event of stacked pair
    //i.e, 1 or 2 as this would make no difference in the logic of the function playcardfromstockpile
    int numMatchedCards = playCardFromHand(cardsOnLayout, stackedPairIndex);

    cout << "\tStacked Pair Index: " << stackedPairIndex << endl;

    playCardFromStockPile(cardsOnLayout, cardsOnStockPile, numMatchedCards, stackedPairIndex);

}

/**********************************************************************
* Function Name: playCardFromHand 
* Purpose: To implement strategy to play for hand for computer player
* Parameters:
*                   cardsOnLayout, vector of vector of pointer to cards which is in the layout
*                   stackedPairIndex, passed as reference to hold the stacked pair index
* Return Value:  
*                   numCardsMatchedOnLayout, int value of number of card matched on layout with the 
*                   card chosen by computer player from the hand
* Local Variables: 
*                   numCardsMatchedOnLayout, int value of the num cards matched on layout
*                   faceOnHand, face value of a card
*                   chosenCard, pointer to card holds the card chosen from hand
*                   capturedCard, pointer to the card to be captured 
*                   layoutCardFrequencyMapper, hashmap with face value as key and frequency of that
*                   value of layout as value of that key
*                   frequencyCard, int value of the total number of card of same face value on layout
*                   numErasedCards, int value that holds number of cards to be erased 
*                   tripleStackIndexReturn, int value of the stack of the triple stack if there is one
*                   faceValue, string value of the face value of the card
*                   numCardsMatched, int value of the number of cards matched
*                   matches, vector of int that contains index of the card with same face value as picked
*                   innerVector, vector of pointer to cards
*                   

* Algorithm:
*                   1. check if there is a triple stack present and if any card in layout matches the face value of 
*                   the triple stack if it is present if yes, capture the cards and return
*                   2. if no for number 1, then check to see if there are any 3 cards on the layout of same face value and
*                   that face value matches with any one of the card on the layout, if it matches with any card from the hand
*                   play that card and capture the 3 cards from the layout and the card from hand and reutrn. 
*                   3. if no for number 1, then look at card on the capture pile and try to play the card which is on the 
*                   capture pile with the card of same value from the layout and computer hand if such a situation exists
*                   if not try to play the card which is present on the layout and the hand, if yes, play the card if not
*                   play any card from the hand as there are no match between hand and the layout
* Assistance Received: None
**********************************************************************/
int COMPUTER::playCardFromHand(vector<vector<Card *> > &cardsOnLayout, int &stackedPairIndex)
{
    cout << "\n\n\tHAND PILE MOVE\n";
    //ALGORITHM FOR COMPUTER  (HOW TO PLAY FROM HAND)

    //stores num of card matched and returns in the end
    int numCardsMatchedOnLayout;

    //TRIPLE STACK HANDLING 
    string faceOnHand;
    int tripleStackIndexReturn = -1;
    for (int i = 0; i < cardsOnHand.size(); i++)
    {

        faceOnHand = cardsOnHand.at(i)->getFace();

        int tripleStackIndexReturn = findIndexMatchedTripleStack(cardsOnLayout, faceOnHand);
        if (tripleStackIndexReturn != -1)
        {

            if (isHelperBot == true)
            {

                //HELPER BOT MESSAGE PRINT HERE WITH IF STATEMENT FOR CAPTURING THREE CARD WITH THE SUGGESTION ***********************************
                cout << "\tRECOMMENDATION: Recommended card to play is " << cardsOnHand.at(i)->getFace() << cardsOnHand.at(i)->getSuit() << " from you hand to capture  a triple stack from the layout" << endl;
            }

            //means there is a match with the triple stack and face card on hand from the hand of the computer
            //Pushing the triple stacked pair to the capture pile
            Card *chosenCard = new Card(*cardsOnHand.at(i));
            cout << "\tCard Chosen from Hand: " << chosenCard->getFace() << chosenCard->getSuit() << "\n";

            for (int i = 0; i < 3; i++)
            {
                Card *capturedCard = new Card(*cardsOnLayout.at(tripleStackIndexReturn).at(i));
                this->cardsOnCapturePile.push_back(capturedCard);
            }

            //remove the triple stack from layout
            cardsOnLayout.erase(cardsOnLayout.begin() + tripleStackIndexReturn);

            //push the face card to the capture pile
            this->cardsOnCapturePile.push_back(chosenCard);

            //print triple stack captured
            //cout<<"Just captured triple stack \n";

            //number of cards matched on layout set to 3 because triple stack is captured
            numCardsMatchedOnLayout = 3;

            //remove the card from the hand here
            cardsOnHand.erase(cardsOnHand.begin() + i);

            //return here
            return numCardsMatchedOnLayout;

        } //end of if statement

    } //end of for loop
    //End of triple stack handling

    //create a hash map of vectors that contains the face value and the number of cards with that face value on the layout
    map<string, int> layoutCardFrequencyMapper;

    //iterate through the layout and store frequency on the map
    for (vector<Card *> i : cardsOnLayout)
    {
        //need to check with the first card on each vector inside the outer vector
        //because all the cards on vector of cards is going to be of the same face
        //Matches only with single cards ( does not contain stack pair and triple stack )
        if (i.size() == 1)
        {
            Card *cardOnLayoutToMatch = i.at(0);
            auto result = layoutCardFrequencyMapper.insert(std::pair<std::string, int>(cardOnLayoutToMatch->getFace(), 1));
            if (result.second == false)
            {
                result.first->second++;
            }
        }
    }

    //stores index of card to be played
    int cardToPlayIndex = -1;

    string faceCardHand;
    int frequencyCard = 0;
    for (int i = 0; i < cardsOnHand.size(); i++)
    {
        faceCardHand = cardsOnHand.at(i)->getFace();

        //if map contains the card
        if (layoutCardFrequencyMapper.count(faceCardHand) == 1)
        {
            //get the value of that card and check if it is 3
            frequencyCard = layoutCardFrequencyMapper.at(faceCardHand);

            //if three then return
            if (frequencyCard >= 3)
            {
                cardToPlayIndex = i;
                break;
            }
        }

    } //end of for loop

    vector<int> matches;
    string faceCardChosen;
    int numCardsMatched = 0;
    int numErasedCards;
    string faceValue;
    vector<Card *> capturePileVector;
    int vectorIndexLayout;
    vector<Card *> innerVector;

    //check if cardToPlayIndex is -1 or sth else. if it is something else then we have a card
    //matched from hand with 3 cards from the layout
    if (cardToPlayIndex != -1)
    {

        cout << "\n\tMatched With Three Cards of Same face. Card index to Play: " << cardToPlayIndex << endl;

        if (isHelperBot == true)
        {

            //HELPER BOT MESSAGE PRINT HERE WITH IF STATEMENT FOR CAPTURING THREE CARD WITH THE SUGGESTION ***********************************
            cout << "\n\tRECOMMENDATION:Recommended card to play is " << cardsOnHand.at(cardToPlayIndex)->getFace() << cardsOnHand.at(cardToPlayIndex)->getSuit() << " from you hand to capture  3 cards from the layout" << endl;
        }
        //else{
        numCardsMatchedOnLayout = 3;

        //capture the cards and add it to the capture pile
        //take the card out from the vector and make a move

        Card *playedCard = new Card(*cardsOnHand.at(cardToPlayIndex));

        faceCardChosen = playedCard->getFace();

        matches = getIndexOfMatchedCardOnLayout(cardsOnLayout, faceCardChosen, numCardsMatched);

        //add played card to the capture pile
        cardsOnCapturePile.push_back(playedCard);

        //create three deep copies of cards to push on the capture pile
        for (int i = 0; i < 3; i++)
        {
            //capture first three cards from the vector and create a deep copy and add it to
            //capture pile of human
            Card *capturedCard = new Card(*cardsOnLayout.at(matches.at(i)).at(0));
            this->cardsOnCapturePile.push_back(capturedCard);
        }
        //erase the first three cards from the vector after capturing it
        numErasedCards = 0;
        //card with face value to delete
        faceValue = playedCard->getFace();

        //Deleting cards from layout one at a  time
        removeCardsFromLayout(cardsOnLayout, faceValue, 3);

        capturePileVector = getCardOnCapturePile();

        //Printing the humand  Capture Pile

        cout << "\n\tCapture Pile: ";
        for (Card *i : capturePileVector)
        {
            cout << i->getFace() << i->getSuit() << " ";
        }
        cout << endl;

        //print computer's rational for playing
        if (isHelperBot == false)
        {

            cout << "\tCard chosen from Hand: " << playedCard->getFace() << playedCard->getSuit() << "\n";

            cout << "\tComputer Chose to play " << cardsOnHand.at(cardToPlayIndex)->getFace() << cardsOnHand.at(cardToPlayIndex)->getSuit() << " from the hand to capture 3 cards of same face from the layout and the played card along with it." << endl;
        }

        //}
    }
    else
    {
        //create a hash map of capture value and the number of cards on it as a key //the value of each key can be either 2 or 4
        //if the value of num of cards is 4 ignore
        //else if it is 2 then check if you have any card on your hand with that value
        //if you do check that value on the layout. if it exist create a stack pair with that value
        //if there are no face card with the keys of hash map of capture value then continue

        //create a hash map of vectors that contains the face value and the number of cards with that face value on the layout
        map<string, int> capturePileCardFrequencyMapper;
        //INDEX VECTOR CONTAINS POSSIBLE CARD TO BE PLAYED FROM HAND THAT HAS A CORRESPONDING CARD WITH SAME FACE VALUE AND FREQUENCY 2 ON CAPTURE PILE
        vector<int> indexVectorHand;
        //iterate over computer capture pile and store the frequency of occurences of the card faces value
        for (Card *eachCard : cardsOnCapturePile)
        {
            auto result = capturePileCardFrequencyMapper.insert(std::pair<std::string, int>(eachCard->getFace(), 1));
            if (result.second == false)
                result.first->second++;
        }

        for (int i = 0; i < cardsOnHand.size(); i++)
        {
            faceCardHand = cardsOnHand.at(i)->getFace();

            //if map contains the card
            if (capturePileCardFrequencyMapper.count(faceCardHand) == 1)
            {
                //get the value of that card and check if it is 2
                frequencyCard = capturePileCardFrequencyMapper.at(faceCardHand);

                //if frequence is 4 do nothing

                //if frequency is 2 then capture that card
                if (frequencyCard == 2 || frequencyCard == 6)
                {
                    indexVectorHand.push_back(i);
                }
            }

        } //end of for loop

        //loop through the layout vector
        //loop through the indexVectorHand if there is a match
        //set the value of variable cardToPlayIndex to that index
        //break
        for (int i = 0; i < cardsOnLayout.size(); i++)
        {

            if (cardsOnLayout.at(i).size() == 1)
            {
                Card *cardOnLayoutToMatch = cardsOnLayout.at(i).at(0);
                for (int j = 0; j < indexVectorHand.size(); j++)
                {
                    if (cardOnLayoutToMatch->getFace() == cardsOnHand.at(indexVectorHand.at(j))->getFace())
                    {
                        cardToPlayIndex = indexVectorHand.at(j);
                        vectorIndexLayout = i;
                        //break if you get a match
                        break;
                    }
                }
            }
        }

        //check if cardToPlay index is != -1 then play that card and set pairedindex card value as well
        if (cardToPlayIndex != -1)
        {
            cout << "\tMatched with Layout and Capture Pile. Card index to play " << cardToPlayIndex << endl;

            if (isHelperBot == true)
            {
                //HELPER BOT MESSAGE PRINT HERE WITH IF STATEMENT FOR CREATING STACK PAIR OF CARD WITH A PAIR ON CAPTURE PILE***********************************
                cout << "\tRECOMMENDATION: Recommended card to play is " << cardsOnHand.at(cardToPlayIndex)->getFace() << cardsOnHand.at(cardToPlayIndex)->getSuit() << " from you hand to create a stack pair that also has a match on your capture pile" << endl;
            } //else{
            //HELPER BOT MESSAGE PRINT HERE WITH IF STATEMENT FOR CREATING STACK PAIR OF CARD WITH A PAIR ON CAPTURE PILE***********************************

            //here we are setting number of cards matched on layout to 2. but the actual match can also be one here
            //there is no need to check if there is one match or two because when we pass this value to stock pile
            //as long as it is value assigned to this variable is one or two the result will be the same. so decided
            //not to get the actual matches as this statement will only execute if the value is one or two
            numCardsMatchedOnLayout = 2;

            //play the card
            //create a stack on the layout
            Card *playedCard = new Card(*cardsOnHand.at(cardToPlayIndex));
            //cout<<"\tThe card selected by the computer from hand to stack a pair that has a match on capture pile is"<<"\n";

            //add the card to create a stack pair on the vectorIndexLayout
            cardsOnLayout.at(vectorIndexLayout).push_back(playedCard);

            //set the stacked pair index value
            stackedPairIndex = vectorIndexLayout;

            //print the cards on layout on stack format
            //printLayoutStackFormat(cardsOnLayout);

            //print computer's rational for playing
            if (isHelperBot == false)
            {
                cout << "\tThe Computer Chose to play " << playedCard->getFace() << playedCard->getSuit() << " to create a stack pair that has a match on the capture pile" << endl;
            }

            //}
        }
        else
        {
            //handle another case here
            //check if any card on the layout matches any card on hand
            //loop through cards on layout and card on hand and if there is a match then store it in a vector
            //display the cards that computer can choose from
            //choose one of the cards
            vector<int> optionToChoseIndex;
            //if it does create a stack pair
            for (int i = 0; i < cardsOnLayout.size(); i++)
            {

                if (cardsOnLayout.at(i).size() == 1)
                {
                    //inner for loop for cards on hand
                    for (int j = 0; j < cardsOnHand.size(); j++)
                    {

                        if (cardsOnLayout.at(i).at(0)->getFace() == cardsOnHand.at(j)->getFace())
                        {
                            //face card on layout at index i is same as on hand at index j
                            cardToPlayIndex = j;
                            vectorIndexLayout = i;
                            //break if you get a match on cards
                            break;
                        }
                    }

                } //end of if statement

            } //end of for loop

            if (cardToPlayIndex != -1)
            {

                cout << "\tMatched with only Layout.  Card index to play " << cardToPlayIndex << endl;

                if (isHelperBot == true)
                {
                    cout << "\tRECOMMENDATION: Recommended card to play is " << cardsOnHand.at(cardToPlayIndex)->getFace() << cardsOnHand.at(cardToPlayIndex)->getSuit() << " from you hand to create a stack pair. You do not have any card on the capture pile that matches with the stack pair that is recommended" << endl;
                    //HELPER BOT MESSAGE PRINT HERE WITH IF STATEMENT FOR CREATING STACK PAIR BUT NO MATCH IN CAPTURE PILE***********************************

                } //else{

                numCardsMatchedOnLayout = 2;

                //if there was a match
                //play the card
                //create a stack on the layout
                Card *playedCard = new Card(*cardsOnHand.at(cardToPlayIndex));

                //add the card to create a stack pair on the vectorIndexLayout
                cardsOnLayout.at(vectorIndexLayout).push_back(playedCard);

                //set the stacked pair index value
                stackedPairIndex = vectorIndexLayout;

                //print computer's rational for playing
                if (isHelperBot == false)
                {

                    cout << "\tCard Chosen From Hand " << playedCard->getFace() << playedCard->getSuit() << "\n";

                    cout << "\tThe Computer Chose to play " << playedCard->getFace() << playedCard->getSuit() << " to create a stack pair. There is no match with the capture pile cards" << endl;
                }

                //}
            }
            else
            {

                if (isHelperBot == true)
                {
                    //HELPER BOT MESSAGE PRINT HERE WITH IF STATEMENT FOR ADDING CARD ON LAYOUT BECAUSE THERE IS NO MATCH ***********************************
                    cout << "\tRECOMMENDATION: You can play any card from your hand and add it to the layout. There is no card that matches on your hand and on the layout" << endl;
                }

                //else{

                if (isHelperBot == false)
                {
                    cout << "\tComputer Chose to play the first card on hand. There are no matches with the layout" << endl;
                }

                numCardsMatchedOnLayout = 0;
                //else get first(can take any card here) card from the hand and push it to the layout
                cardToPlayIndex = 0;
                Card *playedCard = new Card(*cardsOnHand.at(cardToPlayIndex));

                innerVector.push_back(playedCard);
                cardsOnLayout.push_back(innerVector);

                //}
            }
        }
    }

    cardsOnHand.erase(cardsOnHand.begin() + cardToPlayIndex);

    //printing the layout
    printLayoutStackFormat(cardsOnLayout);

    //return the number of card matched
    return numCardsMatchedOnLayout;
}
