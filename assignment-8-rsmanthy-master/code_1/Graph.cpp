#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;


void Graph::addVertex(string name){
    //TODO
    bool found = false;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->name == name)
        {
            found = true;
        }
    }
    if(found == false)
    {
        vertex * v = new vertex;
        v->name = name;
        vertices.push_back(v);
    }
    else
    {
        cout << name << " found." << endl;
        return;
    }
}

void Graph::addEdge(string v1, string v2){
    //TODO
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->name == v1)
        {
            for(int j = 0; j < vertices.size(); j++)
            {
                if(vertices[j]->name == v2 && i != j)
                {
                    adjVertex av;
                    av.v = vertices[j];
                    vertices[i]->adj.push_back(av);
                    //another vertex for edge in other direction
                    adjVertex av2;
                    av2.v = vertices[i];
                    vertices[j]->adj.push_back(av2);
                }
            }
        }
    }
}

void Graph::displayEdges(){
    //TODO
    for(int i = 0; i < vertices.size(); i++)
    {
        //print verticies 
        cout << vertices[i]->name << " --> ";
        for(int f = 0; f < vertices[i]->adj.size(); f++)
        {
            cout << vertices[i]->adj[f].v->name << " ";
        }
        cout << endl;
    }
}

void Graph::breadthFirstTraverse(string sourceVertex){
    // Need to find the source vertex since we only have it's key 'src'
    // A pointer for source vertex
    vertex *vStart;

    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->name == sourceVertex )
        {
            vStart = vertices[i];
        }
    }

    vStart->visited = true;
     // Use the queue to keep track of visited vertices
    queue<vertex*> q;
    //oush the vertex 
    q.push(vStart);
    //itterator
    vertex *n;
    //cout statements 
    cout<< "Starting vertex (root): " << vStart->name << "-> ";
    // standard BFS 
    while(!q.empty())
    {

        n = q.front();
        q.pop();
        // go to all the adjacent vertices of n
        for( int x = 0; x < n->adj.size(); x++ )
        {  
            // If a adjacent has not been visited, then mark it visited and enqueue it
            if(n->adj[x].v->visited == false)
            {
                
                n->adj[x].v->visited = true;
                // Update the distance of the adjacent vertices along the way
                n->adj[x].v->distance = n->distance + 1;
                //need to do my pritning after the distace is updates 
                cout << n->adj[x].v->name <<"("<< n->adj[x].v->distance <<")"<< " ";
                //updating to current node
                n->adj[x].v->previous = n;
                //pushing 
                q.push(n->adj[x].v);
            }
        }
    }
    cout << endl << endl;
}

int Graph::findShortestPathBetweenBuildings(string source, string dest) {
    //TODO
    //use bfs and then use for loop to do the printing that you need to do 

    // Need to find the source vertex since we only have it's key 'src'
    // A pointer for source vertex
    vertex *vStart;
    vertex *vEnd;

    //findint the start 
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->name == source)
        {
            vStart = vertices[i];
        }
    }

    //finding the end
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->name == dest)
        {
            vEnd = vertices[i];
        }
    }

    vStart->visited = true;

    // Use the queue to keep track of visited vertices
    queue<vertex*> q;

    // Enqueue the source vertex
    q.push(vStart);

    //itterator
    vertex *n;

    // standard BFS
    while(!q.empty())
    {

        n = q.front();
        q.pop();

        // go to all the adjacent vertices of n
        for( int x = 0; x < n->adj.size(); x++ )
        {
            // If a adjacent has not been visited, then mark it visited and enqueue it
            if(n->adj[x].v->visited == false)
            {
                n->adj[x].v->visited = true;
                // Update the distance of the adjacent vertices along the way
                n->adj[x].v->distance = n->distance + 1;
                //updating to current node
                n->adj[x].v->previous = n;
                //pushing 
                q.push(n->adj[x].v);
            }
            // Stop when you reach the destination vertex and return the needful
            if(n == vEnd)
            {
               //use n because it is already at vEnd 
                while(n != vStart)
                {
                    cout << n->name << endl;
                    n = n->previous;
                }
                cout << vStart->name << endl;
                cout << "Shortest Path Distance: " << vEnd->distance << endl;
                return vEnd->distance;
            }
        }
    }
    return 0;
}

