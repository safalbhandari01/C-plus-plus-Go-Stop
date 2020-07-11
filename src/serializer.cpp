/*
 ************************************************************
 * Name: Safal Bhandari                                     *
 * Project: C++ Go Stop                                     *
 * Class: OPL Spring 20                                     *
 * Date: 02/17/2020                                         *
 ************************************************************
*/

#include "serializer.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

/**********************************************************************
 * Function Name: SERIALIZER - Default Constructor
 * Purpose: To construct the serializer object
 * Parameters: None
 * Assistance Received: None
 **********************************************************************/
SERIALIZER::SERIALIZER()
{
}

/**********************************************************************
* Function Name: readFromFile
* Purpose: To read and load data from a file to serializer object
* Parameters:
*               face, string value to set the face value of card to
* Return Value: None 
* Local Variables: 
*                   readingFailed, holds true if failed to read file
*                   else holds false
*                   readComputerScore, holds true if computer score
*                    is read already else false
*                   readComputerHand, holds true if computer hand is 
*                   read already else false
*                   readComputerCapturePile true if computer capture 
*                   pile is read already else false
* Algorithm:
*                   take each line from the file one at a time, 
*                   look for key word in that line using find function
*                   if found set the value to appropriate member variable of the class
* Assistance Received: None
**********************************************************************/
void SERIALIZER::readFromFile()
{

    //holds if reading is successful or not
    bool readingFailed = false;

    //holds true if we already read the computer score, hand, and capture file
    //setting it to false because nothing is read yet
    bool readComputerScore = false;
    bool readComputerHand = false;
    bool readComputerCapturePile = false;

    //do while loop until we get all the valid input from the read file
    do
    {
        //get the name of the file from the user
        string fileName;
        cout << "\tPlease enter the file you want to load the data from: ";
        cin >> fileName;

        //read the file
        ifstream inFile(fileName);

        if (inFile.fail())
        {
            //there is an error reading a file
            cout << "\tThere is an error reading the file or the File does not exist\n";
            readingFailed = true;
        }
        else
        {
            //read the file here
            //going through each line in the file and extracting information
            for (string eachLine; getline(inFile, eachLine);)
            {
                //Extracts round number if the line contains round infot
                if (eachLine.find("Round") != string::npos)
                {

                    string roundNumberString = "";
                    for (int i = 7; i < eachLine.size(); i++)
                    {
                        roundNumberString = roundNumberString + eachLine.at(i);
                    }
                    this->roundNumber = stoi(roundNumberString);
                }

                //Extracts the nextPlayer
                if (eachLine.find("Next") != string::npos)
                {
                    string nextPlayerTemp = "";

                    for (int i = 12; i < eachLine.size(); i++)
                    {
                        if (eachLine.at(i) != ' ')
                        {
                            nextPlayerTemp += eachLine.at(i);
                        }
                    }
                    this->nextPlayer = nextPlayerTemp;
                }

                //Extracts the layout from the file
                if (eachLine.find("Layout") != string::npos)
                {

                    //use iterator to traverse through the line
                    for (string::iterator it = eachLine.begin() + 8; it != eachLine.end(); ++it)
                    {
                        if (*it != ' ')
                        {
                            string face = string(1, *it);
                            string suit = string(1, *(++it));
                            //this->roundCardsOnLayout.insert(roundCardsOnLayout.begin(), new Card(face, suit));
                            this->roundCardsOnLayout.push_back(new Card(face, suit));
                        }
                    }
                }

                //Extracts the stock pile from the file
                if (eachLine.find("Stock") != string::npos)
                {

                    for (string::iterator it = eachLine.begin() + 12; it != eachLine.end(); ++it)
                    {
                        if (*it != ' ')
                        {
                            string face = string(1, *it);
                            string suit = string(1, *(++it));
                            this->roundCardsOnStockPile.insert(roundCardsOnStockPile.begin(), new Card(face, suit));
                        }
                    }
                }

                //Extracts Computer and Human Information
                //Extracts computerScore and HumanScore
                if (eachLine.find("Score") != string::npos)
                {

                    if (readComputerScore == false)
                    {

                        string computerScore = "";
                        for (int i = 10; i < eachLine.size(); i++)
                        {
                            if (eachLine.at(i) != ' ')
                            {
                                computerScore += eachLine.at(i);
                            }
                        }
                        this->computerScore = stoi(computerScore);

                        readComputerScore = true;
                    }
                    else
                    {

                        string humanScore = "";
                        for (int i = 10; i < eachLine.size(); i++)
                        {
                            if (eachLine.at(i) != ' ')
                            {
                                humanScore += eachLine.at(i);
                            }
                        }

                        this->humanScore = stoi(humanScore);
                    }
                }

                //Extracts computerHand and HumanHand
                if (eachLine.find("Hand") != string::npos)
                {

                    if (readComputerHand == false)
                    {

                        //reading computer hand

                        for (string::iterator it = eachLine.begin() + 9; it != eachLine.end(); ++it)
                        {
                            if (*it != ' ')
                            {
                                string face = string(1, *it);
                                string suit = string(1, *(++it));

                                this->computerHandCards.push_back(new Card(face, suit));
                            }
                        }

                        readComputerHand = true;
                    }
                    else
                    {

                        //reading human hand
                        for (string::iterator it = eachLine.begin() + 9; it != eachLine.end(); ++it)
                        {
                            if (*it != ' ')
                            {
                                string face = string(1, *it);
                                string suit = string(1, *(++it));

                                this->humanHandCards.push_back(new Card(face, suit));
                            }
                        }
                    }
                }

                //Extracts computerCapture and HumanCapture
                if (eachLine.find("Capture") != string::npos)
                {

                    if (readComputerCapturePile == false)
                    {

                        //iterating without using iterator
                        for (int i = 17; i < eachLine.size(); i++)
                        {
                            if (eachLine.at(i) != ' ')
                            {
                                string face = string(1, eachLine.at(i));
                                string suit = string(1, eachLine.at(++i));
                                this->computerCapturePile.push_back(new Card(face, suit));
                            }
                        }

                        readComputerCapturePile = true;
                    }
                    else
                    {

                        for (int i = 17; i < eachLine.size(); i++)
                        {
                            if (eachLine.at(i) != ' ')
                            {
                                string face = string(1, eachLine.at(i));
                                string suit = string(1, eachLine.at(++i));
                                this->humanCapturePile.push_back(new Card(face, suit));
                            }
                        }
                    }
                }
            }
            readingFailed = false;
        }

    } while (readingFailed == true);

    cin.ignore();

} //end of readFromFile function

/**********************************************************************
* Function Name: saveToFile
* Purpose: save the state of a program to a file
* Parameters: 
*                   fileToSaveIn, name of file to save it in
*                   nextPlayer, next player's turn
*                   roundNumber, current round number 
*                   computerScore, score of computer player 
*                   computerHand,  computer hand of cards vector
*                   computerCapturePile, computer capture pile cards vector
*                   humanScore, score of human player
*                   humanHand, human hand of cards vector
*                   humanCapturePile, human capture pile cards vector
*                   cardsOnLayout, vector of pointer to cards on layout 
*                   cardsOnStockPile, vector of pointer to cards on stockpile
* Local Variables:
*                   saveFile, name of the file to save the state of program
* Algorithm:
*                   Written to the file according to the serialization
*                   format 
* Assistance Received: None
**********************************************************************/
void SERIALIZER::saveToFile(string fileToSaveIn, string nextPlayer, int roundNumber, int computerScore, vector<Card *> computerHand, vector<Card *> computerCapturePile,
                            int humanScore, vector<Card *> humanHand, vector<Card *> humanCapturePile, vector<Card *> cardsOnLayout, vector<Card *> cardsOnStockPile)
{

    ofstream saveFile;

    //opening the file to save in
    saveFile.open(fileToSaveIn);

    //save round information
    saveFile << "Round: " << roundNumber << "\n";
    saveFile << "\n";

    //save computer information
    saveFile << "Computer: \n";
    saveFile << "   Score: " << computerScore << "\n";
    saveFile << "   Hand: ";
    for (int i = 0; i < computerHand.size(); i++)
    {
        saveFile << computerHand.at(i)->getFace() << computerHand.at(i)->getSuit() << " ";
    }
    saveFile << "\n";
    saveFile << "   Capture Pile: ";
    for (int i = 0; i < computerCapturePile.size(); i++)
    {
        saveFile << computerCapturePile.at(i)->getFace() << computerCapturePile.at(i)->getSuit() << " ";
    }
    saveFile << "\n";

    //skipping a line
    saveFile << "\n";

    //save human information
    saveFile << "Human: \n";
    saveFile << "   Score: " << humanScore << "\n";
    saveFile << "   Hand: ";
    for (int i = 0; i < humanHand.size(); i++)
    {
        saveFile << humanHand.at(i)->getFace() << humanHand.at(i)->getSuit() << " ";
    }
    saveFile << "\n";
    saveFile << "   Capture Pile: ";
    for (int i = 0; i < humanCapturePile.size(); i++)
    {
        saveFile << humanCapturePile.at(i)->getFace() << humanCapturePile.at(i)->getSuit() << " ";
    }
    saveFile << "\n";

    //skipping a line
    saveFile << "\n";

    //save layout information
    saveFile << "Layout: ";
    for (int i = 0; i < cardsOnLayout.size(); i++)
    {
        saveFile << cardsOnLayout.at(i)->getFace() << cardsOnLayout.at(i)->getSuit() << " ";
    }
    saveFile << "\n";

    //skipping a line
    saveFile << "\n";

    //save stock pile information
    saveFile << "Stock Pile: ";
    for (int i = cardsOnStockPile.size() - 1; i >= 0; i--)
    {
        saveFile << cardsOnStockPile.at(i)->getFace() << cardsOnStockPile.at(i)->getSuit() << " ";
    }
    saveFile << "\n";

    //skipping a line
    saveFile << "\n";

    //save next player information
    saveFile << "Next Player: " << nextPlayer << "\n";

} //end of saveToFile function
