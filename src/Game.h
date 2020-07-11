/*
 ************************************************************
 * Name: Safal Bhandari                                     *
 * Project: C++ Go Stop                                     *
 * Class: OPL Spring 20                                     *
 * Date: 02/17/2020                                         *
 ************************************************************
*/
#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include "Round.cpp"

using namespace std;

class GAME
{

public:
    GAME();
    int startNewOrLoadGame();
    void startGame();
    int beginAnotherRound();
    void displayGameResult(int humanFinalScore, int computerFinalScore);

private:
};
#endif