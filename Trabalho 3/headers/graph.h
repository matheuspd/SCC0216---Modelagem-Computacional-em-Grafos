#ifndef __GRAPH__
#define __GRAPH__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int dest;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
} List;

typedef struct Graph {
    int num_vertices;
    List* adj_list;
} Graph;


// Graph functions
Node* createNode(int dest);
Graph* createGraph(int num_vertices);
void freeGraph(Graph* graph);
void addEdge(Graph* graph, int src, int dest);
void fillOrder(Graph* graph, int v, bool* visited, int* stack, int* stack_index);
void DFSUtil(Graph* graph, int v, bool* visited, int* components, int* component_index);
Graph* getReversedGraph(Graph* graph);
void reverseDFS(Graph* graph, int v, bool* visited);
int compareComponents(const void* a, const void* b);
int compareIntegers(const void* a, const void* b);
int countStronglyConnectedComponents(Graph* graph, int*** strongly_connected_components);
void printComponent(int* component);
void printComponents(int** strongly_connected_components, int num_components);
void sortComponents(int** strongly_connected_components, int num_components);

#endif