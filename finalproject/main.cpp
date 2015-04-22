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
    //Counter to initialize the size of the 2D array.
    int roomsCounter = 0;
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
            //Initializes 2D vector.
            vector< vector<int> > connections;
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
                    //Grab the weight (edges).
                    if(stringstream(line2) >> risk)
                    {
                        connections.at(one).at(two) = risk;
                        two++;
                    }
                }
                one++;
            }
            //Initializes the maze.
            maze m;
            m.createMaze(rooms,connections);
    }

    //Closes file.
    infile.close();

    //Menu
    int command = 0;
    while(command != 99)
    {
        cout << "/////Menu//////" << endl;
        cout << "1. Test" << endl;
        cout << "99. Quit" << endl;
        cin >> command;
    }
    cout << "Thanks for playing!" << endl;
    return 0;
}
