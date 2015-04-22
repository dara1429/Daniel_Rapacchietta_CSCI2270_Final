#include "maze.h"
#include <vector>
#include <string>
#include <queue>
using namespace std;
maze::maze()
{
    //Initializes class maze.
}

maze::~maze()
{
    //destructor.
}

bool maze::createMaze(vector<string> rooms, vector< vector<int> > connections)
{
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
            if(risk != -1 and risk != -2)
            {
                addEdge(startingRoom,connectedRoom,risk);
            }
        }
        counter++;
    }
    //Assign room ID's
    int id = 1;
    for(int i = 0; i < vertices.size(); i++)
    {
        vertices[i].ID = id;
        id++;
    }

    //Assign mazeCheck ID's (for maze error checking)
    mazeErrorCheck();

    //Checks to see if graph is valid. (No disconnected rooms).
    bool error = false;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].mazeCheck != 1)
        {
            error = true;
            cout << "ERROR : ROOM -> " << vertices[i].name << " is not connected to the rest of your maze!" << endl;
            cout << "----------------------------------------------------------------" << endl;
            cout << "Please edit your maze.txt file and make sure " << vertices[i].name << " is connected to the rest of your maze" << endl;
        }
    }
    //Checks to see if any two rooms have different weights(risks) between them.
    int check = 0;
    int riskCheck = 0;
    for(int i = 0; i < vertices.size(); i++)
    {
        for(int j = 0; j < vertices[i].adj.size(); j++)
        {
            riskCheck = vertices[i].adj[j].risk;
            if(riskCheck > 50)
            {
                error = true;
                cout << vertices[i].adj[j].v->name << " has risk value greater than 50!" << endl;
                cout << "---------------------------------------------------------------" << endl;
                cout << "Please choose risk values lower than 50 (50%)" << endl;
            }
            check++;
        }
    }
    if(check % 2)
    {
        error = true;
        cout << "ERROR : One of your rooms contains a one way path!" << endl;
        cout << "Example : room1 has risk 50 to go room2 but room2 has -1 risk to go to room1" << endl;
        cout << "-----------------------------------------------------------------------" << endl;
        cout << "Please check your maze.txt file for -1's that you forgot to change" << endl;
    }
    return error;
}

void maze::addVertex(string n)
{
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        vertices.push_back(v);

    }
}

void maze::addEdge(string v1, string v2, int risk)
{

    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.risk = risk;
                    vertices[i].adj.push_back(av);
                    //another vertex for edge in other direction.
                    /*
                    adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = weight;
                    vertices[j].adj.push_back(av2);
                    */
                }
            }
        }
    }
}

void maze::mazeErrorCheck()
{
    int id = 1;
    string startingRoom;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].mazeCheck == -1)
        {
            startingRoom = vertices[i].name;
            mazeErrorCheckBFT(startingRoom,id);
            id++;
        }
    }
}

void maze::mazeErrorCheckBFT(string startingRoom, int id)
{
    //Initialize node
    vertex v;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == startingRoom)
        {
            v = vertices[i];
            //Mark city as visited.
            vertices[i].visited = true;
            vertices[i].mazeCheck = id;
        }
    }
    //Create queue for BFS
    queue<vertex> q;

    //Add starting city to queue.
    q.push(v);

    while(!q.empty())
    {
        v = q.front();
        q.pop();

        for(int i = 0;i < v.adj.size(); i++)
        {
            if(v.adj[i].v->visited == false)
            {
                v.adj[i].v->visited = true;
                v.adj[i].v->mazeCheck = id;
                q.push(*v.adj[i].v);
            }
        }
    }

}



