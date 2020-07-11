/*
 ************************************************************
 * Name: Safal Bhandari                                     *
 * Project: C++ Go Stop                                     *
 * Class: OPL Spring 20                                     *
 * Date: 02/17/2020                                         *
 ************************************************************
*/
#ifndef CARD_H
#define CARD_H
#include <string>

using namespace std;

class Card
{

public:
    Card();
    Card(string face, string suit);
    ~Card();

    string getFace();
    string getSuit();

    void setFace(string face);
    void setSuit(string suit);
    int getFaceAsInteger();

private:
    //face holds the face value of a card
    string face;
    //suit holds the suit value of a card
    string suit;
};
#endif
