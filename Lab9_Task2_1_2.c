#include <stdio.h>
#include <stdlib.h>


int** Creategraph(int **, int); //Создание графа
void DFS(int **, int *, int *, int, int);

int size;   //Размер графа


// <---------- Список смежности ---------->
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
};
struct Graph* createGraph(int);
void addEdge(struct Graph* , int , int);
void printGraph(struct Graph*);
// <---------- ! ---------->

void ListDFS(struct Graph*, int *, int *, int);


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
        visited[i] = 0;
        for(j = 0; j < size; j++)
        {
            printf("%d ", graph[i][j]);
            if(graph[i][j] == 1) cnt++;
        }
        printf("\n");
        if(cnt == 0) DIST[i] = -2;
        dist[i] = DIST[i];
    }


    int num = size - 1;

    printf("Enter the number of start vertex (positive integer [0; %d]): ", num);
    scanf("%d", &v);

    // <---------- ! ---------->
    DFS(graph, DIST, visited, size, v);
    // <---------- ! ---------->
    printf("\n");

    for(i = 0; i < size; i++)
        printf("%d: %d\n", i, DIST[i] + 1);

    printf("\n\n");


// <---------- Список смежности ---------->
    struct Graph* graf = createGraph(size);

    for(i = 0; i < size; i++)
    {
        for(j = i; j < size; j++)
        {
            if(graph[i][j] == 1)
            {
                addEdge(graf, i, j);
            }
        }
    }

    printf("\n# Adjacency list #\n");
    printGraph(graf);
// <---------- ! ---------->

    for(i = 0; i < size; i++)
        visited[i] = 0;

    printf("\nEnter the number of start vertex (positive integer[0; %d]): ", num);
    scanf("%d", &v);

    // <---------- ! ---------->
    ListDFS(graf, visited, dist, v);
    // <---------- ! ---------->
    printf("\n");

    for(i = 0; i < size; i++)
        printf("%d: %d\n", i, dist[i] + 1);

    free(DIST);
    free(dist);
    free(graph);
    free(visited);

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


// <---------- Список смежности ---------->
struct node* createNode(int v)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices)
{
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct node*));

    int i;
    for (i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

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

void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node* temp = graph->adjLists[v];
        printf("%d:  ", v);
        while(temp)
        {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void ListDFS(struct Graph* graph, int *visited, int *dist, int v)
{
    visited[v] = 1;
    printf("%d ", v);
    struct node* temp = graph->adjLists[v];
    while (temp)
    {
        if(visited[temp->vertex] == 0)
        {
            dist[temp->vertex] = dist[v] + 1;
            ListDFS(graph, visited, dist, temp->vertex);
        }
        else
        {
            temp = temp -> next;
        }
    }
}
