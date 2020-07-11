/*
 ************************************************************
 * Name: Safal Bhandari                                     *
 * Project: C++ Go Stop                                     *
 * Class: OPL Spring 20                                     *
 * Date: 02/17/2020                                         *
 ************************************************************
*/

#include "Game.h"
#include <string>
#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

/**********************************************************************
 * Function Name: GAME - Default Constructor
 * Purpose: To construct the game object
 * Parameters: None
 * Assistance Received: None
 **********************************************************************/
GAME::GAME()
{
}

/**********************************************************************
 * Function Name: startNewOrLoadGame
 * Purpose: To ask the user to start a new game or load a previous one
 * Parameters:
 *                  None
 * Return Value:
 *                  integer value that is the user's choice
 * Local Variables: 
 *                  newOrLoad, holds the user's choice to return
 *                  
 * Assistance Received: None
 **********************************************************************/
int GAME::startNewOrLoadGame()
{
    string newOrLoad;
    cout << "\n\tWelcome To Go Stop Card Game\n";

    do
    {
        cout << "\tDo you want to load a game? (y/n) ";
        getline(cin, newOrLoad);
    } while (newOrLoad != "y" && newOrLoad != "n");

    if (newOrLoad == "y")
    {
        return 2;
    }
    else
    {
        cout << "\tStarting New Game\n";
        return 1;
    }
}

/**********************************************************************
 * Function Name: startGame
 * Purpose: To start the Go Stop and continue playing until the user wants to exit 
 * Parameters:
 *                  None
 * Return Value:
 *                  newGameOrLoadExistingGam, int value that holds users choice
 *                  load game of play new
 *                  humanPlayer, object of player class representing human
 *                  computerPlayer, object of player class representing computer
 *                  currentRound, holds the round number to pass to round object
 *                  nextPlayerTurn, int value that holds whose turn it is to play 
 *                  roundObj, an object of round class to start the round
 *                  loadSerializerObj, an object of serializer class to load data from a file
 *                  and pass it to round object to resume playing the round
 *                  newOrExit, holds user input on whether to play another round or exit
 * 
 * Local Variables: 
 *                  newOrLoad, holds the user's choice to return
 * Algorithm:       
 *                  Starts the game by creating a new round object or loading a previous state
 *                  from a file and creating a round object. At the end of each round asks users
 *                  to play another round or not. If yes, continues with another new round else
 *                  displays the winner and exits the game gracefully
 *                  
 * Assistance Received: None
 **********************************************************************/
void GAME::startGame()
{

    //Ask the user if he wants to start a new game or load an existing game
    int newGameOrLoadExistingGame = startNewOrLoadGame();

    //create player objects and pass it to  round object
    PLAYER *humanPlayer = new HUMAN("Human");
    PLAYER *computerPlayer = new COMPUTER("Computer");

    //round is first if it is a new game
    int currentRound = 0;

    //when a round is complete ask user here if he wants to play another round. If he does
    //then create new round and continue rounds until user wants to exit the game
    int newOrExit;

    //holds the next player whose turn is to play next
    //initialized to -1 which is checked in round
    //if -1 determine first player function is executed in Round class object which determines the first player.
    //This happens the first time round object is created
    //for every other round index of winner of the last round is passed as the next player turn.
    //if draw -1 is passed
    int nextPlayerTurn = -1;

    //do while loops that keeps the rounds going
    do
    {
        if (newGameOrLoadExistingGame == 1)
        {
            //start new game
            //incrementing round value to pass which round it is
            currentRound++;

            //create a round object and start the round
            ROUND *roundObj = new ROUND(humanPlayer, computerPlayer, currentRound, nextPlayerTurn);

            //get the winner of the round and set it to nextPlayerTurn in case the plyaer wants to play another round
            nextPlayerTurn = roundObj->getRoundWinnerIndex();
        }
        else
        {
            //load existing one
            //create a serializer object and load the file info to the serializer object
            SERIALIZER *loadSerializerObj = new SERIALIZER();
            loadSerializerObj->readFromFile();

            //pass the info to human player, computer player, and create a round object with that
            //for the layout that you get from the file make sure you change the vector of cards of layout
            //to vector of vectors of cards on layout to match with the datatype of the layout used in the program
            vector<vector<Card *> > tempLayout;

            for (Card *i : loadSerializerObj->getRoundCardsOnLayout())
            {
                vector<Card *> tempInnerVector;
                tempInnerVector.push_back(i);

                tempLayout.push_back(tempInnerVector);
            }
            //set info to computer obj
            computerPlayer->setCardOnCapturePile(loadSerializerObj->getComputerCapturePile());
            computerPlayer->setCardsOnHand(loadSerializerObj->getComputerHandCards());
            computerPlayer->setTotalScore(loadSerializerObj->getComputerScore());

            //set info to human obj
            humanPlayer->setCardOnCapturePile(loadSerializerObj->getHumanCapturePile());
            humanPlayer->setCardsOnHand(loadSerializerObj->getHumanHandCards());
            humanPlayer->setTotalScore(loadSerializerObj->getHumanScore());

            //get the next player
            string nextPlayerToPass = loadSerializerObj->getNextPlayer();
            int nextPlayerIndexToPass;

            //get the next player to play
            if (nextPlayerToPass == "Human")
            {
                nextPlayerIndexToPass = 1;
            }
            else
            {
                nextPlayerIndexToPass = 2;
            }

            //In round class create a special constructor to load values from the serializer object and start the round
            //by calling that special constructor
            ROUND *roundObj = new ROUND(humanPlayer, computerPlayer, loadSerializerObj->getRoundNumber(),
                                        nextPlayerIndexToPass, tempLayout, loadSerializerObj->getRoundCardsOnStockPile(), nextPlayerToPass);

            //setting newGameOrLoadExisting game to 1 so another round is started (not loaded) if the user wants to play another round
            newGameOrLoadExistingGame = 1;

            //changing round number to the appropriate value after loading from the file
            currentRound = roundObj->getRoundNumber();

            //get the winner of the round and set it to nextPlayerTurn in case the plyaer wants to play another round
            nextPlayerTurn = roundObj->getRoundWinnerIndex();

        } //end of if else statement

        //user decision to play another round or not. if 1 wants to play game if 2 wants to quit
        newOrExit = beginAnotherRound();

        if (newOrExit == 1)
        {
            //if user wants to play another round
            //empty the player objects because we are using the same player objects to play next round so need to empty
            //all the variables before beginning a new round;
            humanPlayer->emptyCardsOnCapturePile();
            humanPlayer->emptyCardsOnHand();
            computerPlayer->emptyCardsOnCapturePile();
            computerPlayer->emptyCardsOnHand();
        }
        else
        {
            //if user does not want to play another round
            //display who the winner is by comparing the score when user wants to exit the game
            displayGameResult(humanPlayer->getTotalScore(), computerPlayer->getTotalScore());
        }

    } while (newOrExit == 1); //end of while statement that keeps the round in loop unless user wants to exit from the game

} //end of startgame() function

/**********************************************************************
 * Function Name: beginAnotherRound
 * Purpose: To ask user if he/she wants to play another round
 * Parameters:
 *                  None
 * Return Value:
 *                  integer, holds users choice 1 for New Round, 2 For Exit Game
 * Local Variables: 
 *                  newOrExit, holds user choice
 * Algorithm:   
 *                  None    
 * Assistance Received: None
 **********************************************************************/
int GAME::beginAnotherRound()
{

    int newOrExit;
    //ask whether user wants to play another round or not
    do
    {
        cout << "\n\nWould you like to begin another round or quit the game?\n";
        cout << "Enter 1 for New Round, 2 for Exiting the Game: ";
        cin >> newOrExit;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (!(newOrExit == 1 || newOrExit == 2));

    return newOrExit;
}

/**********************************************************************
 * Function Name: displayGameResult
 * Purpose: To display who is the winner of the game
 * Parameters:
 *                  humanFinalScore, final score of the human player
 *                  computerFinalScore, final score of the computer player
 * Return Value:
 *                  None
 * Local Variables: 
 *                  None    
 * Assistance Received: None
 **********************************************************************/
void GAME::displayGameResult(int humanFinalScore, int computerFinalScore)
{
    //int humanFinalScore = humanPlayer->getTotalScore();
    cout << "\nHuman Total Score: " << humanFinalScore;
    //int computerFinalScore = computerPlayer->getTotalScore();
    cout << "\nComputer Total Score: " << computerFinalScore << endl;

    if (humanFinalScore > computerFinalScore)
    {
        cout << "Congratulations Human! You won!";
    }
    else if (computerFinalScore > humanFinalScore)
    {
        cout << "Congratulations Machine! You won!";
    }
    else
    {
        cout << "Its a draw! ";
    }
    cout << "\n************** Thank you! Program is Exiting!! ****************\n";
}

/**********************************************************************
 * Function Name: main
 * Purpose: To provide a starting point for the program to execute and begin the game
 * Parameters:
 *                  None
 * Return Value:
 *                  integer value returns 0
 * Local Variables: 
 *                  gameObj, an object of game class created to begin the game
 *                  by calling the startGame function
 * Algorithm:   
 *                  None    
 * Assistance Received: None
 **********************************************************************/
int main()
{

    //Print the welcome message
    GAME *gameObj = new GAME();
    gameObj->startGame();

    return 0;

} //end of main() function
