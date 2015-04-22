#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "maze.h"
using namespace std;

int main(int argc, char* argv[])
{
    //Open text file containing maze.
    string filename = argv[1];
    ifstream infile;
    infile.open(filename.c_str());

    //Creates the vector to hold room names.
    vector<string> rooms;
    //Counter to initialize the size of the 2D vector.
    int roomsCounter = 0;
    //Error checking bool.
    bool error;
    //Initializes 2D vector.
    vector< vector<int> > connections;
    //Grabs the first line of the text file (room names) and adds them into a vector.
    if(infile.good())
    {
        //First line of the file.
        string line;
        //Each city from the first line of the file.
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
                    //This skips the city name in each line of the file so we only
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
    //Closes file.
    infile.close();

    //Initializes the maze.
    maze m;
    error = m.createMaze(rooms,connections);
    //If error is true. Quit program.
    if(error == true)
    {
        return 0;
    }
    cout << "Your maze is valid!" << endl;
    cout << "Welcome!" << endl;
    //Menu
    int command = 0;
    while(command != 7)
    {
        cout << "//////Game Menu//////" << endl;
        cout << "1. Play Game" << endl;
        cout << "2. Choose difficulty" << endl;
        cout << "/////Options Menu//////" << endl;
        cout << "3. Add room" << endl;
        cout << "4. Add door/key" << endl;
        cout << "5. Find shortest path" << endl;
        cout << "6. Find path with the least risk" << endl;
        cout << "7. Quit" << endl;

        cin >> command;
        if(command == 1)
        {
            //game.
        }
        if(command == 2)
        {
            //difficulty
        }
        if(command == 3)
        {
            //addroom
        }
        if(command == 4)
        {
            //adddoor/key
        }
        if(command == 5)
        {
            m.findShortestPath();
        }
        if(command == 6)
        {
            m.findSafestPath();
        }
    }
    cout << "Thanks for playing!" << endl;
    return 0;
}
