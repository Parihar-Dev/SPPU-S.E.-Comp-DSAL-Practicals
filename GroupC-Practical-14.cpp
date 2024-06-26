/*
There are flight paths between cities. If there is a flight path between city A and city B then there is an edge between the cities.
The cost of the edge can be the time that flight takes to reach city B from A, or the amount of fuel used for the journey. Represent this as
a graph. The node can be represented by airport name or name of the city. Use adjacency list representation of the graph or use adjacency
matrix representation of the graph.
Check whether the graph is connected or not. Justify the storage representation used.
*/

#include<iostream>
#include<queue>
using namespace std;

int adj_matrix[20][20] = {0,0};
int visited[20] = {0};

void DFS(int s, int n, string arr[])
{
    visited[s] = 1;
    cout<<arr[s]<<" ";
    for (int i = 0; i < n; i++)
    {
        if (adj_matrix[s][i] && !visited[i])
            DFS(i,n,arr);
    }
}

void BFS(int s, int n, string arr[])
{
    bool visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = false;
    int v;
    queue<int>bfsq;
    bfsq.push(s);
    visited[s] = true;
    while(!bfsq.empty())
    {
        v = bfsq.front();
        bfsq.pop();
        cout<<arr[v]<<" ";
        for (int i = 0; i < n; i++)
        {
            if (adj_matrix[v][i] != 0 && !visited[i])
            {
                bfsq.push(i);
                visited[i] = true;
            }
        }
    }
}


int main()
{
    int n,u;
    cout<<"Enter no. of cities : ";
    cin >> n;
    string cities[n];

    for (int i = 0; i < n; i++)
    {
        cout<<"Enter city #"<<i+1<<"(Airport Code): ";
        cin>>cities[i];
    }

    cout<<"\nYour cities are: "<<endl;
    for (int i = 0; i < n; i++)
        cout<<"city#"<<i+1<<" : "<<cities[i]<<endl;
        
    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            cout<<"Enter distance between "<<cities[i]<<" and "<<cities[j]<<" : ";
            cin>>adj_matrix[i][j];
            adj_matrix[j][i] = adj_matrix[i][j];
        }
    }
    cout<<endl;

    for (int i = 0; i<n; i++)
        cout<<"\t"<<cities[i]<<"\t";
    for (int i = 0; i<n; i++)
    {
        cout<<"\n"<<cities[i];
        for (int j = 0; j < n ; j++)
            cout<<"\t"<<adj_matrix[i][j]<<"\t";
        cout<<endl;
    }

    cout<<"Enter starting vertex : ";
    cin>>u;
    cout<<"DFS: ";
    DFS(u,n,cities);
    cout<<endl;
    cout<<"BFS:";
    BFS(u,n,cities);
    return 0;
}
