#include "player.h"
#include "maze.h"
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;
player::player()
{
    //Constructor
}

player::~player()
{
    //Destructor
}

void player::game(vector<vertex> maze)
{
    //Holds the ID of the exit.
    int winGame;
    //Holds player command.
    int command;
    //Holds the number rooms (options) to go to.
    int choices;
    //Determines if the player made it through to the next room.
    bool success = false;
    //Flag that prevents the player from going to a locked room without a key.
    bool error = false;
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
    cout << endl;
    cout << "You have fallen into a maze. Try and find your way out. Good luck!" << endl;
    cout << endl;
    while(currentRoom->ID != winGame and getLives() != 0)
    {
        command = 0;
        cout << "////GAME////" << endl;
        cout << "Current room : " << currentRoom->name << endl;
        cout << "Lives remaining : " << getLives() << endl;
        cout << "Keys in inventory : " << getKeys() << endl;
        cout << "Choose a path " << endl;
        cout << endl;
        while(command <= 0 or command > choices)
        {
            error = false;
            choices = 0;
            choices = gameShowChoices(choices);
            cin >> command;
        }
        if(currentOptions[command].door == true)
        {
            if(keys == 0)
            {
                cout << endl;
                cout << "You cant go there without a key." << endl;
                cout << endl;
                error = true;
            }
            else
            {
                success = gameRisk(currentRisks[command]);
                if(success == true)
                {
                    setKeys(--keys);
                }
            }
        }
        else
        {
            success = gameRisk(currentRisks[command]);
        }
        if(success == true and error == false)
        {
            cout << endl;
            cout << "You made it through to the next room safely!" << endl;
            cout << endl;
            for(int i = 0; i < maze.size(); i++)
            {
                //Sets door to false if it was true
                for(int j = 0; j < currentRoom->adj.size(); j++)
                {
                    if(currentOptions[command].name == currentRoom->adj[j].v->name)
                    {
                        currentRoom->adj[j].v->door = false;
                    }
                }
                //Changes the current room.
                if(currentOptions[command].name == maze[i].name)
                {
                    if(maze[i].key == true)
                    {
                        cout << endl;
                        cout << "You found a key !" << endl;
                        cout << endl;
                        setKeys(++keys);
                        maze[i].key = false;
                    }
                    currentRoom = &maze[i];
                }
            }
        }
        else if(success == false and error == false)
        {
            cout << endl;
            cout << "You fell into a trap! Lose one life." << endl;
            cout << "Try again!" << endl;
            setLives(--lives);
            cout << endl;
        }
    }
    if(lives == 0)
    {
        cout << "You lost all of your lives. Game Over!" << endl;
        return;
    }
    else
    {
        cout << "You made it out of the maze. Congratulations!" << endl;
        return;
    }

}

int player::gameShowChoices(int choices)
{
    vertex null;
    currentOptions.clear();
    currentOptions.push_back(null);
    currentRisks.clear();
    currentRisks.push_back(0);
    for(int i = 0; i < currentRoom->adj.size(); i++)
    {
        if(currentRoom->adj[i].v->door == true)
        {
            choices++;
            cout << "[" << choices << "]->" << currentRoom->adj[i].v->name << " (LOCKED->Key required)" <<  " - Risk: " << currentRoom->adj[i].risk << "%" << endl;
            currentOptions.push_back(*currentRoom->adj[i].v);
            currentRisks.push_back(currentRoom->adj[i].risk);
        }
        else
        {
            choices++;
            cout << "[" << choices << "]->" << currentRoom->adj[i].v->name << " - Risk: " << currentRoom->adj[i].risk << "%" << endl;
            currentOptions.push_back(*currentRoom->adj[i].v);
            currentRisks.push_back(currentRoom->adj[i].risk);
        }
    }
    return choices;
}

bool player::gameRisk(int risk)
{
    int finalNumber;
    finalNumber = rand() % 100 + 1;
    cout << endl;
    cout << "You rolled : " << finalNumber << endl;
    cout << endl;
    if(finalNumber <= risk)
    {
        return false;
    }
    else
    {
        return true;
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

void player::gameHelp()
{
    cout << "Game Help" << endl;
    cout << "//////////" << endl;
    cout << "Objective : The objective of the game is to get from the entrance room to the exit room without loosing all of your lives." << endl;
    cout << endl;
    cout << "Lives : " << "Your current number of lives. You will lose one if you fall into a trap." << endl;
    cout << endl;
    cout << "Keys : " << "These are used to unlock doors that you put in your maze." << endl;
    cout << endl;
    cout << "Risk : " << "This is the percent chance of you falling into a trap when traversing through your maze." << endl;
    cout << endl;
    cout << "Risk cont. : " << "Weather you fall into a trap depends on a pseudo random roll. A random number is generated between 1 and 100." << endl;
    cout << "If the number is equal to or lower than the risk %. You will fall into the trap and loose one life" << endl;
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


