#include "maze.h"
#include <vector>
#include <string>
#include <queue>
#include <climits>
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

void maze::findSafestPath()
{
    //Holds path to shortest route.
    vector<vertex> solved;

    //Used for calculating average risk.
    int counter = -1;

    vertex *room1;
    vertex *room2;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == "Entrance" or vertices[i].name == "entrance")
        {
            room1 = &vertices[i];
            vertices[i].risk = 0;
            //Adds origin to solved.
            solved.push_back(vertices[i]);
        }
    }
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == "Exit" or vertices[i].name == "exit")
        {
            room2 = &vertices[i];
        }
    }

    //Previous room
    int previousSize = vertices.size();
    int previous[previousSize];
    //Keeps track of current distance and finds the minimum amount of risk from one room to another.
    int minDistance = 0;
    int distance = 0;
    vertex *minimumRoom;
    //Initializing all rooms.
    for(int i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
        vertices[i].risk = INT_MAX;
        previous[vertices[i].ID] = -1;
    }

    //Initialize first room so we don't check it.
    room1->visited = true;
    room1->risk = 0;

    //While loop to find the minimum weighted(riskiest) path.
    //Distance = risk.
    while(room2->visited == false)
    {
        minDistance = INT_MAX;
        for(int i = 0; i < solved.size(); i++)
        {
            for(int j = 0; j < solved[i].adj.size(); j++)
            {
                if(solved[i].adj[j].v->visited == false)
                {
                    distance = (solved[i].risk + solved[i].adj[j].risk);
                    if(distance < minDistance)
                    {
                        minDistance = distance;
                        minimumRoom = solved[i].adj[j].v;
                        solved[i].adj[j].v->risk = minDistance;
                        previous[minimumRoom->ID] = solved[i].ID;
                    }
                }
            }

        }
        //Update Solved.
        minimumRoom->visited = true;
        solved.push_back(*minimumRoom);
        //Checks to see if solved room was the exit.
        for(int k = 0; k < vertices.size(); k++)
        {
            if(room2->name == minimumRoom->name)
            {
                room2->visited = true;
            }
            if(minimumRoom->name == vertices[k].name)
            {
                vertices[k].visited = true;
            }
        }
    }
    //Traverses the previous pointers and puts them into a vector for printing.
    distance = minDistance;
    vector<vertex> printPath;
    int currentID = minimumRoom->ID;
    while(currentID != -1)
    {
        for(int i = 0; i < vertices.size(); i++)
        {
            if(currentID == vertices[i].ID)
            {
                printPath.push_back(vertices[i]);
                counter++;
            }

        }
        currentID = previous[currentID];
    }
    //Prints the safest path and average risk of traversing that path.
    double avgrisk = distance / counter;
    int i = 0;
    cout << "The safest path in the maze is :" << endl;
    while(!printPath.empty())
    {
        if(i != counter)
        {cout << printPath.back().name << "->";}
        else
        {
            cout << printPath.back().name;
        }
        printPath.pop_back();
        i++;
    }
    cout << endl;
    cout << "The average change of falling into a trap while taking this path is : " << avgrisk << "%" << endl;
    cout << endl;
}

void maze::findShortestPath()
{

}
