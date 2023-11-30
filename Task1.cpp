#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

int** Creategraph(int **, int); //Создание графа
void BFSD(int **, int *, int, int);  //Обход в ширину

int size;   //Размер графа


struct node
{
    int vertex;
    struct node* next;
};

struct node* createNode(int);

struct Graph
{
    int numVertices;
    struct node** adjLists;
    int* visited;
};

struct Graph* createGraph(int );
void addEdge(struct Graph *, int , int );
void printGraph(struct Graph *, int *);
void bfs(struct Graph *, int *, int );

int main()
{
    int i, j, v;
    int **graph = NULL, *DIST = NULL;


    printf("\t# Graphs #\n\n");
    printf("Enter the number of graph vertices (positive integer): ");
    scanf("%d", &size);

    // Creating the graph
    graph = Creategraph(graph, size);
    DIST = (int *)(malloc(sizeof(int *) * size));  // Array for visited vertices

    // Printing the matrix
    for(i = 0; i < size; i++)
    {
        DIST[i] = -1;
        for(j = 0; j < size; j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }

    int num = size - 1;

    printf("Enter the number of start vertex (positive integer [0; %d]): ", num);
    scanf("%d", &v);

    // <---------- ! ---------->
    BFSD(graph, DIST, size, v);
    // <---------- ! ---------->

    for(i = 0; i < size; i++)
        printf("%d: %d\n", i, DIST[i]);


    struct Graph* Graph = createGraph(size);
    int *dist = (int *)(malloc(sizeof(int *) * size));

    for(i = 0; i < size; i++)
    {
        dist[i] = -1;
        for(j = i; j < size; j++)
        {
            if(graph[i][j] == 1)
            {
                addEdge(Graph, i, j);
            }
        }
    }

    printf("\n\n");

    printGraph(Graph, dist);

    printf("Enter the number of start vertex (positive integer [0; %d]): ", num);
    scanf("%d", &v);

    // <---------- ! ---------->
    bfs(Graph, dist, v);
    // <---------- ! ---------->

    for(i = 0; i < size; i++)
        printf("%d: %d\n", i, dist[i] + 1);

    delete[] graph;
    delete[] DIST;
    delete[] dist;

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


//------------------------------------------------------

void bfs(struct Graph* graph, int *dist, int startVertex)
{
    queue<int> q;
    q.push(startVertex);

    graph->visited[startVertex] = 1;

    while(!q.empty())
    {
        int currentVertex = q.front();
        q.pop();

        struct node* temp = graph->adjLists[currentVertex];

        while(temp)
        {
            int adjVertex = temp->vertex;
            if(graph->visited[adjVertex] == 0)
            {
                graph->visited[adjVertex] = 1;
                q.push(adjVertex);
                dist[adjVertex] = dist[currentVertex] + 1;
            }
            temp = temp->next;
        }
    }
}

struct node* createNode(int v)
{
    struct node* newNode = new struct node;
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices)
{
    struct Graph* graph = new struct Graph;
    graph->numVertices = vertices;

    graph->adjLists = new struct node*[vertices];
    graph->visited = new int[vertices];

    int i;
    for (i = 0; i < vertices; i++)
    {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest)
{
    // Add edge from src to dest
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void printGraph(struct Graph* graph, int *dist)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node* temp = graph->adjLists[v];
        printf("%d:  ", v);

        if(temp == NULL) dist[v] = -2;

        while (temp)
        {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}
