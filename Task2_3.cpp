#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

int** Creategraph(int **, int); //Создание графа
void BFSD(int **, int *, int, int);  //Обход в ширину
void DFS(int **, int *, int *, int, int);

int size;   //Размер графа


int main()
{
    int i, j, v, cnt;
    int **graph = NULL, *DIST = NULL, *dist = NULL, *visited = NULL;


    printf("\t# Graphs #\n\n");
    printf("Enter the number of graph vertices (positive integer): ");
    scanf("%d", &size);

    // Creating the graph
    graph = Creategraph(graph, size);
    DIST = (int *)(malloc(sizeof(int *) * size));  // Array for visited vertices
    dist = (int *)(malloc(sizeof(int *) * size));
    visited = (int *)(malloc(sizeof(int *) * size));

    // Printing the matrix
    for(i = 0; i < size; i++)
    {
        cnt = 0;
        DIST[i] = -1;
        dist[i] = DIST[i];
        visited[i] = 0;
        for(j = 0; j < size; j++)
        {
            printf("%d ", graph[i][j]);
            if(graph[i][j] == 1) cnt++;
        }
        printf("\n");
        if(cnt == 0) dist[i] = -2;
    }

    int num = size - 1;

    printf("Enter the number of start vertex (positive integer [0; %d]): ", num);
    scanf("%d", &v);

    // <---------- ! ---------->
    BFSD(graph, DIST, size, v);
    // <---------- ! ---------->
    printf("\n");
    for(i = 0; i < size; i++)
        printf("%d: %d\n", i, DIST[i]);

    printf("\n\n");

    printf("Enter the number of start vertex (positive integer [0; %d]): ", num);
    scanf("%d", &v);

    // <---------- ! ---------->
    DFS(graph, dist, visited, size, v);
    // <---------- ! ---------->
    printf("\n");

    for(i = 0; i < size; i++)
        printf("%d: %d\n", i, dist[i] + 1);


    delete[] visited;
    delete[] dist;
    delete[] graph;
    delete[] DIST;

    return 0;
}


int** Creategraph(int **graph, int size)
{
    srand(time(NULL));

    int i = 0, j = 0;

    // Memory allocation
    graph = (int **)(malloc(sizeof(int *) * size));
    for(i = 0; i < size; i++)
        graph[i] = (int *)(malloc(sizeof(int *) * size));

    // Filling the matrix
    for(i = 0; i < size; i++)
        for(j = i; j < size; j++)
        {
            graph[i][j] = rand() % 2;
            graph[j][i] = graph[i][j];
            if(i == j) graph[i][j] = 0;
            if(graph[i][j] == 1);
        }

    return graph;
}

void BFSD(int **graph, int *DIST, int size, int v)
{
    queue<int> q;
    q.push(v);
    DIST[v] = 0;

    while(!q.empty())
    {
        v = q.front();
        printf("%d ", v);
        q.pop();

        for(int i = 0; i < size; i++)
        {
            if((graph[v][i] == 1) && (DIST[i] == -1))
            {
                q.push(i);
                DIST[i] = DIST[v] + 1;
            }
        }
    }

}

void DFS(int **graph, int *DIST, int *visited, int size, int v)
{
    int i;
    visited[v] = 1;
    printf("%d ", v);

    for(i = 0; i < size; i++)
    {
        if((graph[v][i] == 1) && (visited[i] == 0))
        {
            DIST[i] = DIST[v] + 1;
            DFS(graph, DIST, visited, size, i);
        }
    }
}
