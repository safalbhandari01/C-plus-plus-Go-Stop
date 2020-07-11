/*
 ************************************************************
 * Name: Safal Bhandari                                     *
 * Project: C++ Go Stop                                     *
 * Class: OPL Spring 20                                     *
 * Date: 02/17/2020                                         *
 ************************************************************
*/
#include "Card.h"

/**********************************************************************
 * Function Name: Cards - Default Constructor
 * Purpose: To construct the cards object
 * Parameters: None
 * Assistance Received: None
 **********************************************************************/
Card::Card()
{
}

/**********************************************************************
 * Function Name: Cards - Overloading Constructor
 * Purpose: To construct the cards object
 * Parameters:
 *              face, a string value that holds the
 *              face of card.
 *
 *              suite, a string value that holds the
 *              suite of card
 * Assistance Received: None
 **********************************************************************/
Card::Card(string face, string suit)
{
    this->face = face;
    this->suit = suit;
}

/**********************************************************************
 * Function Name: Cards - Destructor 
 * Purpose: To destruct the created objects
 * Parameters: None
 * Assistance Received: None
 **********************************************************************/
Card::~Card()
{
}

/**********************************************************************
* Function Name: getFace
* Purpose: To return the face value of the card
* Parameters: None
* Return Value: string 
* Local Variables: None
* Assistance Received: None
**********************************************************************/
string Card::getFace()
{
    return this->face;
}

/**********************************************************************
* Function Name: setFace
* Purpose: To set the face value of the card
* Parameters:
*               face, string value to set the face value of card to
* Return Value: None 
* Local Variables: None
* Assistance Received: None
**********************************************************************/
void Card::setFace(string face)
{
    this->face = face;
}

/**********************************************************************
* Function Name: getSuit
* Purpose: To return the suit value of the card
* Parameters: None
* Return Value: string 
* Local Variables: None
* Assistance Received: None
**********************************************************************/
string Card::getSuit()
{
    return this->suit;
}

/**********************************************************************
* Function Name: setFace
* Purpose: To set the suit value of the card
* Parameters:
*               suit, string value to set the suit value of card to
* Return Value: None 
* Local Variables: None
* Assistance Received: None
**********************************************************************/
void Card::setSuit(string suit)
{
    this->suit = suit;
}

/**********************************************************************
* Function Name: getFaceAsInteger
* Purpose:       To get the face value of card as an integer value
* Parameters:
*                None
* Return Value:  integer value of the face value of card 
* Local Variables: None
* Assistance Received: None
**********************************************************************/
int Card::getFaceAsInteger()
{
    if (this->face == "X" || this->face == "x")
    {
        return 10;
    }
    else if (this->face == "J" || this->face == "j")
    {
        return 11;
    }
    else if (this->face == "Q" || this->face == "q")
    {
        return 12;
    }
    else if (this->face == "K" || this->face == "k")
    {
        return 13;
    }
    else if (this->face == "A" || this->face == "a")
    {
        return 1;
    }
    else
    {
        return stoi(this->face);
    }
}