//Main driver
//Daniel Rapacchietta
//Final Project 2270.
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "maze.h"
#include "player.h"
using namespace std;

int main(int argc, char* argv[])
{
    string filename = argv[1];
    ifstream infile;
    infile.open(filename.c_str());

    //Creates the vector to hold room names.
    vector<string> rooms;
    //Counter to find the number of rooms in the text file.
    int roomsCounter = 0;
    //Error checking bool.
    bool error;
    vector< vector<int> > connections;
    //Grabs the first line of the text file (room names) and adds them into a vector.
    if(infile.good())
    {
        string line;
        string line2;
        //Counter so we can skip the first word of the file.
        int counter = 0;

        getline(infile,line);
        istringstream ss(line);
        while(getline(ss, line2, ','))
        {
            if(counter > 0)
            {
                roomsCounter++;
                rooms.push_back(line2);
            }
            counter = 1;
        }

            for(int i = 0; i < roomsCounter; i++)
            {
                vector <int> weight;
                connections.push_back(weight);
                for(int j = 0; j < roomsCounter; j++)
                {
                    connections.at(i).push_back(0);
                }
            }
            // Grabs the weights(risk) of each room and adds them to the connection vector.
            int risk;
            int one = 0;
            int two = 0;
            while(getline(infile,line))
            {
                istringstream ss(line);
                two = 0;
                while(getline(ss,line2, ','))
                {
                    //This skips the room name in each line of the file so we only
                    //Grab the weight (risk).
                    if(stringstream(line2) >> risk)
                    {
                        connections.at(one).at(two) = risk;
                        two++;
                    }
                }
                one++;
            }
    }
    infile.close();

    //Initializes the maze and creates the graph. If the maze is invalid, returns true;
    maze m;
    error = m.createMaze(rooms,connections);

    //If error is true. Quit program.
    if(error == true)
    {
        return 0;
    }

    //Initializes the player.
    player p;

    cout << "Welcome!" << endl;
    //Menu
    int command = 0;
    while(command != 9)
    {
        cout << endl;
        cout << "//////Game Menu//////" << endl;
        cout << "1. Play Game" << endl;
        cout << "2. Choose difficulty" << endl;
        cout << "3. Game Rules/Help" << endl;
        cout << "/////Options Menu//////" << endl;
        cout << "4. Add room" << endl;
        cout << "5. Add door/key" << endl;
        cout << "6. Find shortest path" << endl;
        cout << "7. Find path with the least risk" << endl;
        cout << "8. Print entire maze" << endl;
        cout << "9. Quit" << endl;

        cin >> command;
        if(command == 1)
        {
            vector<vertex> maze;
            maze = m.getVertices();
            p.game(maze);
            return 0;
        }
        if(command == 2)
        {
            p.setDifficulty();
        }
        if(command == 3)
        {
            p.gameHelp();
        }
        if(command == 4)
        {
            m.addRoom();
        }
        if(command == 5)
        {
            m.addDoorAndKey();
        }
        if(command == 6)
        {
            m.findShortestPath();
        }
        if(command == 7)
        {
            m.findSafestPath();
        }
        if(command == 8)
        {
            m.printRooms();
        }
    }
    cout << "Thanks for playing!" << endl;
    return 0;
}
