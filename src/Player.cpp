/*
 ************************************************************
 * Name: Safal Bhandari                                     *
 * Project: C++ Go Stop                                     *
 * Class: OPL Spring 20                                     *
 * Date: 02/27/2020                                         *
 ************************************************************
*/
#include "Player.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

/**********************************************************************
 * Function Name: PLAYER - Default Constructor
 * Purpose: To construct the player object
 * Parameters: None
 * Assistance Received: None
 **********************************************************************/
PLAYER::PLAYER()
{
}

/**********************************************************************
 * Function Name: PLAYER - Overloading Constructor
 * Purpose: To construct the player object and assign name to it
 * Parameters: name, name of the player object created
 * Assistance Received: None
 **********************************************************************/
PLAYER::PLAYER(string name)
{
    this->playerName = name;
    this->totalScore = 0;
    this->isHelperBot = false;
}

/**********************************************************************
 * Function Name: PLAYER - Destructor
 * Purpose: To destruct the object created of the player class
 * Parameters: None
 * Assistance Received: None
 **********************************************************************/
PLAYER::~PLAYER()
{
}

/**********************************************************************
* Function Name:    calculateScore
* Purpose:          To calculate the score from the capturepile 
* Parameters:
*                   None
*
* Return Value:     score, integer value of the score of the player 
*
* Local Variables: 
*                   score, integer value of the points scored by the player
*                  capturePileFrequencyMapper, used to store the number of 
*                   occurence of the the face value of cards
* Algorithm:
*                   store the frequency of occurence of face value as value
*                   and face as the key in a hash map from the capture pile
*                   if any one face has a value equal to 4. The player scores
*                   a point.
*                   Add the points and return it as the score of the player
* Assistance Received: None
**********************************************************************/
int PLAYER::calculateScore()
{

    //holds the score calculated
    int score = 0;

    //create a hash map of frequency
    map<string, int> capturePileFrequencyMapper;

    //get the capture pile
    //iterate through the capture pile and store frequency on the map
    for (Card *i : cardsOnCapturePile)
    {
        //need to check with the first card on each vector inside the outer vector
        //because all the cards on vector of cards is going to be of the same face
        //Matches only with single cards ( does not contain stack pair and triple stack )
        auto result = capturePileFrequencyMapper.insert(std::pair<std::string, int>(i->getFace(), 1));
        if (result.second == false)
        {
            result.first->second++;
        }
    }

    //calculate score iterating through frequency hash map
    //cout<<"\tCapture Pile HashMap Content: \t";
    for (auto it = capturePileFrequencyMapper.cbegin(); it != capturePileFrequencyMapper.cend(); ++it)
    {

        if ((*it).second == 4 || (*it).second == 6)
        {
            score++;
        }
        else if ((*it).second == 8)
        {
            score += 2;
        }
    }
    return score;
}

/**********************************************************************
* Function Name:    checkCardOnLayout
* Purpose:          To check if the face value of a card exists on the layout
* Parameters:
*                   cardsOnLayout, vector of vector of pointer to cards on the layout
*                   faceCardChosen, string value of the face of the card 
*
* Return Value:     numCardsMatched, num of occurence of the faceCard( passed as a parameter)
*                    on the layout which is also passed as a parameter
*
* Local Variables: 
*                   numCardsMatched, occurence of the faceCard passed on the layout
* Algorithm:
*                   Iterate through cards on layout and compare the face value of the 
*                   cards on the layout to the face value passed and if it exists increment
*                   local variable numCardsMatched by 1;
* Assistance Received: None
**********************************************************************/
int PLAYER::checkCardOnLayout(vector<vector<Card *> > cardsOnLayout, string faceCardChosen)
{

    int numCardsMatched = 0;

    for (vector<Card *> i : cardsOnLayout)
    {
        //need to check with the first card on each vector inside the outer vector
        //because all the cards on vector of cards is going to be of the same face
        //Matches only with single cards ( does not contain stack pair and triple stack )
        if (i.size() == 1)
        {
            Card *cardOnLayoutToMatch = i.at(0);
            if (cardOnLayoutToMatch->getFace() == faceCardChosen)
            {
                numCardsMatched++;
            }
        }
    }

    cout << "\tCards Matched on Layout: " << numCardsMatched << endl;
    return numCardsMatched;
}

/**********************************************************************
* Function Name:    getIndexOfMatchedCardOnLayout
* Purpose:          To check and return index of vector of cards that only matches  one element
*                   on the layout with the passed parameter faceCardChosen
*                   ( not two, or three. Only one)
* Parameters:       
*                   cardsOnLayout, vector of vector of pointer to cards on the layout
*                   faceCardChosen, string value of the face of the card 
*                    
* Return Value:     matches, vector of int that contains the matched card index on the layout
*
* Local Variables: 
*                   matches, vector of integer value
* Algorithm:
*                   Iterate through cards on layout and compare the face value of the 
*                   cards on the layout to the face value passed and if it exists and if the
*                   size of the inside vector is only one then add that index of the layout to the matches 
*                   vector
* Assistance Received: None
**********************************************************************/
vector<int> PLAYER::getIndexOfMatchedCardOnLayout(vector<vector<Card *> > cardsOnLayout, string faceCardChosen, int &numCardsMatched)
{

    vector<int> matches;

    for (int i = 0; i < cardsOnLayout.size(); i++)
    {
        //need to check with the first card on each vector inside the outer vector
        //because all the cards on vector of cards is going to be of the same face
        vector<Card *> insideVector = cardsOnLayout.at(i);

        if (insideVector.size() == 1)
        {

            Card *cardOnLayoutToMatch = insideVector.at(0);

            if (cardOnLayoutToMatch->getFace() == faceCardChosen)
            {
                numCardsMatched++;
                matches.push_back(i);
            }
        }
    }

    return matches;
}

/**********************************************************************
* Function Name:    printLayoutStackFormat
* Purpose:          To print the layout in stack format
* Parameters:       
*                   cardsOnLayout, vector of vector of pointer to cards on the layout
* Return Value:     
*                   Void
* Local Variables: 
*                   None
* Assistance Received: None
**********************************************************************/
void PLAYER::printLayoutStackFormat(vector<vector<Card *> > cardsOnLayout)
{

    cout << "\tLayout: ";
    for (vector<Card *> i : cardsOnLayout)
    {

        for (Card *j : i)
        {

            cout << j->getFace() << j->getSuit() << "  ";
        }
        cout << "\t";
    }

    return;
}

//does not work if size of matches is 0
/**********************************************************************
* Function Name:    chooseIndexOfMatchedCardOnLayout
* Purpose:          To provide user with the option to choose the index of the matched
*                   card from the layout to play
* Parameters:       
*                   matches, vector of integer that contains the index of the cards on layout
*                   that is matched
*                    
* Return Value:     optionChosen, option chosen by the player
*
* Local Variables: 
*                   optionChosen, holds the value of option chosen by the player
* Assistance Received: None
**********************************************************************/
int PLAYER::chooseIndexOfMatchedCardOnLayout(vector<int> matches)
{
    //dependent on computer player name and when size is greater than 0
    //returns the first option from matches
    if (this->playerName == "Computer")
    {
        return 0;
    }

    int optionChosen;

    //cout<<"\tThe size of the vector of matches is "<<matches.size()<<endl;
    //because here only one index is matched..filtered from function checkCardOnLayout
    //that returns numCardsMatchedOnLayout. Only the oneMatch is used
    cout << "\tPlease select which index you want to match your drawn card and capture it with\n";
    //loop throug the vector and print the options
    for (int i = 0; i < matches.size(); i++)
    {
        cout << "\tOption " << i << " :" << matches.at(i) << "\n";
    }

    cout << "\tPlease enter the option selected: ";
    cin >> optionChosen;
    while (!cin || optionChosen < 0 || optionChosen >= matches.size())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\tPlease enter valid integer: ";
        cin >> optionChosen;
    }

    return optionChosen;
}

/**********************************************************************
* Function Name:    removeCardsFromLayout
* Purpose:          to remove cards from the layout 
* Parameters:       
*                   cardsOnLayout, vector of vector of pointer to cards on the layout
*                   faceCard, string value of the face card to remove 
*                   numCardsToRemove, total number of cards to be removed from the layout
*                   which is of the same face value that is passed(faceCard)
*            
* Return Value:     
*                   Void
* Local Variables: 
*                   numErasedCards, holds the number of cards removed from the layout
*                   valueToPop, holds the index of the card on the layout to remove
*
* Assistance Received: None
**********************************************************************/
void PLAYER::removeCardsFromLayout(vector<vector<Card *> > &cardsOnLayout, string faceCard, int numCardsToRemove)
{

    int numErasedCards = 0;
    int valueToPop = 0;
    while (numErasedCards < numCardsToRemove)
    {

        for (int i = 0; i < cardsOnLayout.size(); i++)
        {

            if (cardsOnLayout.at(i).size() > 0)
            {

                if (cardsOnLayout.at(i).at(0)->getFace() == faceCard)
                {
                    valueToPop = i;
                    break;
                }
            }
        }

        cardsOnLayout.at(valueToPop).pop_back();
        numErasedCards++;
    }

    //checking and removing if there are any inner vectors that are empty
    numErasedCards = 0;
    while (numErasedCards < numCardsToRemove)
    {
        //deletes the first empty vector inside layout when the function is called
        deleteEmptyVectorsInsideLayout(cardsOnLayout);
        numErasedCards++;
    }
}

/**********************************************************************
* Function Name:    printCapturePileCards
* Purpose:          to print cards from the capture pile
* Parameters:       
*                   None          
* Return Value:     
*                   Void
* Local Variables: 
*                   None
* Assistance Received: None
**********************************************************************/
void PLAYER::printCapturePileCards(vector<Card *> capturePilePassed)
{
    cout << "\n\tCapture Pile after Capture: \t Size:" << capturePilePassed.size() << " \t";
    for (Card *i : capturePilePassed)
    {
        cout << i->getFace() << i->getSuit() << " ";
    }
}

/**********************************************************************
* Function Name:    deleteEmptyVectorsInsideLayout
* Purpose:          to delete the first empty vector found inside the cardsOnLayout
* Parameters:       
*                   cardsOnLayout, vector of vector of pointer to cards on the layout         
* Return Value:     
*                   Void
* Local Variables: 
*                   indexOfInnerVectorToRemove, hold index of inner vector of layout to remove
* Assistance Received: None
**********************************************************************/
void PLAYER::deleteEmptyVectorsInsideLayout(vector<vector<Card *> > &cardsOnLayout)
{

    int indexOfInnerVectorToRemove = -1;
    ;

    for (int i = 0; i < cardsOnLayout.size(); i++)
    {

        if (cardsOnLayout.at(i).size() == 0)
        {
            indexOfInnerVectorToRemove = i;
            break;
        }
    }

    cardsOnLayout.erase(cardsOnLayout.begin() + indexOfInnerVectorToRemove);
}

/**********************************************************************
* Function Name:    findIndexMatchedTriple
* Purpose:          to find if there is a triple stack match with the face card chosen
*                   and return the index of triple stack if it exists
* Parameters:       
*                   cardsOnLayout, vector of vector of pointer to cards on the layout 
*                   faceCardChosen, string value of the faceCardChosen        
* Return Value:     
*                   int, index of triple stack if it exists else -1
* Local Variables: 
*                   tripleStackMatchedIndex, index value to return
*                   
* Assistance Received: None
**********************************************************************/
int PLAYER::findIndexMatchedTripleStack(vector<vector<Card *> > cardsOnLayout, string faceCardChosen)
{
    int tripleStackMatchedIndex = -1;

    for (int i = 0; i < cardsOnLayout.size(); i++)
    {
        //need to check with the first card on each vector inside the outer vector
        //because all the cards on vector of cards is going to be of the same face
        vector<Card *> insideVector = cardsOnLayout.at(i);

        if (insideVector.size() == 3)
        {

            Card *cardOnLayoutToMatch = insideVector.at(0);

            if (cardOnLayoutToMatch->getFace() == faceCardChosen)
            {
                tripleStackMatchedIndex = i;
                break;
            }
        }
    }
    return tripleStackMatchedIndex;
}

/**********************************************************************
* Function Name:    playCardFromStockPile
* Purpose:          Implements strategy for when the card is drawn for the stock pile 
* Parameters:
*                   cardsOnLayout, vector of vector of pointer to cards on the layout
*                   cardsOnStockPile, vector of pointer to cards on the capture pile
*                   numCardsMatchedOnHand, number of cards that was matched on hand
*                   stackedPairIndex, index of stackedPair on the layout of cards
*                   when played from the hand 
*
* Return Value:      
*                   None
* Local Variables: drawnCardFromStockPile, card that is picked from stock pile of type pointer to card
*                  numCardsMatchedFromStockPile, cards matched to the layout with drawn card
*                  innerVector,vector of pointer to card
*                  optionChosen, int value of option chosen by user
*                  matches, vector of int that contains index of matched card in the layout
*                  valueToPop, int value of value to pop 
*                  numErasedCard, total number of cards to  remove from layout 
*                  capturePileVector, vector of pointer to card  
*
* Algorithm:        H0 or H3 - If the card from the stock pile matches:
*                   no card in the layout, the card is added to the layout.
*                   one card in the layout, the player captures both the cards: the card played from the stock pile and the card from the layout that matches it.
*                   two cards in the layout, the player picks one of the two matching cards and captures it along with the card played from the stock pile.
*                   three cards in the layout or triple stack, the player captures all four cards.  
*                   H1 or H2: If the card from the stock pile matches:
*                   no card in the layout, the card is added to the layout. The pair of cards stacked in H1/H2 are captured.
*                   three cards in the layout or triple stack, the player captures all four cards. The pair of cards stacked in H1/H2 are also captured.
*                   any card in the layout other than the stack pair from H1/H2, the player captures both the pairs - the stacked pair and the current pair.
*                   only the stack pair from H1/H2, the player does not capture any card - the player leaves all three cards as a triple stack in the layout.
*                  
* Assistance Received: None
**********************************************************************/
void PLAYER::playCardFromStockPile(vector<vector<Card *> > &cardsOnLayout, vector<Card *> &cardsOnStockPile, int numCardsMatchedOnHand, int stackedPairIndex)
{

    //get the last element from the vector every time from the stock pile as the next card to draw
    //When printing the content of the stock pile always print it from the end so the display will show the last element of the stock pile
    //as the first element on the console(or GUI). Done this way for readability of the stock pile

    //card drawn from the stock pile get a deep copy
    Card *drawnCardFromStockPile = new Card(*cardsOnStockPile.at(cardsOnStockPile.size() - 1));
    //remove the card from the stock pile after copying it
    cardsOnStockPile.pop_back();

    //CHECKING IF CARD IS REMOVED AND COPIED OR NOT
    cout << "\n\n\tSTOCK PILE MOVE\n";
    cout << "\tCard drawn from Stock Pile: " << drawnCardFromStockPile->getFace() << drawnCardFromStockPile->getSuit() << endl;

    //cout<<"\tThe size of the stock pile after removal is"<<cardsOnStockPile.size()<<endl;

    //get face value of card drawn from stock pile
    string faceCardDrawnFromStockPile = drawnCardFromStockPile->getFace();
    //get the numbers of cards matched on the layout with face value of card chosen from stock pile
    int numCardsMatchedFromStockPileCard = checkCardOnLayout(cardsOnLayout, faceCardDrawnFromStockPile);

    // if cards matched on layout is greater than 3 then it is given the value to 3 because we handle only 3 cards matching at the most in this game.
    if (numCardsMatchedFromStockPileCard > 3)
    {
        numCardsMatchedFromStockPileCard = 3;
    }

    //TRIPLE STACK HANDLING CODE PART STARTS**************************************************************************************************************
    int tripleStackIndexReturn = findIndexMatchedTripleStack(cardsOnLayout, faceCardDrawnFromStockPile);
    if (tripleStackIndexReturn != -1)
    {

        if (numCardsMatchedOnHand == 1 || numCardsMatchedOnHand == 2)
        {

            //now capture the h1/h2 stacked pair as well because there is a stacked pair
            for (int i = 0; i < 2; i++)
            {
                Card *capturedCard = new Card(*cardsOnLayout.at(stackedPairIndex).at(i));
                this->cardsOnCapturePile.push_back(capturedCard);
            }

            //remove the stacked pair and the vector from the capture pile
            cardsOnLayout.erase(cardsOnLayout.begin() + stackedPairIndex);

        } //end of if statement for numCardsMatchedOnHand
        //means there is a match with the triple stack and face card chosen
        //Pushing the stacked pair to the capture pile

        //calling findIndexMatchedTriple stack inside again because removing the stacked pair index changes the index of the triplestack called before
        tripleStackIndexReturn = findIndexMatchedTripleStack(cardsOnLayout, faceCardDrawnFromStockPile);
        for (int i = 0; i < 3; i++)
        {
            Card *capturedCard = new Card(*cardsOnLayout.at(tripleStackIndexReturn).at(i));
            this->cardsOnCapturePile.push_back(capturedCard);
        }

        //remove the triple stack from layout
        cardsOnLayout.erase(cardsOnLayout.begin() + tripleStackIndexReturn);

        //push the face card to the capture pile
        this->cardsOnCapturePile.push_back(drawnCardFromStockPile);

        if (isHelperBot == true)
        {
            cout << "\tRECOMMENDATION: Recommend to capture the triple stack on the layout with the drawn card.";
        }
        else
        {
            //printing computer move here for strategy display
            cout << "\t" << this->playerName << " captured triple stack on the layout and the drawn card with it \n";
        } //end of ishelperBot if statement

        if (numCardsMatchedOnHand == 1 || numCardsMatchedOnHand == 2)
        {
            if (isHelperBot == true)
            {
                cout << "and capture the previously stacked pair index from last hand move .\n";
            }
            else
            {
                //printing computer move here for strategy display
                cout << "\t" << this->playerName << " also captured the previously stacked pair from last hand move.\n";
            } //end of ishelperBot if statement
        }

        return;
    }
    //TRIPLE STACK HANDLING CODE PART ENDS**********************************************************************************************

    vector<Card *> innerVector;
    vector<Card *> innerVectorForOneCardFromStackPair;
    int numCardsMatched = 0;
    vector<int> matches;
    int optionChosen;
    int numErasedCards;
    int valueToPop;
    vector<Card *> capturePileVector;

    //cout<<"CHECK1";

    if (numCardsMatchedOnHand == 0 || numCardsMatchedOnHand == 3)
    {
        //if card chosen from the stock pile matches 0,1,2,3 cards

        switch (numCardsMatchedFromStockPileCard)
        {
        case 0:
            //cout<<"CHECK2";
            innerVector.push_back(drawnCardFromStockPile);
            cardsOnLayout.push_back(innerVector);
            //cout<<"CHECK3";

            //
            if (isHelperBot == true)
            {
                cout << "\tRECOMMENDATION: Recommend to add a card to the layout because there is no match in the layout. "
                     << "That is the only option here. Follow the rules!\n ";
            }
            else
            {
                cout << "\t" << this->playerName << " added the card to the layout because there is no match in the layout.\n";
            }
            //

            break;
        case 1:
            //returns vector of matches that contains indexes of card  matched on layout with the card played from hand or stock
            matches = getIndexOfMatchedCardOnLayout(cardsOnLayout, faceCardDrawnFromStockPile, numCardsMatched);

            if (isHelperBot == true)
            {
                cout << "\tRECOMMENDATION: to pair the drawn card with " << cardsOnLayout.at(matches.at(0)).at(0)->getFace()
                     << cardsOnLayout.at(matches.at(0)).at(0)->getSuit() << " from the layout to create a stack pair and capture it" << endl;
            }
            else
            {
                //returns the option chosen by the human to match the card with and create a stack or capture it
                cout << "\t" << this->playerName << " has the following cards on layout to choose from.\n";
                optionChosen = chooseIndexOfMatchedCardOnLayout(matches);
                cout << "\t" << this->playerName << " paired the drawn card with " << cardsOnLayout.at(matches.at(optionChosen)).at(0)->getFace()
                     << cardsOnLayout.at(matches.at(optionChosen)).at(0)->getSuit() << " from the layout to create a stack pair and capture it" << endl;
            }

            //push the card drawn from the stock pile to the capture pile
            cardsOnCapturePile.push_back(drawnCardFromStockPile);

            //get the card from the layout and push it to the capture pile
            //size of matches is 1;

            for (int i = 0; i < matches.size(); i++)
            {
                Card *capturedCard = new Card(*cardsOnLayout.at(matches.at(i)).at(0));
                this->cardsOnCapturePile.push_back(capturedCard);
            }

            //erase the first one card from the vector after capturing it
            numErasedCards = 0;

            //Deleting cards from layout one at a  time
            //Deleting all similar card inside one loop will cause the vector to collapse or go out of range
            //so first face value match taken index and then break out from the loop and delete the card on that index
            //then get inside loop and find another face value and break out and delete the card and so on...
            //HERE Card to erase is one because we have one match on the layout

            removeCardsFromLayout(cardsOnLayout, faceCardDrawnFromStockPile, 1);

            //printing the capture pile after capturing the cards
            //printCapturePileCards(getCardOnCapturePile());

            break;
        case 2:
            matches = getIndexOfMatchedCardOnLayout(cardsOnLayout, faceCardDrawnFromStockPile, numCardsMatched);

            if (isHelperBot == true)
            {
                cout << "\tRECOMMENDATION: Recommend to pair the drawn card with " << cardsOnLayout.at(matches.at(0)).at(0)->getFace()
                     << cardsOnLayout.at(matches.at(0)).at(0)->getSuit() << " from the layout to create a stack pair and capture it" << endl;
            }
            else
            {
                cout << "\t" << this->playerName << " has the following cards on layout to choose from.\n";
                optionChosen = chooseIndexOfMatchedCardOnLayout(matches);
                cout << "\t" << this->playerName << " paired the drawn card with " << cardsOnLayout.at(matches.at(optionChosen)).at(0)->getFace()
                     << cardsOnLayout.at(matches.at(optionChosen)).at(0)->getSuit() << " from the layout to create a stack pair and capture it" << endl;
            }

            //push the card drawn from the stock pile to the capture pile
            cardsOnCapturePile.push_back(drawnCardFromStockPile);

            //get the card from the layout chosen by the human  from the layout pile and push it to the capture pile
            //size of matches is 1;

            //throwing it inside the loop to make the initialization of the capturedCard work otherwise declaring the captureCard inside the switch statement is not
            //allowed by c++
            for (int i = 0; i < 1; i++)
            {
                Card *capturedCard = new Card(*cardsOnLayout.at(matches.at(optionChosen)).at(0));
                this->cardsOnCapturePile.push_back(capturedCard);
            }

            //delete the card chosen by human from the layout
            cardsOnLayout.at(matches.at(optionChosen)).pop_back();
            //remove if there is any empty vector in layout after deletion
            deleteEmptyVectorsInsideLayout(cardsOnLayout);

            //printing the capture pile after capturing the cards: one from layout and another one is drawn from the stock pile
            //print the cards on layout on stack format HUMAN CAPTURE CARDS
            //printCapturePileCards(getCardOnCapturePile());

            break;

        case 3:
            matches = getIndexOfMatchedCardOnLayout(cardsOnLayout, faceCardDrawnFromStockPile, numCardsMatched);

            cout << "\t Three or more cards match with the card drawn from stock pile! \n";

            //add played card to the capture pile
            cardsOnCapturePile.push_back(drawnCardFromStockPile);

            if (isHelperBot == true)
            {
                cout << "\tRECOMMENDATION: Recommend to pair the drawn card with ";
            }

            //create three deep copies of cards to push on the capture pile and remaining matches are left untouched as per the algorithm
            for (int i = 0; i < 3; i++)
            {
                //capture first three cards from the vector and create a deep copy and add it to
                //capture pile of human
                Card *capturedCard = new Card(*cardsOnLayout.at(matches.at(i)).at(0));
                if (isHelperBot == true)
                {
                    cout << capturedCard->getFace() << capturedCard->getSuit() << " ";
                }
                this->cardsOnCapturePile.push_back(capturedCard);
            }
            if (isHelperBot == true)
            {
                cout << " from the layout to capture four cards.\n";
            }
            else
            {
                //printing computer move here for strategy display
                cout << "\t" << this->playerName << " captured 3 cards of same face as drawn card from the layout and the drawn card with it \n";
            }

            //Deleting cards from layout one at a  time
            //Deleting all similar card will cause the vector to collapse or go out of range
            //so first face value match taken index and then break out from the loop and delete the card on that index
            //then get inside loop and find another face value and break out and delete the card and so on...

            removeCardsFromLayout(cardsOnLayout, faceCardDrawnFromStockPile, 3);

            //printing the capture pile after capturing the cards
            //print the cards on layout on stack format HUMAN CAPTURE CARDS

            //printCapturePileCards(getCardOnCapturePile());

            break;
        }
        //in this else if value of stacked pair index will never be -1 because it executes only when stackedpair is created
        //so no need to check if it is negative
    }
    else if (numCardsMatchedOnHand == 1 || numCardsMatchedOnHand == 2)
    {

        switch (numCardsMatchedFromStockPileCard)
        {
        case 0:
            //if only the stack pair from h1/h2 is matched then create a triple stack and push it to layout
            //add three cards on the layout as separate vector so rather there are 3 card present than a
            //stack
            if (cardsOnLayout.at(stackedPairIndex).at(0)->getFace() == faceCardDrawnFromStockPile)
            {

                //COMMENTING OUT FOR THE MOMENT TO TEST TRIPLE STACK *******************************************************************************************
                //only removing and pushing the last card from the stacked pair to another vector of the
                //stack layout

                //COMMENTED OUT FROM HERE *******************************************************************************************
                // Card * captureCard = new Card(*cardsOnLayout.at(stackedPairIndex).at(1));
                // //removing from stacked pair last card
                // cardsOnLayout.at(stackedPairIndex).pop_back();
                // //adding that removed card to the layout with a new inner vector
                // innerVectorForOneCardFromStackPair.push_back(captureCard);

                // //adding the innerVector to the layout
                // //cardsOnLayout.push_back(innerVectorForOneCardFromStackPair);

                // //pushing the triple stack element one after another
                // cardsOnLayout.insert(cardsOnLayout.begin()+stackedPairIndex,innerVectorForOneCardFromStackPair);

                // //push the drawn card on cards on layout with another innervector
                // innerVector.push_back(drawnCardFromStockPile);

                // //cardsOnLayout.push_back(innerVector);

                // cardsOnLayout.insert(cardsOnLayout.begin()+stackedPairIndex,innerVector);
                //set is triple stack to true

                //COMMENTED OUT UNTIL HERE*******************************************************************************************

                //ADDED LINE TO CREATE A TRIPLE STACK
                cardsOnLayout.at(stackedPairIndex).push_back(drawnCardFromStockPile);

                if (isHelperBot == true)
                {
                    cout << "\tRECOMMENDATION: The card will match only with h1/h2 stack pair created from hand. So creating"
                         << " a triple stack and pushing it to the layout is recommended\n";
                }
                else
                {
                    cout << "\t" << this->playerName << " created a triple stack by pushing the drawn card to the stacked pair of the layout because the"
                         << " drawn card only matched with h1/h2 stack pair created from the hand.\n";
                }

                //COMMENTING OUT FOR THE MOMENT TO TEST TRIPLE STACK **************************************************************************************************
            }
            else
            { //if no card in the layout, the card is added to the layout.The pair of cards stacked in
                //h1/h2 are captured

                //Pushing the stacked pair to the capture pile
                for (int i = 0; i < 2; i++)
                {
                    Card *capturedCard = new Card(*cardsOnLayout.at(stackedPairIndex).at(i));
                    this->cardsOnCapturePile.push_back(capturedCard);
                }

                //remove the stacked pair and the vector from the capture pile
                cardsOnLayout.erase(cardsOnLayout.begin() + stackedPairIndex);

                innerVector.push_back(drawnCardFromStockPile);
                cardsOnLayout.push_back(innerVector);

                if (isHelperBot == true)
                {
                    cout << "\tRECOMMENDATION: The card does not match any card in layout so adding the drawn card to "
                         << "the layout is recommended and capture the previously stacked pair from hand. Play by the rules!\n";
                }
                else
                {
                    cout << "\t" << this->playerName << " added the drawn card to the layout because there is no match and captured the previously stacked pair from hand\n";
                }
            }

            //printing the capture pile after capturing the cards
            //print the cards on layout on stack format HUMAN CAPTURE CARDS
            //printCapturePileCards(getCardOnCapturePile());

            // cout<<"\n\tLayout After Move: ";
            // printLayoutStackFormat(cardsOnLayout);

            break;

        case 3:
            matches = getIndexOfMatchedCardOnLayout(cardsOnLayout, faceCardDrawnFromStockPile, numCardsMatched);

            //cout<<"\tThe size of the vector of matches is "<<matches.size()<<endl;
            //cout<<"\t You have 3 or more cards match. Congratulations!\n";
            //cout<<"\t You just captured 3 cards from layout and one played by you\n";

            //add played card to the capture pile
            cardsOnCapturePile.push_back(drawnCardFromStockPile);

            if (isHelperBot == true)
            {
                cout << "\tRECOMMENDATION: Recommend to pair the drawn card with ";
            }

            //create three deep copies of cards to push on the capture pile and remaining matches are left untouched as per the algorithm
            for (int i = 0; i < 3; i++)
            {
                //capture first three cards from the vector and create a deep copy and add it to
                //capture pile of human
                Card *capturedCard = new Card(*cardsOnLayout.at(matches.at(i)).at(0));
                if (isHelperBot == true)
                {
                    cout << capturedCard->getFace() << capturedCard->getSuit() << " ";
                }
                this->cardsOnCapturePile.push_back(capturedCard);
            }
            if (isHelperBot == true)
            {
                cout << " from the layout to capture four cards. Also capture the h1/h2 pair stacked before.\n";
            }
            else
            {
                //printing computer move here for strategy display
                cout << "\t" << this->playerName << " captured 3 cards of same face as drawn card from the layout and the drawn card with it. Also captured the"
                     << " h1/h2 pair stacked from hand before.\n";
            }

            //now capture the h1/h2 stacked pair as well

            //Pushing the stacked pair to the capture pile
            for (int i = 0; i < 2; i++)
            {
                Card *capturedCard = new Card(*cardsOnLayout.at(stackedPairIndex).at(i));
                this->cardsOnCapturePile.push_back(capturedCard);
            }

            //remove the stacked pair and the vector from the capture pile
            cardsOnLayout.erase(cardsOnLayout.begin() + stackedPairIndex);

            //Deleting cards from layout one at a  time
            //Deleting all similar card will cause the vector to collapse or go out of range
            //so first face value match taken index and then break out from the loop and delete the card on that index
            //then get inside loop and find another face value and break out and delete the card and so on...

            removeCardsFromLayout(cardsOnLayout, faceCardDrawnFromStockPile, 3);

            //printing the capture pile after capturing the cards
            //print the cards on layout on stack format HUMAN CAPTURE CARDS
            //printCapturePileCards(getCardOnCapturePile());

            break;
        case 1:
        case 2:

            //now capture the h1/h2 stacked pair as well

            //Pushing the stacked pair to the capture pile
            for (int i = 0; i < 2; i++)
            {
                Card *capturedCard = new Card(*cardsOnLayout.at(stackedPairIndex).at(i));
                this->cardsOnCapturePile.push_back(capturedCard);
            }

            //remove the stacked pair and the vector from the capture pile
            cardsOnLayout.erase(cardsOnLayout.begin() + stackedPairIndex);

            matches = getIndexOfMatchedCardOnLayout(cardsOnLayout, faceCardDrawnFromStockPile, numCardsMatched);

            if (isHelperBot == true)
            {
                cout << "\tRECOMMENDATION: Recommend to pair the drawn card with " << cardsOnLayout.at(matches.at(0)).at(0)->getFace()
                     << cardsOnLayout.at(matches.at(0)).at(0)->getSuit() << " from the layout to create a stack pair and capture it as well as the previous"
                     << " stack pair created from hand" << endl;
            }
            else
            {
                cout << "\t" << this->playerName << " has the following cards on layout to choose from.\n";
                optionChosen = chooseIndexOfMatchedCardOnLayout(matches);
                cout << "\t" << this->playerName << " paired the drawn card with " << cardsOnLayout.at(matches.at(optionChosen)).at(0)->getFace()
                     << cardsOnLayout.at(matches.at(optionChosen)).at(0)->getSuit() << " from the layout to create a stack pair and capture it as well as the previous"
                     << " stack pair created from hand" << endl;

                //push the card drawn from the stock pile to the capture pile
                cardsOnCapturePile.push_back(drawnCardFromStockPile);

                //get the card from the layout chosen by the human  from the layout pile and push it to the capture pile
                //size of matches is 1;

                //throwing it inside the loop to make the initialization of the capturedCard work otherwise declaring the captureCard inside the switch statement is not
                //allowed by c++
                for (int i = 0; i < 1; i++)
                {
                    Card *capturedCard = new Card(*cardsOnLayout.at(matches.at(optionChosen)).at(0));
                    this->cardsOnCapturePile.push_back(capturedCard);
                }

                //delete the card chosen by human from the layout
                cardsOnLayout.at(matches.at(optionChosen)).pop_back();

                //printing the capture pile after capturing the cards: one from layout and another one is drawn from the stock pile
                //print the cards on layout on stack format HUMAN CAPTURE CARDS
                //printCapturePileCards(getCardOnCapturePile());

                deleteEmptyVectorsInsideLayout(cardsOnLayout);
            }

            break;
        }
    }
    else
    {
        //Throw an exception saying numCardsMatchedOnHand can be 0,1,2, or 3
        //if this lock executes it means the value is not what is desired by program(the value is <0 so thrown an error)
    }
}

/**********************************************************************
 * Function Name:   emptyCardsOnHand
 * Purpose:         To clear and empty all cards from hand of the player
 * Parameters:      None            
 * Return Value:    None
 * Local Variables: None
 * Assistance Received: None
 **********************************************************************/
void PLAYER::emptyCardsOnHand()
{
    this->cardsOnHand.clear();
}

/**********************************************************************
 * Function Name:   emptyCardsOnCapturePile
 * Purpose:         To clear and empty all cards from capturepile of the player
 * Parameters:      None            
 * Return Value:    None
 * Local Variables: None
 * Assistance Received: None
 **********************************************************************/
void PLAYER::emptyCardsOnCapturePile()
{
    this->cardsOnCapturePile.clear();
}

/**********************************************************************
 * Function Name:   getName
 * Purpose:         to get the name of the player
 * Parameters:      None            
 * Return Value:    string, name of the player
 * Local Variables: None
 * Assistance Received: None
 **********************************************************************/
string PLAYER::getName()
{
    return this->playerName;
}

/**********************************************************************
 * Function Name:   setName
 * Purpose:         to set the name of the player
 * Parameters:      name, name of the player to set             
 * Return Value:    None
 * Local Variables: None
 * Assistance Received: None
 **********************************************************************/
void PLAYER::setName(string name)
{
    this->playerName = name;
}

/**********************************************************************
 * Function Name:   getCardsOnHand
 * Purpose:         to get the cards on the hand of the player
 * Parameters:      None            
 * Return Value:    Vector of pointer to cards on the hand of the player
 * Local Variables: None
 * Assistance Received: None
 **********************************************************************/
vector<Card *> PLAYER::getCardsOnHand()
{
    return this->cardsOnHand;
}

/**********************************************************************
 * Function Name:   setCardsOnHand
 * Purpose:         to set the cards on the hand of the player
 * Parameters:      cardsForHand, vector of pointer to cards             
 * Return Value:    None
 * Local Variables: None
 * Assistance Received: None
 **********************************************************************/
void PLAYER::setCardsOnHand(vector<Card *> cardsForHand)
{
    this->cardsOnHand = cardsForHand;
}

/**********************************************************************
 * Function Name:   sizeOFHandCards
 * Purpose:         returns the size of cards on hand of player
 * Parameters:      None            
 * Return Value:    int, size of the hand of player
 * Local Variables: None
 * Assistance Received: None
 **********************************************************************/
int PLAYER::sizeOfHandCards()
{
    return this->cardsOnHand.size();
}

/**********************************************************************
 * Function Name:   getCardsOnCapturePile
 * Purpose:         to get the cards on the capture pile of the player
 * Parameters:      None            
 * Return Value:    Vector of pointer to cards on the capturepile of the player
 * Local Variables: None
 * Assistance Received: None
 **********************************************************************/
vector<Card *> PLAYER::getCardOnCapturePile()
{
    return this->cardsOnCapturePile;
}

/**********************************************************************
 * Function Name:   setCardOnCapturePile
 * Purpose:         to set the cards on the capture pile of the player
 * Parameters:      cardsForCapturePile, vector of pointer to cards             
 * Return Value:    None
 * Local Variables: None
 * Assistance Received: None
 **********************************************************************/
void PLAYER::setCardOnCapturePile(vector<Card *> cardsForCapturePile)
{
    this->cardsOnCapturePile = cardsForCapturePile;
}

/**********************************************************************
 * Function Name:   addCardOnHand
 * Purpose:         to add a pointer to card to the hand of player
 * Parameters:      cardToAdd, a pointer to card object             
 * Return Value:    None
 * Local Variables: None
 * Assistance Received: None
 **********************************************************************/
void PLAYER::addCardOnHand(Card *cardToAdd)
{
    cardsOnHand.push_back(cardToAdd);
}

// //Implement whichever way is clear and efficient later on
// void PLAYER::removeCardFromHand(Card* cardToRemove){

// }

/**********************************************************************
 * Function Name:   addCardOnCapturePile
 * Purpose:         to add a pointer to card to the capturePile of player
 * Parameters:      cardToAdd, a pointer to card object             
 * Return Value:    None
 * Local Variables: None
 * Assistance Received: None
 **********************************************************************/
void PLAYER::addCardOnCapturePile(Card cardToAdd)
{
    cardsOnCapturePile.push_back(&cardToAdd);
}

// //Impement whichever way is clear and efficient later on
// void PLAYER::removeCardFromCapturePile(Card cardToRemove){

// }

/**********************************************************************
 * Function Name:   setHelperBot
 * Purpose:         to set the value of helperbot
 * Parameters:      trueOrFalse, a boolean value to set isHelperBot to         
 * Return Value:    None
 * Local Variables: None
 * Assistance Received: None
 **********************************************************************/
void PLAYER::setHelperBot(bool trueOrFalse)
{
    isHelperBot = trueOrFalse;
}

/**********************************************************************
 * Function Name:   getTotalScore
 * Purpose:         to get the totalScore of the player
 * Parameters:      None             
 * Return Value:    int, score of the player
 * Local Variables: None
 * Assistance Received: None
 **********************************************************************/
int PLAYER::getTotalScore()
{
    return totalScore;
}

/**********************************************************************
 * Function Name:   setTotalScore
 * Purpose:         to set the totalScore of the player
 * Parameters:      totalScorePassed, score passed to set to the totalScore             
 * Return Value:    None
 * Local Variables: None
 * Assistance Received: None
 **********************************************************************/
void PLAYER::setTotalScore(int totalScorePassed)
{
    this->totalScore = totalScorePassed;
}

//getter/setter for rounds played
// int PLAYER::getRoundsPlayed(){
//     return this->roundsPlayed;
// }

// void PLAYER::setRoundsPlayed(int totalRoundsPlayed){
//     this->roundsPlayed = totalRoundsPlayed;
// }
