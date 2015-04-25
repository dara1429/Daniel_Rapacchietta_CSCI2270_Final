#include "player.h"
#include <string>
#include <iostream>
using namespace std;
player::player()
{
    //Constructor
}

player::~player()
{
    //Destructor
}

void player::gameStart()
{

}

void player::setDifficulty()
{
    int command = 0;
    cout << "Please select your difficulty" << endl;
    cout << "1. Easy (5 Lives, 1 Key to start)" << endl;
    cout << "2. Normal (3 Lives, 0 Keys to start)" << endl;
    cout << "3. Hard (1 Life, 0 Keys to start)" << endl;
    while(command != 1 and command != 2 and command != 3)
    {
    cin >> command;
    if(command == 1)
    {
        cout << "Easy difficulty selected." << endl;
        int numLives = 5;
        int numKeys = 1;
        setLives(numLives);
        setKeys(numKeys);
    }
    else if(command == 2)
    {
        cout << "Normal difficulty selected." << endl;
        int numLives = 3;
        setLives(numLives);
    }
    else if(command == 3)
    {
        cout << "Hard difficulty selected. Good luck!" << endl;
        int numLives = 1;
        setLives(numLives);
    }
    else
    {
        cout << "Invalid input. Please try again." << endl;
    }
    }
}

int player::getLives()
{
    return lives;
}

int player::getKeys()
{
    return keys;
}

int player::getPosition()
{
    return position;
}

void player::setLives(int numLives)
{
    lives = numLives;
}

void player::setKeys(int numKeys)
{
    keys = numKeys;
}

void player::setPosition(int ID)
{

}
