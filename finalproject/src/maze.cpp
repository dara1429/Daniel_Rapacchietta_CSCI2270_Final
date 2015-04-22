#include "maze.h"
#include <vector>
#include <string>
using namespace std;
maze::maze()
{
    //Initializes class maze.
}

maze::~maze()
{
    //destructor.
}

void maze::createMaze(vector<string> rooms, int connections[][])
{
    //Creates the initial maze.
    //Creates variables to send to the add Vertex/Edge functions.
    string startingRoom;
    string connectedRoom;
    int counter = 0;
    int risk = 0;

    //Creates Vertexes
    for(int i = 0; i < rooms.size(); i++)
    {
        addVertex(rooms[i]);
    }

    //Creates Edges.
    while(counter < rooms.size())
    {
        startingRoom = rooms[counter];
        for(int i = 0; i < rooms.size(); i++)
        {
            connectedRoom = rooms[i];
            risk = connections[counter][i];
            if(risk != -1 and risk != 0)
            {
                addEdge(startingRoom,connectedRoom,risk);
            }
        }
        counter++;
    }
    //Assign ID's
    int id = 1;
    for(int i = 0; i < vertices.size(); i++)
    {
        vertices[i].ID = id;
        id++;
    }

}

