#include "player.h"
#include "maze.h"
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

void player::gameStart(vector<vertex> maze)
{
    //Holds the ID of the exit.
    int winGame;
    //Holds player command.
    int command;
    //Holds the number rooms (options) to go to.
    int choices = 0;
    //Sets player in the entrance room.
    for(int i = 0; i < maze.size(); i++)
    {
        if(maze[i].name == "entrance" or maze[i].name == "Entrance")
        {
            currentRoom = &maze[i];
        }
        if(maze[i].name == "exit" or maze[i].name == "Exit")
        {
            winGame = maze[i].ID;
        }
    }

    //Game loop for traversing through the maze.
    cout << "You have fallen into a maze. Try and find your way out. Good luck!" << endl;
    while(currentRoom->ID != winGame)
    {
        command = 0;
        while(command == 0 or command > choices)
        {
            cout << "////GAME////" << endl;
            cout << "Lives remaining : " << lives << endl;
            cout << "Keys in inventory : " << keys << endl;
            cout << "Choose a path" << endl;
            gameShowChoices();
            cin >> command;
        }
    }
}

void player::gameShowChoices()
{
    for(int i = 0; i < currentRoom->adj.size(); i++)
    {
        //WIP.
    }
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

void player::setLives(int numLives)
{
    lives = numLives;
}

void player::setKeys(int numKeys)
{
    keys = numKeys;
}


