/*
 ************************************************************
 * Name: Safal Bhandari                                     *
 * Project: C++ Go Stop                                     *
 * Class: OPL Spring 20                                     *
 * Date: 02/17/2020                                         *
 ************************************************************
*/
#include "Round.h"
#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/**********************************************************************
 * Function Name: ROUND
 * Purpose: 
 *                  To set up the member variables from the round class and create a computer
 *                  class player for help option for human player. Used when a new round is started
 *                  and on each successive round
 * Parameters:
 *                  humanPlayer, object of human class that represents a human player
 *                  computerPlayer, object of computer class that represents a computer player
 *                  currentRound, round that is currently being played
 *                  nextPlayerToPlay, index of player whose turn it is to play next
 * Return Value:
 *                  None
 * Local Variables: 
 *                  None
 * Algorithm:       
 *                  sets up the round by calling the roundSetup function and 
 *                  dealing cards to players and stock and layout pile
 *                  
 * Assistance Received: None
 **********************************************************************/
ROUND::ROUND(PLAYER *humanPlayer, PLAYER *computerPlayer, int currentRound, int nextPlayerToPlay)
{

    //set the current round value to roundNumber variable
    this->roundNumber = currentRound;
    //empty when the game just started
    this->nextPlayerTurn = "";
    //new game true for game just started
    this->newGame = true;
    //set the humanHelper bot to index 0
    players[HUMAN_HELPER_BOT] = new COMPUTER("BOT_HELPER");
    //setting helperbot member variable in player class to true to make a distinction between computer object
    //and helper computer object
    players[HUMAN_HELPER_BOT]->setHelperBot(true);

    //set human player to index 1
    players[HUMAN_INDEX] = humanPlayer;
    //set computer player to index 2
    players[COMPUTER_INDEX] = computerPlayer;

    //setting up round when new game is started
    roundSetup();

    //here check if players turn to play is what
    //if negative do set up first player
    //else set it to what ever value is passed
    //set up first player
    //cout<<"The next player to play passed is CHECKING "<<nextPlayerToPlay;
    if (nextPlayerToPlay == -1)
    {
        //meanse the last round was draw or this is the first round
        //determine first player to play
        setUpFirstPlayer();
    }
    else if (nextPlayerToPlay == HUMAN_INDEX)
    {
        this->nextPlayer = HUMAN_INDEX;
    }
    else
    {
        this->nextPlayer = COMPUTER_INDEX;
    }

    //for checking
    //cout<<"The next player to play is CHECKING "<< this->nextPlayer<<endl;

    //STARTING THE ROUND FROM HERE FOR NOW
    startRound();
}

/**********************************************************************
 * Function Name:   ROUND- overloading constructor
 * Purpose: 
 *                  To set up the players, round, nextplayer turn, cardOnLayout, cardOnStockpile. 
 *                  Userd to create a round object when instance of a round class is loaded from a file 
 * Parameters:
 *                  humanPlayer, object of human class that represents a human player
 *                  computerPlayer, object of computer class that represents a computer player
 *                  currentRound, round that is currently being played
 *                  nextPlayerToPlay, index of player whose turn it is to play next
 *                  cardsOnLayoutPassed, state of layout passed when Round object is created
 *                  cardsOnStockPilePassed, state of stockpile passed when Round object is created
 *                  nextPlayerTurnPassed, next player turn as a string value; Human or Computer
 * Return Value:
 *                  None
 * Local Variables: 
 *                  None
 * Algorithm:       
 *                  sets up the round by creating a computer object for help function provided to human,
 *                  sets cardsOnLayout passed, cardsOnStockPile passed and begins the round by calling 
 *                  startRound function 
 *                  
 * Assistance Received: None
 **********************************************************************/
ROUND::ROUND(PLAYER *humanPlayer, PLAYER *computerPlayer, int currentRound, int nextPlayerPassed, vector<vector<Card *> > cardsOnLayoutPassed, vector<Card *> cardsOnStockPilePassed, string nextPlayerTurnPassed)
{

    //setting the round number
    this->roundNumber = currentRound;
    //empty when the game just started

    this->nextPlayerTurn = nextPlayerPassed;

    //set the humanHelper bot to index 0
    players[HUMAN_HELPER_BOT] = new COMPUTER("BOT_HELPER");
    //setting helperbot member variable in player class to true to make a distinction between computer object
    //and helper computer object
    players[HUMAN_HELPER_BOT]->setHelperBot(true);

    //set human player to index 1
    players[HUMAN_INDEX] = humanPlayer;
    //set computer player to index 2
    players[COMPUTER_INDEX] = computerPlayer;

    //set nextPlayer variable (index of the player who is to play next)
    this->nextPlayer = nextPlayerPassed;

    //set the cards on layout
    setCardsOnLayout(cardsOnLayoutPassed);

    //set the cards on stock pile
    setCardsOnStockPile(cardsOnStockPilePassed);

    //printing for checking if load was successful or not
    //printVectors for checking
    printVectors();

    //STARTING THE ROUND FROM HERE FOR NOW
    startRound();
}

/**********************************************************************
 * Function Name: roundSetup
 * Purpose: 
 *                  To deal cards to the necessary member variables and set up variables
 *                  in correct order before beginning the game 
 * Parameters:
 *                  None
 * Return Value:
 *                  Void
 * Local Variables: 
 *                  deckObj, an object of Deck class that creates a deck of 104 cards
 *                  for the round           
 * Algorithm:       
 *                  creates a deck object, shuffles that deck object and
 *                  and assigns it to cardDeck which then distributes the cards to
 *                  hand of human and computer player, layout, and 
 *                  stock pile by calling dealAllCards function
 *                  and prints all the vector of cards for display in the 
 *                  end
 *                  
 * Assistance Received: None
 **********************************************************************/
void ROUND::roundSetup()
{

    //creates a deck of cards of 104 cards and shuffles the deck
    Deck deckObj;
    deckObj.shuffleDeck();

    //another deck object
    Deck deckObj2;
    deckObj2.shuffleDeck();

    vector<Card *> tempVect = deckObj.getDeck();
    vector<Card *> tempVect2 = deckObj2.getDeck();

    this->cardDeck.insert(this->cardDeck.begin(), tempVect.begin(), tempVect.end());
    this->cardDeck.insert(this->cardDeck.end(), tempVect2.begin(), tempVect2.end());

    //Printing the shuffled deck
    int j = 0;
    cout << "\n\tShuffled Card Deck: ";
    for (Card *i : cardDeck)
    {
        j++;
        cout << i->getFace() << i->getSuit() << " ";
        if (j == 50)
        {
            cout << "\n\t";
        }
    }

    cout << "\n\tSize of Shuffled Deck: " << cardDeck.size() << endl;

    //function that deals card to the player, computer, layout, and stock Pile
    dealAllCards();

    //printing the game table after setup and before beginning turns
    printVectors();
}

/**********************************************************************
 * Function Name: setUpFirstPlayer
 * Purpose: 
 *                  To set up and determine whose turn is to play first 
 * Parameters:
 *                  None
 * Return Value:
 *                  Void
 * Local Variables: 
 *                  firstPlayerIndex, an Int value which holds index of the
 *                  first player.                   
 * Algorithm:       
 *                  calls determineFirstPlayer() to determine whose turn is 
 *                  to play first. If the function returns INT_MAX means there
 *                  is a draw(MODULO SUIT) so the player's hand, deck, layout, and stockpile 
 *                  are all emptied and refilled again to to determine the turn 
 *                  
 * Assistance Received: None
 **********************************************************************/
void ROUND::setUpFirstPlayer()
{
    //determines and returns the index of the player scheduled to make the first move
    int firstPlayerIndex = determineFirstPlayer();

    //if there is a modulo suit case then goes inside the while loop, clear all cards from hand, deck, layout, and stock and deals new cards
    //again to determine the first player again
    while (firstPlayerIndex == INT_MAX)
    {

        //printing modulo suit case
        cout << "There is MODULO SUIT. Dealing again\n";
        //means clear all object and deal again and determine first player again

        //clear all the cards
        players[HUMAN_INDEX]->emptyCardsOnHand();
        players[COMPUTER_INDEX]->emptyCardsOnHand();
        clearCardsFromDeck();
        clearCardsFromLayout();
        clearCardsFromStockPile();

        Deck deckObj;
        //shuffle it
        deckObj.shuffleDeck();
        vector<Card *> tempVect = deckObj.getDeck();

        Deck deckObj2;
        vector<Card *> tempVect2 = deckObj2.getDeck();

        //set the deck
        this->cardDeck.insert(this->cardDeck.begin(), tempVect.begin(), tempVect.end());
        this->cardDeck.insert(this->cardDeck.end(), tempVect2.begin(), tempVect2.end());

        //set the deck
        //this->cardDeck = deckObj2.getDeck();

        //deal the cards again
        dealAllCards();
        //Prin to show
        printVectors();

        //call determine first player again to determine the first player
        firstPlayerIndex = determineFirstPlayer();
    }

    this->nextPlayer = firstPlayerIndex;
}

/**********************************************************************
 * Function Name:   startRound
 * Purpose: 
 *                  To set up the players, round, nextplayer turn, cardOnLayout, cardOnStockpile. 
 *                  Userd to create a round object when instance of a round class is loaded from a file 
 * Parameters:
 *                  None
 * Return Value:
 *                  Void
 * Local Variables: 
 *                  None
 * Algorithm:       
 *                   Displays menu giving options for user to make a move
 *                   While the round does not end, lets the players play.
 *                   Round ends when the size of hand of both player is equal to 0.
 *                   Change players after each player makes a move.
 *                   Checks if player saved or quit the game. Quit the program
 *                   if player chose to quit. Save and quit if player chose to save
 *                   After round is complete, display the score and captured hand
 *                   and determine who won the round
 *                  
 * Assistance Received: None
 **********************************************************************/
void ROUND::startRound()
{

    //holds the next player index temporarily to be later assigned to next player variable
    int tempNextPlayer;
    //roundComplete when handSizeComputerAndHuman is 2
    int roundComplete = 0;

    //start the turns and end the game when both players have played all their cards
    while (cardOnStockPile.size() != 0)
    {
        //printing out whose turn it is to play
        if (nextPlayer == HUMAN_INDEX)
        {
            cout << "\nHUMAN's TURN\n";
        }
        else if (nextPlayer == COMPUTER_INDEX)
        {
            cout << "\nBOT's TURN\n";
        }
        else
        {
            cout << "\nHELPER BOT\n";
        }

        int optionChosen = displayMenu(nextPlayer);

        switch (optionChosen)
        {

        case 1:
            //save the game to a file and exit
            saveGameAndExit();
            break;

        case 2:
            players[nextPlayer]->play(getCardsOnLayout(), getCardsOnStockPile());
            //get the size of the hand of the player and check if it is zero . if zero increment roundComplete by 1;
            if (players[nextPlayer]->sizeOfHandCards() == 0)
            {
                roundComplete++;
            }
            if (roundComplete == 2)
            {
                this->isRoundComplete = true;
            }
            //check if roundComplete is 2. If yes, both the hands of computer and human is zero. So the round is complete.
            break;

        case 3:
            if (this->nextPlayer == COMPUTER_INDEX)
            {
                cout << "\tOption 3 is only for human player. Please select other option\n";
            }
            else
            {
                cout << "\t*************TURN SIMULATION FOR HUMAN HELP STARTS******************\n";
                nextPlayer = HUMAN_HELPER_BOT;

                //first we need to get the hand of human index, and capture pile of human index
                //set the helper computer player hand and capture pile to the hand and capture pile taken from human object

                //Also check if capture pile and cards on hand of human player is passed by referenceo
                //or passed by value. Make sure it is passed by value so any changes on helper object
                //won't end up effecting the human cards from the human player object

                players[nextPlayer]->setCardOnCapturePile(players[HUMAN_INDEX]->getCardOnCapturePile());
                players[nextPlayer]->setCardsOnHand(players[HUMAN_INDEX]->getCardsOnHand());

                vector<vector<Card *> > cardsOnLayoutTemp = getCardsOnLayoutByValue();
                vector<Card *> cardsOnStockPileTemp = getCardsOnStockPileByValue();

                //players[nextPlayer]->play(getCardsOnLayout(), getCardsOnStockPile());
                //passing by value so any changes won't affect the actual game
                players[nextPlayer]->play(cardsOnLayoutTemp, cardsOnStockPileTemp);

                //clear the hand and capture pile from the helper player
                players[nextPlayer]->emptyCardsOnCapturePile();
                players[nextPlayer]->emptyCardsOnHand();

                //then make necessary adjustments on the computer class to display the recommendation

                cout << "\t*************TURN SIMULATION FOR HUMAN HELP ENDS******************\n";
            }

            break;

        case 4:
            // if you want to display the stats of the program display it here then return
            return;

            break;
        }

        if (!(optionChosen == 3 && this->nextPlayer == COMPUTER_INDEX))
        {
            printVectors();

            if (this->isRoundComplete == true)
            {
                //calculates the winner of the round and also sets the players total score until now from all
                // rounds played until now
                roundCompleteInfo();
                //breaks the while loop and goes back to Game class object
                break;
            }

            if (optionChosen == 2 || optionChosen == 3)
            {

                if (nextPlayer == HUMAN_INDEX)
                {
                    tempNextPlayer = COMPUTER_INDEX;
                }
                else if (nextPlayer == COMPUTER_INDEX)
                {
                    tempNextPlayer = HUMAN_INDEX;
                }
                if (nextPlayer == HUMAN_HELPER_BOT)
                {
                    tempNextPlayer = HUMAN_INDEX;
                }

                nextPlayer = tempNextPlayer;
            }

        } //end of outer if statement

    } //end of while loop
}

/**********************************************************************
 * Function Name: saveGameAndExit
 * Purpose: 
 *                  To save the current state of the game and exit 
 * Parameters:
 *                  None
 * Return Value:
 *                  Void
 * Local Variables: 
 *                  nextPlayerInString, a string value which holds name of player whose turn is to
 *                  play next
 *                  singleVectorLayout, vector of pointer to cards
 *                  serializerObject, an object of serializer class to save the game to a file
 * Algorithm        Created a serializer object and get necessary information from the round, player,
 *                  human, and computer class and pass it to the serializer object constructor and call
 *                  the saveToFile function to save the state of the game        
 * Assistance Received: None
 **********************************************************************/
void ROUND::saveGameAndExit()
{
    //stores string value of nextplayer
    string nextPlayerInString;
    //stores cards in layout on a single vector of cards
    vector<Card *> singleVectorLayout;
    //create a serializerObject
    SERIALIZER *serializerObject;

    //create a serialization object to save the state of the program
    serializerObject = new SERIALIZER();

    //get the string representation of next player to pass to serializer object to save it
    if (this->nextPlayer == HUMAN_INDEX)
    {
        nextPlayerInString = "Human";
    }
    else
    {
        nextPlayerInString = "Computer";
    }

    //change the vector of vector of cards on layout to a single vector of cards on layout to pass it to serializer object
    //loop throug cards on layout and assign all the variables to singleVectorLayout

    for (vector<Card *> i : cardOnLayout)
    {
        if (i.size() == 1)
        {
            singleVectorLayout.push_back(i.at(0));
        }
    }

    serializerObject->saveToFile("saveFile.txt", nextPlayerInString, this->roundNumber, players[COMPUTER_INDEX]->getTotalScore(), players[COMPUTER_INDEX]->getCardsOnHand(), players[COMPUTER_INDEX]->getCardOnCapturePile(),
                                 players[HUMAN_INDEX]->getTotalScore(), players[HUMAN_INDEX]->getCardsOnHand(), players[HUMAN_INDEX]->getCardOnCapturePile(), singleVectorLayout, getCardsOnStockPile());

    //exit the program after saving the game
    cout << "\n*****Program saved to a file. Exiting the Program******" << endl;
    exit(0);
}

/**********************************************************************
 * Function Name: roundCompleteInfo
 * Purpose: 
 *                  To get the score of human and computer when the round is complete
 *                  and set total score for the player and human and display who won 
 *                  the round
 * Parameters:
 *                  None
 * Return Value:
 *                  Void
 * Local Variables: 
 *                  humanScore, an Int value which holds score of human player
 *                  computerScore, an Int value which holds computer player score
 *                  humanUpdatedTotalScore, holds the sum of all the scores in all rounds 
 *                  played until now by human
 *                  computerUpdatedTotalScore, holds the sum of all the scores in all rounds 
 *                  played until now by computer
 * 
 * Algorithm:       
 *                  calculates the human and computer score of all the rounds played by calling
 *                  the appropriate function from the player class and displays the score of the
 *                  current round and total score until now to determine the winner of all the 
 *                  rounds until now and the winner of the current round.
 *                  
 * Assistance Received: None
 **********************************************************************/
void ROUND::roundCompleteInfo()
{

    int humanScore = players[HUMAN_INDEX]->calculateScore();
    int computerScore = players[COMPUTER_INDEX]->calculateScore();

    //set the winner index to whoever won the round
    if (humanScore > computerScore)
    {
        this->roundWinnerIndex = HUMAN_INDEX;
    }
    else if (humanScore < computerScore)
    {
        this->roundWinnerIndex = COMPUTER_INDEX;
    }
    else
    {
        this->roundWinnerIndex = -1;
    }

    //also set the total score of the players
    int humanUpdatedTotalScore = players[HUMAN_INDEX]->getTotalScore() + humanScore;
    int computerUpdatedTotalScore = players[COMPUTER_INDEX]->getTotalScore() + computerScore;

    //update total score for human and computer
    players[HUMAN_INDEX]->setTotalScore(humanUpdatedTotalScore);
    players[COMPUTER_INDEX]->setTotalScore(computerUpdatedTotalScore);

    //Printing the result of the round
    cout << "\n\tComputer Score: Current Round: " << computerScore << " \t Total Score: " << computerUpdatedTotalScore << endl;
    cout << "\n\tHuman Score: Current Round:    " << humanScore << " \t Total Score: " << humanUpdatedTotalScore << endl;
}

/**********************************************************************
 * Function Name: displayMenu
 * Purpose: 
 *                  Displays the menu to take user input on what the user wants to do 
 *                  when it is their turn to play
 * Parameters:
 *                  None
 * Return Value:
 *                  an integer value that holds the user's choice from the menu
 * Local Variables: 
 *                  optionChosen, a string value that holds the user's choice
 * 
 *                  
 * Assistance Received: None
 **********************************************************************/
int ROUND::displayMenu(int humanOrComputer)
{

    string optionChosen;

    do
    {
        cout << "\n\t1. Save the game";
        cout << "\n\t2. Make a move";

        if (humanOrComputer == HUMAN_INDEX)
        {
            cout << "\n\t3. Ask for help ";
        }
        else
        {
            cout << "\n\t3. ----------- ";
        }

        cout << "\n\t4. Quit the game\n";
        cout << "\tPlease choose an option: ";
        cin >> optionChosen;

    } while (!cin || (optionChosen != "1" && optionChosen != "2" && optionChosen != "3" && optionChosen != "4"));

    return stoi(optionChosen);
}

/**********************************************************************
 * Function Name: dealAllCards
 * Purpose: 
 *                  distributes the deck of cards from decKCards to human and computer hands,
 *                  layout of the round, and the stock pile for the round
 * Parameters:
 *                  None
 * Return Value:
 *                  Void
 * Local Variables: 
 *                  i, an integer variable to loop through each element of the cardDeck
 * Algorithm:       
 *                  distributes first 5 cards from cardDeck are dealt to the human player
 *                  next 5 cards are dealt to the computer player
 *                  next 4 cards are placed face up in the layout
 *                  next 5 cards are dealt to the human player
 *                  next 5 cards are dealt to the computer player
 *                  next 4 cards are placed face up in the layout                
 * Assistance Received: None
 **********************************************************************/
void ROUND::dealAllCards()
{

    int i = 0;
    while (cardDeck.size() != 0)
    {

        if (i <= 4)
        {
            players[HUMAN_INDEX]->addCardOnHand(cardDeck.front());
        }
        else if (i > 4 && i <= 9)
        {
            players[COMPUTER_INDEX]->addCardOnHand(cardDeck.front());
        }
        else if (i > 9 && i <= 13)
        {
            vector<Card *> innerVector;
            innerVector.push_back(cardDeck.front());
            cardOnLayout.push_back(innerVector);
        }
        else if (i > 13 && i <= 18)
        {
            players[HUMAN_INDEX]->addCardOnHand(cardDeck.front());
        }
        else if (i > 18 && i <= 23)
        {
            players[COMPUTER_INDEX]->addCardOnHand(cardDeck.front());
        }
        else if (i > 23 && i <= 27)
        {
            vector<Card *> innerVector;
            innerVector.push_back(cardDeck.front());
            cardOnLayout.push_back(innerVector);
        }
        else
        {
            cardOnStockPile.push_back(cardDeck.front());
        }

        //remove the first element from the vector every time you add a card
        this->cardDeck.erase(cardDeck.begin());

        i++;
    }
}

/**********************************************************************
 * Function Name: printVectors
 * Purpose: 
 *                  To print cards on hand , cards on capture pile, and score of
 *                  both human and computer player. Also prints the layout and stock
 *                  pile of the round
 * Parameters:
 *                  None
 * Return Value:
 *                  Void
 * Local Variables: 
 *                  None              
 * Assistance Received:
 *                  None
 **********************************************************************/
void ROUND::printVectors()
{

    //Printing for checking the empty deck after assigning the cards to players
    // cout<<"\nPrinting the 0 Remaining card deck\t";
    // cout<<"Size is"<<cardDeck.size()<<"\t";
    // for(Card* i : cardDeck)
    //     cout << i->getFace() <<i->getSuit()<<" ";
    // cout<<endl;

    cout << endl;
    cout << "\t************************ CURRENT GAME STATE ***********************\n";

    //Printing the round number
    cout << "\n\t Current Round: " << this->roundNumber << endl;

    //Printing the humand hand
    vector<Card *> vectorHumanHand = players[HUMAN_INDEX]->getCardsOnHand();

    cout << "\n\t Human Hand \t Size:" << vectorHumanHand.size() << " \t";
    // for (Card *i : vectorHumanHand)
    //     cout << i->getFace() << i->getSuit() << " ";

    for (int i = 0; i < vectorHumanHand.size(); i++)
    {
        cout << i << "-" << vectorHumanHand.at(i)->getFace() << vectorHumanHand.at(i)->getSuit() << " ";
    }

    //Print the human capture pile
    vector<Card *> capturePileHuman = players[HUMAN_INDEX]->getCardOnCapturePile();
    //sort the capture pile before printing
    sort(capturePileHuman.begin(), capturePileHuman.end(), [](Card *lhs, Card *rhs) {
        return lhs->getFaceAsInteger() < rhs->getFaceAsInteger();
    });

    cout << "\tCapture Pile \t Size:" << capturePileHuman.size() << " \t";
    for (Card *i : capturePileHuman)
    {
        cout << i->getFace() << i->getSuit() << " ";
    }

    cout << " Score: " << players[HUMAN_INDEX]->getTotalScore();
    cout << endl;

    //Printing the computer hand
    vector<Card *> vectorComputerHand = players[COMPUTER_INDEX]->getCardsOnHand();
    cout << "\n\t Computer Hand \t Size:" << vectorComputerHand.size() << " \t";
    // for (Card *i : vectorComputerHand)
    //     cout << i->getFace() << i->getSuit() << " ";

    for (int i = 0; i < vectorComputerHand.size(); i++)
    {
        cout << i << "-" << vectorComputerHand.at(i)->getFace() << vectorComputerHand.at(i)->getSuit() << " ";
    }

    //Print the computer capture pile
    vector<Card *> capturePileComputer = players[COMPUTER_INDEX]->getCardOnCapturePile();

    //sort the capture pile before printing
    sort(capturePileComputer.begin(), capturePileComputer.end(), [](Card *lhs, Card *rhs) {
        return lhs->getFaceAsInteger() < rhs->getFaceAsInteger();
    });

    cout << "\tCapture Pile \t Size:" << capturePileComputer.size() << " \t";
    for (Card *i : capturePileComputer)
    {
        cout << i->getFace() << i->getSuit() << " ";
    }
    cout << " Score: " << players[COMPUTER_INDEX]->getTotalScore();
    cout << endl;

    //Print the layout
    int k = 0;
    cout << "\n\t Layout Hand  \t Size:" << cardOnLayout.size() << " \t";
    for (vector<Card *> i : cardOnLayout)
    {
        cout << k << "-";
        if (i.size() > 1)
        {
            // for (Card *j : i)
            // {

            //     cout << j->getFace() << j->getSuit() << "-";
            // }

            for (int j = 0; j < i.size(); j++)
            {
                if (j == i.size() - 1)
                {
                    cout << i.at(j)->getFace() << i.at(j)->getSuit();
                }
                else
                {
                    cout << i.at(j)->getFace() << i.at(j)->getSuit() << "-";
                }
            }
        }
        else
        {
            for (Card *j : i)
            {

                cout << j->getFace() << j->getSuit() << " ";
            }
        }

        cout << "\t";
        k++;
    }
    cout << endl;

    //Printing the stock file from front to make it readable on the screen
    cout << "\n\t Stock Pile \t Size:" << cardOnStockPile.size() << " \t";
    for (int i = cardOnStockPile.size() - 1; i >= 0; i--)
    {
        cout << cardOnStockPile.at(i)->getFace() << cardOnStockPile.at(i)->getSuit() << " ";
        if (i == 40)
        {
            cout << "\n\t ";
        }
    }
    cout << endl;

    cout << "\t************************ CURRENT GAME STATE ***********************\n";
}

/**********************************************************************
 * Function Name: determineFirstPlayer
 * Purpose: 
 *                  to determine the first players turn and return the index
 * Parameters:
 *                  None
 * Return Value:
 *                  integer value of whose turn it is to play
 * Local Variables: 
 *                  cardFrequencyMapperHuman, key:faces and value: its occurence in human hand
 *                  cardFrequencyMapperComputer, key:faces and value: its occurence in computer hand
 *                  faces, an array of integer that contains face value of a card from K to A desc
 *                  countHuman, int value of number of occurence of single value in hand of human
 *                  countComputer, int value of number of occurence of single value in hand of computer
 *                  sizeFaces, size of the array of faces i.e, 13
 * Algorithm:       
 *                  created hash map with face value as key and occurences of face value in hand as values
 *                  for both computer and human and compared the occurences starting from king to Ace in desc
 *                  order who ever has the more occurence of the face value during comparision which starts from
 *                  king first then queen then joker and so on, the first turn is awarded to that player. if every face value
 *                  has same number of occurence. INT_MAX is returned by the function
 * Assistance Received: None
 **********************************************************************/
int ROUND::determineFirstPlayer()
{

    map<string, int> cardFrequencyMapperHuman;
    map<string, int> cardFrequencyMapperComputer;

    //iterate over human card on Handsand store the frequency of occurences of the card faces value
    for (Card *eachCard : players[HUMAN_INDEX]->getCardsOnHand())
    {
        auto result = cardFrequencyMapperHuman.insert(std::pair<std::string, int>(eachCard->getFace(), 1));
        if (result.second == false)
            result.first->second++;
    }

    //iterate over Computer card on Hands and store the frequency of occurences of the card faces value
    for (Card *eachCard : players[COMPUTER_INDEX]->getCardsOnHand())
    {
        auto result = cardFrequencyMapperComputer.insert(std::pair<std::string, int>(eachCard->getFace(), 1));
        if (result.second == false)
            result.first->second++;
    }

    string faces[13] = {"K", "Q", "J", "X", "9", "8", "7", "6", "5", "4", "3", "2", "A"};
    int sizeFaces = sizeof(faces) / sizeof(faces[0]);

    int countHuman = 0;
    int countComputer = 0;
    for (int i = 0; i < sizeFaces; i++)
    {
        //map contains the element
        if (cardFrequencyMapperHuman.count(faces[i]) == 1)
        {
            countHuman = cardFrequencyMapperHuman.at(faces[i]);
        }
        //map does not contain the element
        else
        {
            countHuman = 0;
        }

        if (cardFrequencyMapperComputer.count(faces[i]) == 1)
        {
            countComputer = cardFrequencyMapperComputer.at(faces[i]);
        }
        else
        {
            countComputer = 0;
        }

        if (countHuman > countComputer)
        {
            return HUMAN_INDEX;
        }
        if (countHuman < countComputer)
        {
            return COMPUTER_INDEX;
        }
    }

    //returning INT_MAX indicates all the values in the card hand of human and computer is same
    return INT_MAX;
}

/**********************************************************************
 * Function Name: clearCardsFromDeck
 * Purpose: 
 *                  to remove all the cards from the cardDeck member variable
 * Parameters:
 *                  None
 * Return Value:
 *                  void
 * Local Variables: 
 *                  None
 * Assistance Received:
 *                   None
 **********************************************************************/
void ROUND::clearCardsFromDeck()
{
    this->cardDeck.clear();
}

/**********************************************************************
 * Function Name: clearCardsFromLayout
 * Purpose: 
 *                  to remove all the cards from the cardOnLayout member variable
 * Parameters:
 *                  None
 * Return Value:
 *                  void
 * Local Variables: 
 *                  None
 * Assistance Received:
 *                   None
 **********************************************************************/
void ROUND::clearCardsFromLayout()
{
    this->cardOnLayout.clear();
}

/**********************************************************************
 * Function Name: clearCardsFromStockPile
 * Purpose: 
 *                  to remove all the cards from the cardOnStockPile member variable
 * Parameters:
 *                  None
 * Return Value:
 *                  void
 * Local Variables: 
 *                  None
 * Assistance Received:
 *                   None
 **********************************************************************/
void ROUND::clearCardsFromStockPile()
{
    this->cardOnStockPile.clear();
}

/**********************************************************************
 * Function Name:  getIsRoundComplete
 * Purpose: 
 *                  returns bool value of isRoundComplete
 * Parameters:
 *                  None
 * Return Value:
 *                  boolean, true or false value
 * Local Variables: 
 *                  None
 * Assistance Received:
 *                   None
 **********************************************************************/
bool ROUND::getIsRoundComplete()
{
    return this->isRoundComplete;
}

/**********************************************************************
 * Function Name:  setIsRoundComplete
 * Purpose: 
 *                  set bool value of isRoundComplete
 * Parameters:
 *                  trueOrFalse, boolean value to set isRoundComplete to
 * Return Value:
 *                  None
 * Local Variables: 
 *                  None
 * Assistance Received:
 *                   None
 **********************************************************************/
void ROUND::setIsRoundComplete(bool trueOrFalse)
{
    this->isRoundComplete = trueOrFalse;
}

/**********************************************************************
 * Function Name:  getRoundWinnerIndex
 * Purpose: 
 *                  to get index of the winner of the round
 * Parameters:
 *                  None
 * Return Value:
 *                  roundWinnerIndex, index value of the winner of the round
 * Local Variables: 
 *                  None
 * Assistance Received:
 *                   None
 **********************************************************************/
int ROUND::getRoundWinnerIndex()
{
    return this->roundWinnerIndex;
}

/**********************************************************************
 * Function Name:  setRoundWinnerIndex
 * Purpose: 
 *                  set roundWinnerIndex to the passed parameter
 * Parameters:
 *                  index, int value to set the roundWinnerIndex to
 * Return Value:
 *                  None
 * Local Variables: 
 *                  None
 * Assistance Received:
 *                   None
 **********************************************************************/
void ROUND::setRoundWinnerIndex(int index)
{
    this->roundWinnerIndex = index;
}

/**********************************************************************
 * Function Name:  getCardsOnLayout
 * Purpose: 
 *                  to get the cardsOnLayout by reference
 * Parameters:
 *                  None
 * Return Value:
 *                  cardOnLayout, vector of vector of pointer to Cards  by Reference
 * Local Variables: 
 *                  None
 * Assistance Received:
 *                   None
 **********************************************************************/
vector<vector<Card *> > &ROUND::getCardsOnLayout()
{
    return this->cardOnLayout;
}

/**********************************************************************
 * Function Name:  getCardsOnStockPile
 * Purpose: 
 *                  to get the cardsOnStockPile by reference
 * Parameters:
 *                  None
 * Return Value:
 *                  cardOnStockPile,  vector of pointer to Cards by Reference
 * Local Variables: 
 *                  None
 * Assistance Received:
 *                   None
 **********************************************************************/
vector<Card *> &ROUND::getCardsOnStockPile()
{
    return this->cardOnStockPile;
}

/**********************************************************************
 * Function Name:  getCardsOnLayoutByValue
 * Purpose: 
 *                 to get the cardsOnLayout by value
 * Parameters:
 *                  None
 * Return Value:
 *                  cardOnLayout, vector of vector of pointer to Cards
 * Local Variables: 
 *                  None
 * Assistance Received:
 *                   None
 **********************************************************************/
vector<vector<Card *> > ROUND::getCardsOnLayoutByValue()
{
    return this->cardOnLayout;
}

/**********************************************************************
 * Function Name:  getCardsOnStockPileByValue
 * Purpose: 
 *                  to get the cardsOnStockPile by value
 * Parameters:
 *                  None
 * Return Value:
 *                  cardOnStockPile, vector of pointer to Cards  
 * Local Variables: 
 *                  None
 * Assistance Received:
 *                  None
 **********************************************************************/
vector<Card *> ROUND::getCardsOnStockPileByValue()
{
    return this->cardOnStockPile;
}

/**********************************************************************
 * Function Name:  setCardsOnLayout
 * Purpose: 
 *                  to set the cardsOnLayout to the passed parameter
 * Parameters:
 *                  cardsOnLayoutPassed, vector of vector of pointer to Cards
 * Return Value:
 *                  None
 * Local Variables: 
 *                  None
 * Assistance Received:
 *                   None
 **********************************************************************/
void ROUND::setCardsOnLayout(vector<vector<Card *> > cardsOnLayoutPassed)
{
    this->cardOnLayout = cardsOnLayoutPassed;
}

/**********************************************************************
 * Function Name:  setCardsOnStockPile
 * Purpose: 
 *                  to set the cardsOnStockPile to the passed parameter
 * Parameters:
 *                  cardsOnStockPilePassed,  vector of pointer to Cards
 * Return Value:
 *                  None
 * Local Variables: 
 *                  None
 * Assistance Received:
 *                   None
 **********************************************************************/
void ROUND::setCardsOnStockPile(vector<Card *> cardsOnStockPilePassed)
{
    this->cardOnStockPile = cardsOnStockPilePassed;
}

/**********************************************************************
 * Function Name:  getRoundNumber
 * Purpose: 
 *                 to get the value of roundNumber
 * Parameters:
 *                 None
 * Return Value:
 *                  roundNumber, int value of roundNumber
 * Local Variables: 
 *                  None
 * Assistance Received:
 *                   None
 **********************************************************************/
int ROUND::getRoundNumber()
{
    return this->roundNumber;
}

/**********************************************************************
 * Function Name:  setRoundNumber
 * Purpose: 
 *                 to set the value of roundNumber to passed parameter
 * Parameters:
 *                 roundNumber, int value passed to set it to roundNumber
 * Return Value:
 *                 None
 * Local Variables: 
 *                 None
 * Assistance Received:
 *                 None
 **********************************************************************/
void ROUND::setRoundNumber(int roundNumber)
{
    this->roundNumber = roundNumber;
}
