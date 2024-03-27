//Name : Ahmad Qaimari
//Student ID : 1210190
//Section : 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Defining Constants
#define MAX_SIZE 20
#define LINE_SIZE 100
#define INF 999999
// Data structure to store a graph object
struct Graph
{

    int N;
    struct Node *head[];
};

// Data structure to store adjacency list nodes of the graph
struct Node
{
    int w;
    char dest[MAX_SIZE];
    struct Node *next;
};
//Data structure to store a Queue object
struct Queue
{
    struct Node *front;
    struct Node *rear;
};
//Data structure to sotre a heap node
struct MinHeapNode
{
    int v;
    int dist;
};
//Data structure to store a heap object
struct MinHeap
{
    int size;
    int capacity;
    int *pos;//Position of each node in the heap
    struct MinHeapNode **arr;
};
//Function to create an adjacency list node
struct Node *newNode(int x, char str[])
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->w = x;
    strcpy(temp->dest, str);
    temp->next = NULL;
    return temp;
}
//Function to create a queue
struct Queue *createQueue()
{
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

int isEmptyQueue(struct Queue *q)
{
    return q->front == NULL && q->rear == NULL;
}

void enQueue(struct Queue *q, int x, char str[])
{
    
    struct Node *temp = newNode(x, str);

    if (q->rear == NULL)//Checking if queue is empty
    {
        q->front = q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}

void deQueue(struct Queue *q)
{
    if (q->front == NULL)//if queue is empty don't do anything
        return;

    struct Node *temp = q->front;

    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
}
//function to return the size of a linked list
int Size(struct Node *L)
{
    int count = 0;
    struct Node *P = L->next;

    while (P != NULL)
    {
        count++;
        P = P->next;
    }
    return count;
}
//Fuction to insert elements into a linked list
void InsertAtEnd(int x, char str[], struct Node *L)
{
    struct Node *new_node;
    new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->w = x;
    strcpy(new_node->dest, str);
    new_node->next = NULL;
    if (L->next == NULL)
    { // Checking if the it's the first node to be inserted
        L->next = new_node;
    }
    else
    {
        struct Node *P = L;
        while (P->next != NULL)
            P = P->next;
        P->next = new_node;
    }
}

void PrintList(struct Node *L)
{
    struct Node *P = L;
    if (L->next == NULL)
        printf("Empty List");
    else
        do
        {
            P = P->next;
            printf("%d\t%s\t", P->w, P->dest);
        } while (P->next != NULL);
    printf("\n");
}

struct Node *ReverseList(struct Node *L)
{
    struct Node *P = L->next;
    struct Node *Prev = NULL;

    while (P != NULL)
    {
        struct Node *next = P->next;
        P->next = Prev;
        Prev = P;
        P = next;
    }
    L->next = Prev;
    return L;
}
//Function to check if a city is new in the linkedlist
int isNew(char str[], struct Node *L)
{
    if (L->next == NULL)
        return 1;
    else
    {
        struct Node *P = L->next;
        while (P != NULL)
        {
            if (!strcmp(str, P->dest))
                return 0;
            P = P->next;
        }
    }
    return 1;
}
//Function to return a city's index in a linked list
int getCityIndex(char str[], struct Node *L)
{

    struct Node *P = L->next;
    while (P != NULL)
    {
        if (!strcmp(str, P->dest))
            return P->w;
        P = P->next;
    }
}
//Function to return a city's index in an adjacency list
int getIndex(char city[], struct Graph *graph)
{
    for (int i = 0; i < graph->N; i++)
    {
        char current[MAX_SIZE];
        strcpy(current, graph->head[i]->dest);
        if (!strcmp(city, graph->head[i]->dest))
        {
            return i;
        }
    }

    return -1;
}
//Function to retturn the a city node given its index
struct Node *Find(int x, struct Node *L)
{
    struct Node *P;
    P = L->next;
    while (P != NULL && P->w != x)
        P = P->next;

    return P;
}

// Data structure to store a graph edge
struct Edge
{
    char src[MAX_SIZE];
    char dest[MAX_SIZE];
    int weight;
};

// Function to create an adjacency list from specified edges
struct Graph *createGraph(struct Edge edges[], int n, struct Node *src_cities)
{
    
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->N = Size(src_cities);
    // initialize head pointer for all vertices
    for (int i = 0; i < Size(src_cities); i++)
    {
        graph->head[i] = (struct Node *)malloc(sizeof(struct Node));
        strcpy(graph->head[i]->dest, Find(i, src_cities)->dest);
        graph->head[i]->next = NULL;
    }

    // Inserting edges to the directed graph one by one
    for (int i = 0; i < n; i++)
    {
        // getting the source and destination nodes and the weight of an edge
        char dest[MAX_SIZE];
        int src = getCityIndex(edges[i].src, src_cities);
        strcpy(dest, edges[i].dest);
        int weight = edges[i].weight;
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        strcpy(newNode->dest, dest);
        newNode->w = weight;
        newNode->next = NULL;
        //Inserting the main nodes into the adjacency list(graph->head)
        if (graph->head[src]->next == NULL)
        {
            graph->head[src]->next = newNode;
        }
        else
        {
            struct Node *P = graph->head[src];
            while (P->next != NULL)
                P = P->next;
            P->next = newNode;
        }
       
    }

    return graph;
}

// Function to print adjacency list representation of a graph
void printGraph(struct Graph *graph)
{
    for (int i = 0; i < graph->N; i++)
    {
        
        struct Node *ptr = graph->head[i]->next;
        while (ptr != NULL)
        {
            printf("(%s -> %s||%d km)\t", graph->head[i]->dest, ptr->dest, ptr->w);
            ptr = ptr->next;
        }

        printf("\n");
    }
}
//Function to get the weight between a node and its neighbor from the adjacency list
int getDistance(char src[MAX_SIZE], char dest[MAX_SIZE], struct Graph *graph)
{
    int src_index = getIndex(src, graph);//getting the head node of the source of an adjacency list
    struct Node *temp = graph->head[src_index]->next;
    while (temp != NULL)//iterating through the list
    {
        if (!strcmp(temp->dest, dest))
            return temp->w;
        temp = temp->next;
    }
}
//Function to get the number of non empty lines from a file
int getLinesCount(FILE *fp)
{
    int count = 0;
    char ch;
    while (!feof(fp))
    {
        ch = fgetc(fp);
        if (ch == '\n')
        {
            count++;
        }
    }
    return count;
}
//Function to get the list of unique citites from the file
struct Node *getSrcCities(FILE *input_file)
{
    struct Node *src_cities = (struct Node *)malloc(sizeof(struct Node));
    src_cities->next = NULL;
    char line[LINE_SIZE];
    int src_count = 0;
    while (fgets(line, LINE_SIZE, input_file) != NULL)
    {
        line[strcspn(line, "\n")] = 0;
        int i = 0;
        char *p = strtok(line, "\t"); // using strtok to divide the lines in the file to pieces of information
        char *arr[3];
        while (p != NULL) // saving the pieces of information in an array
        {
            arr[i++] = p;
            p = strtok(NULL, "\t");
        }
        if (isNew(arr[0], src_cities))
        {
            InsertAtEnd(src_count, arr[0], src_cities);
            src_count++;
        }
    }
    return src_cities;
}
//Function that constructs the graph from the file,returns the adjacency list
struct Graph *ReadFile(FILE *input_file)
{
    struct Node *src_cities = (struct Node *)malloc(sizeof(struct Node));//Creating the list of unique cities
    src_cities->next = NULL;
    char line[LINE_SIZE];
    int edges_count = getLinesCount(input_file);//The number of edges is the number of lines in the file
    rewind(input_file);//returning the file pointer to the start of the file
    struct Edge edges[edges_count];
    int count = 0;
    int src_count = 0;
    while (fgets(line, LINE_SIZE, input_file) != NULL)
    {
        line[strcspn(line, "\n")] = 0;//removing the new line character after reading from the file
        int i = 0;
        char *p = strtok(line, "\t"); // using strtok to divide the lines in the file to pieces of information
        char *arr[3];
        while (p != NULL) // saving the pieces of information in an array
        {
            arr[i++] = p;
            p = strtok(NULL, "\t");
        }
        if (isNew(arr[0], src_cities))
        {
            InsertAtEnd(src_count, arr[0], src_cities);
            src_count++;
        }
        //Creating the edges
        strcpy(edges[count].src, arr[0]);
        strcpy(edges[count].dest, arr[1]);
        edges[count].weight = atoi(arr[2]);
        count++;
    }

    struct Graph *adj_list = createGraph(edges, edges_count, src_cities);

    return adj_list;
}
//Function to perform the Breadth First Search algorithm
void BFS(struct Graph *graph, char src[MAX_SIZE], char Dest[MAX_SIZE],int mode)//mode is used to print the result either to the file or to the terminal
{
    //Obtaining the index of the source city in the adjacency list array
    int src_index = getIndex(src, graph);
    struct Queue *Q = createQueue();//Initializing a queue
    enQueue(Q, src_index, src);//Enqueuing the source city
    int visited[graph->N];//Array keep track of the visited nodes
    for (int i = 0; i < graph->N; i++)
        visited[i] = 0;
    
    visited[src_index] = 1;
    //Array to keep track of path
    int prev[graph->N];
    //If a city isn't in the path then it's parent is -1
    prev[src_index] = -1;
    //Array to keep track of costs to get to a node(Edges)
    int d[graph->N];
    for (int i = 0; i < graph->N; i++)
        d[i] = -1;
    d[src_index] = 0;
    //Linked list to sotre nodes that are in the path
    struct Node *path = (struct Node *)malloc(sizeof(struct Node));
    path->next = NULL;

    while (!isEmptyQueue(Q))//Keep checking the nodes in the Queue until its empty
    {
        //Stopping the algorithm when reaching the entered destination
        if (!strcmp(Dest, Q->front->dest))
            break;
        struct Node *node = newNode(getIndex(Q->front->dest, graph), Q->front->dest);
        deQueue(Q);
        //Pointer to iterate through the neighbors of a node in the adjacency list
        struct Node *neighbors = graph->head[getIndex(node->dest, graph)]->next;

        while (neighbors != NULL)
        {

            if (!visited[getIndex(neighbors->dest, graph)])//Chechking if node has already been visited
            {
                enQueue(Q, getIndex(neighbors->dest, graph), neighbors->dest);
                visited[getIndex(neighbors->dest, graph)] = 1;
                d[getIndex(neighbors->dest, graph)] = d[node->w] + 1;//Updating the cost when travelling a specific node
                prev[getIndex(neighbors->dest, graph)] = node->w;
            }
            neighbors = neighbors->next;
        }
    }
    //Cost in terms of edges to get to the destination
    int n_edges = d[getIndex(Dest, graph)];
    //Checking to see if the destination wasn't reachable from the source
    if (visited[getIndex(Dest, graph)] == 0)
        printf("No path to destination");
    
    else
    {
        int x = getIndex(Dest, graph);
        //Saving the Path in a linked list by going through the prev array
        while (x != -1)
        {
            InsertAtEnd(x, graph->head[x]->dest, path);
            x = prev[x];
        }
    }
    //Reversing the linked list since the path was saved from the destination to source
    path = ReverseList(path);
    //Total weight of each edge(not taken into consideration in the algorithm)
    int total = 0;
    struct Node *temp = path->next;
    //If mode parameter is one then the function prints to the terminal
    if(mode==0){
         while (temp->next != NULL)
    {
        total += getDistance(temp->dest, temp->next->dest, graph);
        printf("%s->%s( %d km)\n", temp->dest, temp->next->dest, getDistance(temp->dest, temp->next->dest, graph));
        temp = temp->next;
    }

    printf("Total Distance from %s to %s : %d km\n", src, Dest, total);
    printf("Edges Travelled : %d\n",n_edges);
    }
    //If the mode parameter is not 0 then the function prints to the file
    else{
        FILE *fp = fopen("shortest_distance.txt","a");
         while (temp->next != NULL)
    {
        total += getDistance(temp->dest, temp->next->dest, graph);
        fprintf(fp,"%s->%s( %d km)\n", temp->dest, temp->next->dest, getDistance(temp->dest, temp->next->dest, graph));
        temp = temp->next;
    }

    fprintf(fp,"Total Distance from %s to %s using BFS : %d km\n", src, Dest, total);
    printf("Edges Travelled : %d\n",n_edges);
    fclose(fp);
    }
    
    
   
    
}
//Function to create a heap node(includes the cities index in the adjacency list and the distance to it)

struct MinHeapNode *newMinHeapNode(int v, int dist)
{
    struct MinHeapNode *minHeapNode = (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
//Function to crrate a heap give a capacity
struct MinHeap *createMinHeap(int capacity)
{
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->arr = (struct MinHeapNode **)malloc(capacity * sizeof(struct MinHeapNode *));//Allocating size for the array
    return minHeap;
}
//Used to swap between heaps' nodes
void swap(struct MinHeapNode **a, struct MinHeapNode **b)
{
    struct MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

void Heapify(struct MinHeap *minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
    //Chehcking if the distance of the node on  the left is lower than the root
    if (left < minHeap->size &&minHeap->arr[left]->dist <minHeap->arr[smallest]->dist)
        smallest = left;
    //Chehcking if the distance of the node on  the right is lower than the root


if (right < minHeap->size &&minHeap->arr[right]->dist <minHeap->arr[smallest]->dist)
        smallest = right;

    if (smallest != idx)
    {
        // The nodes to be swapped in  heap
        struct MinHeapNode *smallestNode = minHeap->arr[smallest];
        struct MinHeapNode *idxNode = minHeap->arr[idx];

        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // Swap nodes
        swap(&minHeap->arr[smallest], &minHeap->arr[idx]);

        Heapify(minHeap, smallest);
    }
}

int isEmpty(struct MinHeap *minHeap)
{
    return minHeap->size == 0;
}

//Function to get the minimum node of the heap
struct MinHeapNode *getMin(struct MinHeap *minHeap)
{
    if (isEmpty(minHeap))
        return NULL;

    struct MinHeapNode *root = minHeap->arr[0];

    // Replace root node with last node
    struct MinHeapNode *lastNode = minHeap->arr[minHeap->size - 1];
    minHeap->arr[0] = lastNode;

    // Update position of last node
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    
    --minHeap->size;
    Heapify(minHeap, 0);

    return root;
}
//Function to organize the heap used  after inserting a new node
void Organize(struct MinHeap *minHeap, int v, int dist)
{
    int i = minHeap->pos[v];

    // Get the node and update its dist value
    minHeap->arr[i]->dist = dist;

    //Iterating through the heap and repositioning nodes
    while (i && minHeap->arr[i]->dist <minHeap->arr[(i - 1) / 2]->dist)
    {
        
        minHeap->pos[minHeap->arr[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->arr[(i - 1) / 2]->v] = i;
        swap(&minHeap->arr[i], &minHeap->arr[(i - 1) / 2]);

        // move to parent index
        i = (i - 1) / 2;
    }
}
//Function if node is in heap
int isInHeap(struct MinHeap *minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->size)
        return 1;
    return 0;
}
//Function to perform Djikstra's algorithm
void djikstra(struct Graph *graph, char start[MAX_SIZE], char end[MAX_SIZE],int mode)
{
    
    int src = getIndex(start, graph);//Getiing index of source in the adjancency list
    //Initializing arrays to save the distances and the previous nodes
    int dist[graph->N];
    int prev[graph->N];
    struct MinHeap *minHeap = createMinHeap(graph->N);

    for (int i = 0; i < graph->N; i++)
    {
        //Initializing all distance to infinity when first starting the algorithm
        dist[i] = INF;
        minHeap->arr[i] = newMinHeapNode(i, dist[i]);
        minHeap->pos[i] = i;
    }

    minHeap->arr[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;//Setting distance of source node to 0
    prev[src] = -1;//Setting previous of source node to -1 since it has no previous nodes
    Organize(minHeap, src, dist[src]);//Inserting the source city to the heap
    minHeap->size = graph->N;

    while (!isEmpty(minHeap))
    {
        struct MinHeapNode *minHeapNode = getMin(minHeap);

        int u = minHeapNode->v;
        
        struct Node *temp = graph->head[u]->next;
        while (temp != NULL)//Iterating through the adjancency list
        {

            int v = getIndex(temp->dest, graph);
            //Updating distances if they are lower than the saved ones
            if (isInHeap(minHeap, v) && dist[u] != INF && temp->w + dist[u] < dist[v])
            {
                dist[v] = dist[u] + temp->w;
                prev[v] = u;
                Organize(minHeap, v, dist[v]);
            }
            temp = temp->next;
        }
    }
    //Linked list to store shortest path
    struct Node *path = (struct Node *)malloc(sizeof(struct Node));
    path->next = NULL;
    int x = getIndex(end, graph);
    while (x != -1)
    {
        InsertAtEnd(x, graph->head[x]->dest, path);
        x = prev[x];
    }
    path = ReverseList(path);
    struct Node *temp = path->next;
    if(mode==0){
         while (temp->next != NULL)
    {
        printf("%s->%s( %d km)\n", temp->dest, temp->next->dest, getDistance(temp->dest, temp->next->dest, graph));
        temp = temp->next;
    }
    printf("Total Distance from %s to %s : %d km\n", start, end, dist[getIndex(end, graph)]);
    }
    else{
        FILE *fp = fopen("shortest_distance.txt","a");
        while (temp->next != NULL)
    {
        fprintf(fp,"%s->%s( %d km)\n", temp->dest, temp->next->dest, getDistance(temp->dest, temp->next->dest, graph));
        temp = temp->next;
    }
    fprintf(fp,"Total Distance from %s to %s using Dijkstra : %d km\n", start, end, dist[getIndex(end, graph)]);
    fclose(fp);
    }
   
}
//Function to print program menu
void displayMenu(){
    printf("Choose one of the following Options:\n1-Load Cities\n2-Enter Source\n3-Enter Destination\n4-Exit");
}

int main(void)
{
    //Start of Program
    displayMenu();
    int op;
    scanf("%d",&op);
    char Source[MAX_SIZE]="";
    char Destination[MAX_SIZE]="";
    struct Graph* graph;
    while(op!=4){
        if(op==1){
         FILE *fp;
         fp = fopen("cities.txt", "r");
         graph=ReadFile(fp);
         fclose(fp);
         printf("The Graph has been Constructed\n");


        }
        else if(op==2){
            printf("Please Enter the source\n");
            scanf("%s",Source);
            if(getIndex(Source,graph)==-1){
                printf("Entered city is not on the map");
            }
        }
        
        else if(op==3){
            printf("Please Enter the destination\n");
            scanf("%s",Destination);
            if(getIndex(Destination,graph)==-1){
                printf("Entered city is not on the map\n");
            
            }
            else if(!strcmp(Source,""))
                printf("Please enter a source city first\n");
            else{
                printf("Using Breadth First Seach Algorithm:\n");
                BFS(graph,Source,Destination,0);
                printf("\nUsing Dijkstra's Algorithm:\n");
                djikstra(graph,Source,Destination,0);
            }
        }
    
        displayMenu();
        scanf("%d",&op);
        
    }
    djikstra(graph,Source,Destination,1);
    BFS(graph,Source,Destination,1);
    printf("Program Quitted");

}
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    